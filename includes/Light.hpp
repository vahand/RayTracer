/*
** EPITECH PROJECT, 2024
** BS_RAYTRACER
** File description:
** Light
*/

#ifndef LIGHT_HPP_
    #define LIGHT_HPP_

    #include "Point3D.hpp"

namespace RayTracer {
    class Light {
        public:
            Light(const Math::Point3D& position, double intensity, const Math::Vector3D& color)
                : _position(position), _intensity(intensity), _color(color) {}

            Math::Point3D position() const { return _position; }
            double intensity() const { return _intensity; }
            Math::Vector3D color() const { return _color; }

        private:
            Math::Point3D _position;
            double _intensity;
            Math::Vector3D _color;
    };

}

#endif /* !LIGHT_HPP_ */
