/*
** EPITECH PROJECT, 2024
** RAYTRACER
** File description:
** Core
*/

#ifndef CORE_HPP_
#define CORE_HPP_

    #include "IShape.hpp"
    #include "Ray.hpp"
    #include "Color.hpp"
    #include "Camera.hpp"
    #include "Light.hpp"
    #include "HitData.hpp"
    #include "Range.hpp"
    #include "Utils.hpp"

    #include <vector>
    #include <memory>
    #include <unordered_map>
    #include <fcntl.h>
    #include <dirent.h>

namespace RayTracer {
    class Core {
        public:
            class RayException : public std::exception {
                public:
                    RayException(std::string const &message) { _message = message;}
                    const char *what() const noexcept override { return _message.c_str();}

                private:
                    std::string _message;
            };
            enum LIBRARY_TYPE {
                SPHERE,
                PLANE,
                CONE,
                CYLINDER,
                AMBIANT_LIGHT,
            };

            Core(int screenWidth, int screenHeight);
            ~Core() = default;

            void run();
            void writeColor(RayTracer::Color &color);

            std::vector<std::reference_wrapper<IShape>> _shapes;
            std::vector<std::reference_wrapper<Light>> _lights;
            std::unordered_map<LIBRARY_TYPE, std::shared_ptr<void>> _handles;

            void addShape(IShape &shape) { _shapes.push_back(shape); }
            void addLight(Light &light) { _lights.push_back(light); }

            RayTracer::Camera _camera;

            bool hit(const RayTracer::Ray &r, RayTracer::Range ray_range, HitData &data) const
            {
                HitData dataTmp;
                bool hasHitted = false;
                auto closest = ray_range.max;

                for (const auto &object : _shapes) {
                    if (object.get().hit(r, RayTracer::Range(ray_range.min, closest), dataTmp)) {
                        hasHitted = true;
                        closest = dataTmp.tValue;
                        data = dataTmp;
                    }
                }

                return hasHitted;
            }

            static void displayProgress(
                int current, int total,
                std::chrono::time_point<std::chrono::high_resolution_clock> iterationTime = std::chrono::high_resolution_clock::now(),
                std::chrono::time_point<std::chrono::high_resolution_clock> startTime = std::chrono::high_resolution_clock::now())
            {
                int progress = static_cast<int>((static_cast<double>(current) / total) * 100);
                int barWidth = 70;
                int filledWidth = static_cast<int>(barWidth * (static_cast<double>(progress) / 100));

                auto now = std::chrono::high_resolution_clock::now();
                std::chrono::duration<double> elapsed = now - iterationTime;
                auto totalElapsed = std::chrono::duration_cast<std::chrono::milliseconds>(now - startTime).count();

                double timeEstimate = 0.0;
                if (current != 0) {
                    timeEstimate = (totalElapsed / current) * (total - current);
                }

                std::clog << "\r[";
                for (int i = 0; i < barWidth; ++i) {
                    if (i < filledWidth) {
                        std::clog << "=";
                    } else if (i == filledWidth) {
                        std::clog << ">";
                    } else {
                        std::clog << " ";
                    }
                }
                std::clog << "] " << progress << "% (" << current << "/" << total << ")";
                std::clog << " - Elapsed: " << static_cast<int>(totalElapsed / 1000.0) << "s - ETA: " << static_cast<int>(timeEstimate / 1000) << "s (1/" << static_cast<int>(elapsed.count() * 1000) << "ms)";
                std::clog.flush();
            }

            void loadLibrairies();
            RayTracer::IShape& getNewShape(LIBRARY_TYPE type);


        private:
            int _screenWidth;
            int _screenHeight;

            void loadLibrary(std::string path);

            bool isShapeType(LIBRARY_TYPE type) {
                if (type != 4)
                    return true;
                else
                    return false;
            }
            bool isLightType(LIBRARY_TYPE type) {
                if (type == 4)
                    return true;
                else
                    return false;
            }
    };
}

#endif /* !CORE_HPP_ */
