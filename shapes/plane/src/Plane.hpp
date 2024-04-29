/*
** EPITECH PROJECT, 2024
** Raytracer
** File description:
** Plane
*/

#ifndef PLANE_HPP_
#define PLANE_HPP_

#include "../../../includes/IShape.hpp"
#include "../../../includes/HitData.hpp"
#include "../../../includes/Range.hpp"
#include "../../../includes/Ray.hpp"
#include <cmath>

namespace RayTracer {
    class Plane : public IShape {
        public:
            enum AXIS {
                X,
                Y,
                Z
            };
            Plane() {};
            ~Plane() {};

            Math::Vector3D getVectorFromPoints(const Math::Point3D& lhs, const Math::Point3D& rhs) const
            {
                return Math::Vector3D(lhs.x() - rhs.x(), lhs.y() - rhs.y(), lhs.z() - rhs.z());
            }

            bool hit(const RayTracer::Ray& ray, RayTracer::Range ray_range, HitData& data) const override
            {
                if (isVectorParallel(ray.direction()))
                    return false;
                Math::Point3D a = ray.origin();
                Math::Vector3D ab = ray.direction();
                Math::Vector3D n = getNormalVector();
                double numerator = (-1) * (n.X * a.X) - (n.Y * a.Y) - (n.Z * a.Z);
                double denominator = (n.X * ab.X) + (n.Y * ab.Y) + (n.Z * ab.Z);
                double t = numerator / denominator;
                if (!ray_range.around(t))
                    return false;
                data.tValue = t;
                data.normal = getNormalVector();
                data.point = ray.at(t);
                std::cerr << "Hit on plane!" << std::endl;
                return true;
             }

            RayTracer::Color getColor() const override {
                return _color;
            };

            void setup(RayTracer::Color& planeColor, Math::Point3D& origin, RayTracer::Plane::AXIS axis)
            {
                _color = planeColor;
                _origin = origin;
                _axis = axis;
                if (_axis == RayTracer::Plane::AXIS::X) {
                    _normal = Math::Vector3D(1, 0, 0);
                } else if (_axis == RayTracer::Plane::AXIS::Y) {
                    _normal = Math::Vector3D(0, 1, 0);
                } else {
                    _normal = Math::Vector3D(0, 0, 1);
                }
            }

            Math::Vector3D getNormalVector() const {
                return _normal;
            }

            bool isVectorParallel(const Math::Vector3D& vector) const {
                return getNormalVector().DotProduct(vector) == 0.0;
            }

        protected:
        private:
            RayTracer::Color _color;
            Math::Point3D _origin;
            RayTracer::Plane::AXIS _axis;
            Math::Vector3D _normal;
    };
}

#endif /* !PLANE_HPP_ */
