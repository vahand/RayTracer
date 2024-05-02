/*
** EPITECH PROJECT, 2024
** RAYTRACER
** File description:
** Workers
*/

#ifndef WORKER_HPP_
    #define WORKER_HPP_

    #include "Core.hpp"

    #include <thread>
    #include <iostream>
    #include <mutex>
    #include <fstream>
    #include <unordered_map>
    #include <unistd.h>

class Workers {
    public:
        Workers(int threadsCount = 1, int imageWidth = 400, int imageHeight = 400)
            : _threadsCount(threadsCount), _width(imageWidth), _height(imageHeight)
        {
            if (_threadsCount < 1) {
                std::cerr << "Error: You can't run the program without at least one thread: " << _threadsCount << " threads requested, 1 thread minimum." << std::endl;
                exit(84);
            }

            if (_threadsCount > std::thread::hardware_concurrency()) {
                std::cerr << "Error: The computer does not have enough threads to run the program: " << _threadsCount << " threads requested, " << std::thread::hardware_concurrency() << " threads available." << std::endl;
                exit(84);
            }

            std::cerr << "[INFO] Running with " << _threadsCount << " / " << std::thread::hardware_concurrency() << " threads." << std::endl;
        }
        ~Workers() = default;

        void initialize(RayTracer::Core &core)
        {
            if (_threadsCount > std::thread::hardware_concurrency()) {
                std::cerr << "Error: The computer does not have enough threads to run the program: " << _threadsCount << " threads requested, " << std::thread::hardware_concurrency() << " threads available." << std::endl;
                exit(84);
            }

            _threads.resize(_threadsCount);

            _mutexes.clear();
            finalImage.clear();

            placeholderImage.clear();
            placeholderMutex.unlock();

            for (int i = 0; i < _threadsCount; i++) {
                _mutexes.push_back(std::make_unique<std::mutex>());
                _mutexes.at(i)->unlock();
            }

            for (int y = 0; y < core._screenHeight; y++) {
                finalImage[y] = std::vector<RayTracer::Color>();
                finalImage[y].reserve(core._screenWidth);
            }

            std::cerr << "[INFO] Initialized " << _mutexes.size() << " mutexes and " << _threads.size() << " threads." << std::endl;
        }

        int getFreeThreadIndex()
        {
            for (int i = 0; i < _mutexes.size(); i++) {
                if (_mutexes.at(i)->try_lock()) {
                    _mutexes.at(i)->unlock();
                    return i;
                }
            }
            return -1;
        }

        bool renderLine(int y, RayTracer::Core &core, std::mutex &mutex)
        {
            if (finalImage.find(y) != finalImage.end() && finalImage.at(y).size() == core._screenWidth) {
                mutex.unlock();
                return false;
            }

            for (int x = 0; x < core._screenWidth; x++) {
                double u = static_cast<double>(x) / core._screenWidth;
                double v = static_cast<double>(y) / core._screenHeight;

                RayTracer::Color finalColor(0, 0, 0);
                for (int sample = 0; sample < core._camera._samples; sample++) {
                    RayTracer::Ray ray = core._camera.rayAround(u, v);
                    finalColor += RayTracer::Core::getRayColor(ray, core, core._maxDepth);
                }
                finalColor *= core._camera._samplesScale;
                finalImage[y].push_back(finalColor);
            }
            mutex.unlock();
            return true;
        }

        void render(RayTracer::Core &core)
        {
            auto startTime = std::chrono::high_resolution_clock::now();

            for (int y = 0; y < core._screenHeight; y++) {
                int threadIndex = getFreeThreadIndex();
                if (threadIndex == -1) {
                    y--;
                    usleep(250);
                    continue;
                }
                core.displayProgress(y, core._screenHeight, startTime, threadIndex);

                _mutexes.at(threadIndex)->lock();
                _threads.at(threadIndex) = std::thread(&Workers::renderLine, this, y, std::ref(core), std::ref(*_mutexes.at(threadIndex)));
                _threads.at(threadIndex).detach();
            }

            auto endTime = std::chrono::high_resolution_clock::now();
            std::chrono::duration<double> elapsed = endTime - startTime;
            core.displayProgress(core._screenHeight, core._screenHeight, startTime);
            std::cerr << "\nDone! - Total Lines: " << core._screenHeight << std::endl;

            for (int i = 0; i < _mutexes.size(); i++) {
                if (_mutexes.at(i)->try_lock()) {
                    _mutexes.at(i)->unlock();
                } else {
                    i--;
                    usleep(250);
                }
            }

            if (!isImageComplete()) {
                std::cerr << "Error: The image is not complete. Printing it anyway..." << std::endl;
            }

            printImage();
        }

        void beginRender()
        {
            _yUpdate = 0;
            _startTime = std::chrono::high_resolution_clock::now();
        }

        void copyToPlaceholder()
        {
            for (int y = 0; y < finalImage.size(); y++) {
                if (finalImage.find(y) != finalImage.end()) {
                    placeholderMutex.lock();
                    placeholderImage[y] = finalImage[y];
                    placeholderMutex.unlock();
                }
            }
        }

        void renderUpdate(RayTracer::Core &core)
        {
            int threadIndex = getFreeThreadIndex();
            while (threadIndex != -1 && _yUpdate < core._screenHeight) {
                _yUpdate++;
                core.displayProgress(_yUpdate, core._screenHeight, _startTime, threadIndex);

                _mutexes.at(threadIndex)->lock();
                _threads.at(threadIndex) = std::thread(&Workers::renderLine, this, _yUpdate, std::ref(core), std::ref(*_mutexes.at(threadIndex)));
                _threads.at(threadIndex).detach();
                threadIndex = getFreeThreadIndex();
            }

            // update placeholder image (copy all key/values from finalImage)
            copyToPlaceholder();

            if (_yUpdate >= core._screenHeight) {
                _endTime = std::chrono::high_resolution_clock::now();
                std::chrono::duration<double> elapsed = _endTime - _startTime;
                core.displayProgress(core._screenHeight, core._screenHeight, _startTime);
                std::cerr << "\nDone! - Total Lines: " << core._screenHeight << std::endl;

                for (int i = 0; i < _mutexes.size(); i++) {
                    if (_mutexes.at(i)->try_lock()) {
                        _mutexes.at(i)->unlock();
                    } else {
                        i--;
                        usleep(250);
                    }
                }

                processImage();
                copyToPlaceholder();
                usleep(1000);
                _rendering = false;
            }
        }

        bool isRendering() const { return _rendering; }
        void setRendering(bool rendering) { _rendering = rendering; }

        void writeImageToFile(const std::string &filename) const
        {
            std::ofstream file(filename);
            file << "P3\n" << _width << " " << _height << "\n255\n";
            for (int y = 0; y < _height; y++) {
                for (int x = 0; x < _width; x++) {
                    file << finalImage.at(y)[x]._r << " " << finalImage.at(y)[x]._g << " " << finalImage.at(y)[x]._b << "\n";
                }
            }
            file.close();
        }

        void processImage() {
            static const RayTracer::Range colorRange(0.0, 255.0);

            std::cerr << "Processing image..." << std::endl;
            for (int y = 0; y < _height; y++) {
                for (int x = 0; x < _width; x++) {
                    RayTracer::Color colorGamma = RayTracer::Core::getGammaColor(finalImage.at(y)[x]);
                    int r = colorRange.bound(colorGamma._r);
                    int g = colorRange.bound(colorGamma._g);
                    int b = colorRange.bound(colorGamma._b);
                    finalImage.at(y)[x] = RayTracer::Color(r, g, b);
                }
            }
        }

        void printImage() const
        {
            static const RayTracer::Range colorRange(0.0, 255.0);

            std::cout << "P3\n" << _width << " " << _height << "\n255\n";
            for (int y = 0; y < _height; y++) {
                for (int x = 0; x < _width; x++) {
                    RayTracer::Color colorGamma = RayTracer::Core::getGammaColor(finalImage.at(y)[x]);
                    int r = colorRange.bound(colorGamma._r);
                    int g = colorRange.bound(colorGamma._g);
                    int b = colorRange.bound(colorGamma._b);
                    std::cout << r << " " << g << " " << b << "\n";
                }
            }
        }

        bool isImageComplete() const
        {
            for (int y = 0; y < _height; y++) {
                if (finalImage.find(y) == finalImage.end())
                    return false;
                if (finalImage.at(y).size() != _width)
                    return false;
            }
            return true;
        }

        std::unordered_map<int, std::vector<RayTracer::Color>> finalImage;
        std::unordered_map<int, std::vector<RayTracer::Color>> placeholderImage;
        std::mutex placeholderMutex;
        std::vector<std::thread> _threads;
        std::vector<std::unique_ptr<std::mutex>> _mutexes;

        int getThreadsCount() const { return _threadsCount; }

    protected:
    private:
        int _threadsCount;
        int _width;
        int _height;

        int _yUpdate = 0;
        std::chrono::time_point<std::chrono::high_resolution_clock> _startTime;
        std::chrono::time_point<std::chrono::high_resolution_clock> _endTime;
        bool _rendering = false;

};

#endif /* !WORKERS_HPP_ */
