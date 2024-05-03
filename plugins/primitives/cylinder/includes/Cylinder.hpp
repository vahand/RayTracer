/*
** EPITECH PROJECT, 2024
** Raytracer
** File description:
** Cylinder
*/

#ifndef CYLINDER_HPP_
#define CYLINDER_HPP_

#include "../../../../includes/AShape.hpp"
#include "../../../../includes/HitData.hpp"
#include "../../../../includes/Range.hpp"
#include "../../../../includes/Ray.hpp"
#include "../../../../includes/AMaterial.hpp"
#include <cmath>

namespace RayTracer {
    class Cylinder : public AShape {
        public:
            Cylinder() = default;
            Cylinder(Math::Point3D origin, RayTracer::ShapeConfig::AXIS axis, double radius, double height, std::shared_ptr<RayTracer::Material::IMaterial> material)
            {
                _origin = origin;
                _axis = axis;
                _material = material;
                _radius = radius;
                _height = height;
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

        protected:
        private:
            Math::Point3D _origin;
            RayTracer::ShapeConfig::AXIS _axis;
            Math::Vector3D _normal;
            std::shared_ptr<RayTracer::Material::IMaterial> _material;
            double _radius;
            double _height;
    };
}

#endif /* !CYLINDER_HPP_ */
