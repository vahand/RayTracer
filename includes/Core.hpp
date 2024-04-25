/*
** EPITECH PROJECT, 2024
** BS_RAYTRACER
** File description:
** Core
*/

#ifndef CORE_HPP_
    #define CORE_HPP_

    #include "../shapes/sphere/src/Sphere.hpp"
    #include "../shapes/plane/src/Plane.hpp"
    #include "Ray.hpp"
    #include "Color.hpp"
    #include "Camera.hpp"
    #include "Light.hpp"
    #include "Loader.hpp"

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
            RayTracer::Color castLight(const RayTracer::Ray &ray) const;
            void writeColor(RayTracer::Color &color);

            std::vector<std::reference_wrapper<IShape>> _shapes;
            std::vector<std::reference_wrapper<Light>> _lights;

            std::unordered_map<LIBRARY_TYPE, std::shared_ptr<void>> _handles;

            void loadLibrairies();
            RayTracer::IShape& getNewShape(LIBRARY_TYPE type);

            void addShape(IShape &shape) { _shapes.push_back(shape); }
            void addLight(Light &light) { _lights.push_back(light); }

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

            RayTracer::Camera _camera;

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
