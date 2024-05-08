/*
** EPITECH PROJECT, 2024
** Raytracer
** File description:
** Plane
*/

#ifndef PLANE_HPP_
#define PLANE_HPP_

#include "../../../../includes/AShape.hpp"
#include "../../../../includes/HitData.hpp"
#include "../../../../includes/Range.hpp"
#include "../../../../includes/Ray.hpp"
#include "../../../../includes/AMaterial.hpp"
#include <cmath>

namespace RayTracer {
    class Plane : public AShape {
        public:
            Plane() = default;
            Plane(Math::Point3D origin, RayTracer::ShapeConfig::AXIS axis, std::shared_ptr<RayTracer::Material::IMaterial> material)
            {
                _origin = origin;
                _axis = axis;
                _material = material;
                if (_axis == RayTracer::ShapeConfig::AXIS::X) {
                    _normal = Math::Vector3D(1, 0, 0);
                } else if (_axis == RayTracer::ShapeConfig::AXIS::Y) {
                    _normal = Math::Vector3D(0, 1, 0);
                } else {
                    _normal = Math::Vector3D(0, 0, 1);
                }
            }

            void setup(const RayTracer::ShapeConfig& config)
            {
                _origin = config._origin;
                _axis = config._axis;
                _material = config._material;
                if (_axis == RayTracer::ShapeConfig::AXIS::X) {
                    _normal = Math::Vector3D(1, 0, 0);
                } else if (_axis == RayTracer::ShapeConfig::AXIS::Y) {
                    _normal = Math::Vector3D(0, 1, 0);
                } else {
                    _normal = Math::Vector3D(0, 0, 1);
                }
            }

            Math::Vector3D getVectorFromPoints(const Math::Point3D& lhs, const Math::Point3D& rhs) const
            {
                return Math::Vector3D(lhs.x() - rhs.x(), lhs.y() - rhs.y(), lhs.z() - rhs.z());
            }

            double getDConstante() const
            {
                Math::Vector3D n = getNormalVector();
                Math::Point3D o = _origin;
                double d = n.X * o.X + n.Y * o.Y + n.Z * o.Z;

                return d;
            }

            bool hit(const RayTracer::Ray& ray, RayTracer::Range ray_range, HitData& data) const override
            {
                double d = getDConstante();
                double t = (d - ray.origin().DotProduct(getNormalVector())) / getNormalVector().DotProduct(ray.direction());
                if (t < ray_range.min || t > ray_range.max)
                    return false;
                data.tValue = t;
                data.point = ray.at(data.tValue);
                data.normal = getNormalVector();
                data.determineFace(ray, data.normal);
                data.material = _material;
                return true;
            }

            Math::Vector3D getNormalVector() const {
                return _normal;
            }

            bool isVectorParallel(const Math::Vector3D& vector) const {
                return getNormalVector().DotProduct(vector) == 0.0;
            }

            void rotate(const Math::Vector3D &rotation) override {
                Math::Vector3D vecTemp;
                _rotation = rotation;
                degreeToRadian(_rotation);
                std::cerr << "Rotate: " << _rotation.X << "  " << _rotation.Y << "  " << _rotation.Z << std::endl;
                if (rotation.X != 0) {
                    vecTemp.X = (1 * _normal.X) + (0 * _normal.Y) + (0 * _normal.Z);
                    vecTemp.Y = (0 * _normal.X) + (cos(_rotation.x()) * _normal.Y) + (-sin(_rotation.x()) * _normal.Z);
                    vecTemp.Z = (0 * _normal.X) + (sin(_rotation.x()) * _normal.Y) + (cos(_rotation.x()) * _normal.Z);
                    _normal = vecTemp;
                }
                if (rotation.Y != 0) {
                    vecTemp.X = (cos(_rotation.y()) * _normal.X) + (0 * _normal.Y) + (sin(_rotation.y()) * _normal.Z);
                    vecTemp.Y = (0 * _normal.X) + (1 * _normal.Y) + (0 * _normal.Z);
                    vecTemp.Z = (-sin(_rotation.y()) * _normal.X) + (0 * _normal.Y) + (cos(_rotation.y()) * _normal.Z);
                    _normal = vecTemp;
                }
                if (rotation.Z != 0) {
                    vecTemp.X = (cos(_rotation.z()) * _normal.X) + (-sin(_rotation.z()) * _normal.Y) + (0 * _normal.Z);
                    vecTemp.Y = (sin(_rotation.z()) * _normal.X) + (cos(_rotation.z()) * _normal.Y) + (0 * _normal.Z);
                    vecTemp.Z = (0 * _normal.X) + (0 * _normal.Y) + (1 * _normal.Z);
                    _normal = vecTemp;
                }
                std::cerr << "Normal: " << _normal.X << "  " << _normal.Y << "  " << _normal.Z << std::endl;
                return;
            }

        protected:
        private:
            RayTracer::ShapeConfig::AXIS _axis;
            Math::Vector3D _normal;
            Math::Vector3D _rotation;
            std::shared_ptr<RayTracer::Material::IMaterial> _material;
    };
}

#endif /* !PLANE_HPP_ */
