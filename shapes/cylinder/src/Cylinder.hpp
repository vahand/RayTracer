/*
** EPITECH PROJECT, 2024
** Raytracer
** File description:
** Cylinder
*/

#ifndef CYLINDER_HPP_
#define CYLINDER_HPP_

#include "../../../includes/IShape.hpp"

namespace RayTracer {
    class Cylinder : public IShape {
        public:
            Cylinder();
            ~Cylinder();

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

#endif /* !CYLINDER_HPP_ */
