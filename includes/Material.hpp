/*
** EPITECH PROJECT, 2024
** RAYTRACER
** File description:
** Material
*/

#ifndef MATERIAL_HPP_
    #define MATERIAL_HPP_

    #include "Ray.hpp"
    #include "Color.hpp"
    #include "Vector3D.hpp"
    #include "HitData.hpp"
    #include "Texture.hpp"
    #include "MaterialConfig.hpp"

namespace RayTracer {
    namespace Material {

        class AMaterial {
            public:
                AMaterial() = default;
                ~AMaterial() = default;

            virtual void setup(MaterialConfig& config) {}

            virtual bool diffuse (
                const RayTracer::Ray& r_in,
                const HitData& data,
                RayTracer::Color& dissipation,
                RayTracer::Ray& diffusedRay
            ) {
                return false;
            }

            virtual RayTracer::Color emit() const {
                return RayTracer::Color(0, 0, 0);
            }
        };
    }
}


#endif /* !MATERIAL_HPP_ */
