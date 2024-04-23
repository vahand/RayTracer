/*
** EPITECH PROJECT, 2024
** BS_RAYTRACER
** File description:
** Sphere
*/

#ifndef SPHERE_HPP_
    #define SPHERE_HPP_

    #include "../../../includes/IShape.hpp"
    #include <cmath>

namespace RayTracer {
    class Sphere : public IShape {
        public:
            Sphere() = default;
            Sphere(const Math::Point3D& center, double radius, const RayTracer::Color& color) {
                _origin = center;
                _radius = radius;
                _color = color;
            }

            void setup(const Math::Point3D& center, double radius, const RayTracer::Color& color) {
                _origin = center;
                _radius = radius;
                _color = color;
            }

            Math::Vector3D getVectorFromPoints(const Math::Point3D& lhs, const Math::Point3D& rhs) const {
                return Math::Vector3D(lhs.x() - rhs.x(), lhs.y() - rhs.y(), lhs.z() - rhs.z());
            }

            HitResult hits(const Ray& ray) override {
                Math::Vector3D oc = ray.origin() - _origin;

                double a = ray.direction().DotProduct(ray.direction());
                double b = 2.0 * oc.DotProduct(ray.direction());
                double c = oc.DotProduct(oc) - _radius * _radius;

                double discriminant = b * b - 4 * a * c;

                if (discriminant < 0) {
                    return { Math::Point3D(), false };
                } else {
                    double t1 = (-b - sqrt(discriminant)) / (2.0 * a);
                    double t2 = (-b + sqrt(discriminant)) / (2.0 * a);

                    if (t1 >= 0 || t2 >= 0) {
                        Math::Point3D intersectionPoint = ray.origin() + ray.direction() * std::min(t1, t2);
                        return { intersectionPoint, true };
                    } else {
                        return { Math::Point3D(), false };
                    }
                }
            }

            Math::Vector3D normal(const Math::Point3D& point) const {
                Math::Vector3D normal = getVectorFromPoints(_origin, point).normalize();
                return normal;
            };

            Math::Point3D center() const { return _origin; }
            double radius() const { return _radius; }
            RayTracer::Color getColor() const override { return _color; }

            RayTracer::Ray objectRay(const Math::Point3D& objectPosition) const {
                return RayTracer::Ray(_origin, getVectorFromPoints(objectPosition, _origin));
            }

        private:
            Math::Point3D _origin;
            double _radius;
            RayTracer::Color _color;
    };
}

#endif /* !SPHERE_HPP_ */
