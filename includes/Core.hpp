/*
** EPITECH PROJECT, 2024
** BS_RAYTRACER
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

    #include <vector>
    #include <memory>

namespace RayTracer {
    class Core {
        public:
            Core(int screenWidth, int screenHeight);
            ~Core() = default;

            void run();
            RayTracer::Color castLight(const RayTracer::Ray &ray) const;
            void writeColor(RayTracer::Color &color);

            std::vector<std::reference_wrapper<IShape>> _shapes;
            std::vector<std::reference_wrapper<Light>> _lights;

            void addShape(IShape &shape) { _shapes.push_back(shape); }
            void addLight(Light &light) { _lights.push_back(light); }

            RayTracer::Camera _camera;

        private:
            int _screenWidth;
            int _screenHeight;
    };
}

#endif /* !CORE_HPP_ */
