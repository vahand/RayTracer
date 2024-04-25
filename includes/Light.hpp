/*
** EPITECH PROJECT, 2024
** BS_RAYTRACER
** File description:
** Light
*/

#ifndef LIGHT_HPP_
    #define LIGHT_HPP_

    #include "Point3D.hpp"
    #include "Vector3D.hpp"

namespace RayTracer {
    class Light {
        public:
            Light() = default;
            Light(Math::Point3D position, double intensity, Math::Vector3D color) {
                _position = position;
                _intensity = intensity;
                _color = color;
            }
            Light(Math::Point3D& position, double intensity, Math::Vector3D& color) : _position(position), _intensity(intensity), _color(color) {}
            Light(const Light &light) {
                _position = light._position;
                _intensity = light._intensity;
                _color = light._color;
            }
            ~Light() = default;

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
