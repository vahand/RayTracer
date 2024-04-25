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
            enum LightType {
                AMBIENT,
                POINT,
                DIRECTIONAL
            };
            Light(const Math::Point3D& position, double intensity, const Math::Vector3D& color)
                : _position(position), _intensity(intensity), _color(color) {}
            Light(const Math::Point3D& position, double ambient, double diffuse, LightType type)
                : _position(position), _ambient(ambient), _diffuse(diffuse), _type(type) {}

            Math::Point3D position() const { return _position; }
            double intensity() const { return _intensity; }
            Math::Vector3D color() const { return _color; }

            const std::string& getName() const { return _name; }
            void setName(const std::string& name) { _name = name; }

        private:
            Math::Point3D _position;
            double _intensity;
            Math::Vector3D _color;

            double _ambient;
            double _diffuse;
            LightType _type;
            std::string _name;
    };

}

#endif /* !LIGHT_HPP_ */
