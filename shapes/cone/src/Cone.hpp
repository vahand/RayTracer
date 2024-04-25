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
            Cone() = default;
            ~Cone() = default;

            bool hit(const RayTracer::Ray& ray, RayTracer::Range ray_range, HitData& data) const override
            {
                (void)ray;
                (void)ray_range;
                (void)data;
                return false;
            };

            RayTracer::Color getColor() const override {
                return RayTracer::Color();
            };

        protected:
        private:
    };
}

#endif /* !CONE_HPP_ */
