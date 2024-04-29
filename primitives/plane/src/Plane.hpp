/*
** EPITECH PROJECT, 2024
** Raytracer
** File description:
** Plane
*/

#ifndef PLANE_HPP_
#define PLANE_HPP_

#include "../../../includes/AShape.hpp"
#include "../../../includes/HitData.hpp"
#include "../../../includes/Range.hpp"
#include "../../../includes/Ray.hpp"
#include <cmath>

namespace RayTracer {
    class Plane : public AShape {
        public:
            enum AXIS {
                X,
                Y,
                Z
            };

            Plane() = default;
            Plane(Math::Point3D origin, RayTracer::Plane::AXIS axis, std::shared_ptr<RayTracer::Material::AMaterial> material)
            {
                _origin = origin;
                _axis = axis;
                _material = material;
                if (_axis == RayTracer::Plane::AXIS::X) {
                    _normal = Math::Vector3D(1, 0, 0);
                } else if (_axis == RayTracer::Plane::AXIS::Y) {
                    _normal = Math::Vector3D(0, 1, 0);
                } else {
                    _normal = Math::Vector3D(0, 0, 1);
                }
            }
            ~Plane() = default;

            void setup(const RayTracer::ShapeConfig& config)
            {
                _origin = config._origin;
                // _axis = config._axis;
                _normal = config._direction;
                _material = config._material;
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
                if (isVectorParallel(ray.direction())) {
                    std::cerr << "Ray is parallel to plane" << std::endl;
                    return false;
                }
                Math::Point3D A = ray.origin();
                Math::Vector3D AB = ray.direction();
                // std::cerr << "AB: (" << ab.X << " ; " << ab.Y << " ; " << ab.Z << ")" << std::endl;
                Math::Vector3D n = getNormalVector();
                double d = getDConstante();
                // std::cerr << "D = " << d << std::endl;
                if (d < 0) {
                    return false;
                }
                double numerator = -d - (n.X * A.X) - (n.Y * A.Y) - (n.Z * A.Z);
                double denominator = (n.X * AB.X) + (n.Y * AB.Y) + (n.Z * AB.Z);
                double t = numerator / denominator;
                // if (!ray_range.around(t)) {
                //     std::cerr << "T solution is not in the range" << std::endl;
                //     return false;
                // }
                double x = A.X + AB.X * t;
                double y = A.Y + AB.Y * t;
                double z = A.Z + AB.Z * t;
                // std::cerr << "hit with (AB): (" << x << " ; " << y << " ; " << z << ")" << std::endl;
                data.tValue = t;
                data.normal = getNormalVector();
                data.point = ray.at(t);
                // std::cerr << "Hit on plane!" << std::endl;
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
            RayTracer::Plane::AXIS _axis;
            Math::Vector3D _normal;
            std::shared_ptr<RayTracer::Material::AMaterial> _material;
    };
}

#endif /* !PLANE_HPP_ */
