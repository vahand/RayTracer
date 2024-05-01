/*
** EPITECH PROJECT, 2024
** RAYTRACER
** File description:
** Core
*/

#ifndef CORE_HPP_
#define CORE_HPP_

    #include "../primitives/sphere/src/Sphere.hpp"
    #include "../primitives/plane/src/Plane.hpp"
    #include "../materials/lambertian/src/Lambertian.hpp"
    #include "../materials/metal/src/Metal.hpp"
    #include "../materials/lightDiffuse/src/LightDiffuse.hpp"
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
    #include <iostream>
    #include <filesystem>

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
                SPHERE = 0,
                PLANE = 1,
                CONE = 2,
                CYLINDER = 3,
                AMBIANT_LIGHT = 100,
                LAMBERTIAN = 1000,
                METAL = 1001,
                LIGHT_DIFFUSE = 1002
            };

            Core(int screenWidth, int screenHeight);
            ~Core() = default;

            std::vector<std::reference_wrapper<IShape>> _shapes;
            std::vector<std::reference_wrapper<Light>> _lights;
            std::unordered_map<LIBRARY_TYPE, std::shared_ptr<void>> _handles;
            std::unordered_map<std::string, std::shared_ptr<RayTracer::Material::AMaterial>> _loadedMaterials;
            RayTracer::Color sceneBackground;
            int _screenWidth;
            int _screenHeight;
            int _maxDepth = 10;
            RayTracer::Camera _camera;

            void addShape(IShape &shape) { _shapes.push_back(shape); }
            void addLight(Light &light) { _lights.push_back(light); }
            void addMaterial(const std::string &name, std::shared_ptr<RayTracer::Material::AMaterial> material) { _loadedMaterials[name] = material; }

            void printShape() {
                for (auto &shape : _shapes) {
                    std::cerr << shape.get().getName() << std::endl;
                }
            }
            void printLight() {
                for (auto &light : _lights) {
                    std::cerr << light.get().getName() << std::endl;
                }
            }
            void printMaterials() {
                for (const auto& pair : _loadedMaterials) {
                    std::cerr << pair.first << std::endl;
                }
            }

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

            static RayTracer::Color getGammaColor(RayTracer::Color color)
            {
                double r = color._r / 255.0;
                double g = color._g / 255.0;
                double b = color._b / 255.0;

                r = std::sqrt(r);
                g = std::sqrt(g);
                b = std::sqrt(b);

                return RayTracer::Color(r * 255, g * 255, b * 255);
            }

            static RayTracer::Color getRayColor(const RayTracer::Ray& r, const RayTracer::Core& core, int limit = 10) {
                if (limit <= 0)
                    return RayTracer::Color(0, 0, 0);

                HitData data;
                double infinity = std::numeric_limits<double>::infinity();
                if (!core.hit(r, RayTracer::Range(0.001, infinity), data))
                    return core.sceneBackground;

                RayTracer::Ray diffusedRay;
                RayTracer::Color dissipation;
                RayTracer::Color emitted = data.material->emit();

                if (!data.material->diffuse(r, data, dissipation, diffusedRay))
                    return emitted;

                RayTracer::Color diffusedColor = dissipation * getRayColor(diffusedRay, core, limit - 1);
                return emitted + diffusedColor;
            }

            static void displayProgress(
                int current, int total,
                std::chrono::time_point<std::chrono::high_resolution_clock> iterationTime = std::chrono::high_resolution_clock::now(),
                std::chrono::time_point<std::chrono::high_resolution_clock> startTime = std::chrono::high_resolution_clock::now(),
                int threadIndex = 0)
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
                std::clog << " - Thread: " << threadIndex;
                std::clog << "       ";
                std::clog.flush();
            }

            void loadLibrairies();
            RayTracer::IShape& getNewShape(LIBRARY_TYPE type);
            std::shared_ptr<RayTracer::Material::AMaterial> getNewMaterial(LIBRARY_TYPE type);
            void loadNewMaterial(LIBRARY_TYPE type, MaterialConfig& config, const std::string& name);

        private:
            void loadLibrary(std::string path);

            bool isShapeType(LIBRARY_TYPE type) {
                if (type < 100)
                    return true;
                else
                    return false;
            }
            bool isLightType(LIBRARY_TYPE type) {
                if (type >= 100 && type <= 1000)
                    return true;
                else
                    return false;
            }
            bool isMaterialType(LIBRARY_TYPE type) {
                if (type >= 1000)
                    return true;
                else
                    return false;
            }
    };
}

#endif /* !CORE_HPP_ */
