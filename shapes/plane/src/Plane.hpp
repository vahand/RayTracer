/*
** EPITECH PROJECT, 2024
** Raytracer
** File description:
** Plane
*/

#ifndef PLANE_HPP_
#define PLANE_HPP_

#include "../../../includes/IShape.hpp"

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

            HitResult hits(const RayTracer::Ray &ray) override {
                Math::Vector3D oc = ray.origin() - _origin;

                double t = (getNormalVector().DotProduct(_origin - ray.origin())) / getNormalVector().DotProduct(ray.direction());
                if (t <= 0.0) { // intersection behind the ray
                    return { Math::Point3D(), false };
                }
                return { ray.origin() + ray.direction() * t, true };
            };
            RayTracer::Color getColor() const override {
                return _color;
            };

            RayTracer::Ray objectRay(const Math::Point3D& objectPosition) const override {
                return RayTracer::Ray();
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
