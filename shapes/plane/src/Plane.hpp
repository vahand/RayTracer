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
            Plane();
            ~Plane();

            HitResult hits(const RayTracer::Ray &ray) override {
                return HitResult();
            };
            RayTracer::Color getColor() const override {
                return RayTracer::Color();
            };

            RayTracer::Ray objectRay(const Math::Point3D& objectPosition) const override {
                return RayTracer::Ray();
            };

        protected:
        private:
    };
}

#endif /* !PLANE_HPP_ */
