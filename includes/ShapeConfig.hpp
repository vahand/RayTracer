/*
** EPITECH PROJECT, 2024
** RAYTRACER
** File description:
** ShapeConfig
*/

#pragma once

#include "Vector3D.hpp"
#include "Color.hpp"
#include "Point3D.hpp"

namespace RayTracer {
    class ShapeConfig {
        public:
            enum AXIS {
                X,
                Y,
                Z
            };
            ShapeConfig() = default;
            ~ShapeConfig() = default;

            double _radius;
            Math::Point3D _origin;
            Math::Vector3D _direction;
            int _type;
            std::shared_ptr<RayTracer::Material::AMaterial> _material;
            RayTracer::ShapeConfig::AXIS _axis;

        protected:
        private:
    };
}

