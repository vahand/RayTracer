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

#include <unordered_map>
#include <exception>

namespace RayTracer {
    class ShapeConfig {
        public:
            enum AXIS {
                X,
                Y,
                Z
            };
            ShapeConfig() = default;
            ShapeConfig(std::unordered_map<std::string, std::shared_ptr<RayTracer::Material::IMaterial>>& loadedMaterials)
                : _loadedMaterials(loadedMaterials) {}
            ~ShapeConfig() = default;

            // double _radius;
            // double _height;
            // double _angle;
            // Math::Point3D _origin;
            // Math::Vector3D _direction;
            // int _type;
            // std::shared_ptr<RayTracer::Material::IMaterial> _material;
            // RayTracer::ShapeConfig::AXIS _axis;

            std::unordered_map<std::string, std::shared_ptr<RayTracer::Material::IMaterial>>& _loadedMaterials;
            std::unordered_map<std::string, std::string> _parameters;

        protected:
        private:
    };
}

