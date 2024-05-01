/*
** EPITECH PROJECT, 2024
** RAYTRACER
** File description:
** Material
*/

#ifndef MATERIAL_HPP_
    #define MATERIAL_HPP_

    #include "IMaterial.hpp"

namespace RayTracer {
    namespace Material {

        class AMaterial : public IMaterial {
            public:
                AMaterial() = default;
                virtual ~AMaterial() = default;

                virtual bool diffuse (
                    const RayTracer::Ray& r_in,
                    const HitData& data,
                    RayTracer::Color& dissipation,
                    RayTracer::Ray& diffusedRay
                ) override {
                    return false;
                }

                virtual RayTracer::Color emit() const override {
                    return RayTracer::Color(0, 0, 0);
                }
        };
    }
}


#endif /* !MATERIAL_HPP_ */
