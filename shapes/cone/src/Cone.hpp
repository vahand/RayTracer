/*
** EPITECH PROJECT, 2024
** Raytracer
** File description:
** Cone
*/

#ifndef CONE_HPP_
#define CONE_HPP_

#include "../../../includes/IShape.hpp"

namespace RayTracer {
    class Cone : public IShape {
        public:
            Cone();
            ~Cone();

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

#endif /* !CONE_HPP_ */
