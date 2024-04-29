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
            Cylinder() = default;
            ~Cylinder() = default;

            bool hit(const RayTracer::Ray& ray, RayTracer::Range ray_range, HitData& data) const override
            {
                (void)ray;
                (void)ray_range;
                (void)data;
                return false;
            };

            RayTracer::Color getColor() const override
            {
                return RayTracer::Color();
            };

        protected:
        private:
    };
}

#endif /* !CYLINDER_HPP_ */
