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
                finalColor *= core._camera._samples_scale;
                finalImage[y].push_back(finalColor);
            }
            mutex.unlock();
            return true;
        }

        void render(RayTracer::Core &core)
        {
            auto startTime = std::chrono::high_resolution_clock::now();

            auto iterationTime = std::chrono::high_resolution_clock::now();
            for (int y = 0; y < core._screenHeight; y++) {
                int threadIndex = getFreeThreadIndex();
                if (threadIndex == -1) {
                    y--;
                    usleep(250);
                    continue;
                }
                iterationTime = std::chrono::high_resolution_clock::now();
                core.displayProgress(y, core._screenHeight, iterationTime, startTime, threadIndex);

                _mutexes.at(threadIndex)->lock();
                _threads.at(threadIndex) = std::thread(&Workers::renderLine, this, y, std::ref(core), std::ref(*_mutexes.at(threadIndex)));
                _threads.at(threadIndex).detach();
            }

            auto endTime = std::chrono::high_resolution_clock::now();
            std::chrono::duration<double> elapsed = endTime - startTime;
            core.displayProgress(core._screenHeight, core._screenHeight, iterationTime, startTime);
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
        std::vector<std::thread> _threads;
        std::vector<std::unique_ptr<std::mutex>> _mutexes;

        int getThreadsCount() const { return _threadsCount; }

    protected:
    private:
        int _threadsCount;
        int _width;
        int _height;

};

#endif /* !WORKERS_HPP_ */
