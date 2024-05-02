/*
** EPITECH PROJECT, 2024
** Raytracer
** File description:
** IMaterial
*/

#ifndef IMATERIAL_HPP_
#define IMATERIAL_HPP_

    #include "Ray.hpp"
    #include "Color.hpp"
    #include "Vector3D.hpp"
    #include "HitData.hpp"
    #include "Texture.hpp"
    #include "MaterialConfig.hpp"

namespace RayTracer {
    namespace Material {
        class IMaterial {
            public:
                IMaterial() = default;
                virtual ~IMaterial() = default;

                virtual void setup(MaterialConfig& config) = 0;

                virtual bool diffuse (
                    const RayTracer::Ray& r_in,
                    const HitData& data,
                    RayTracer::Color& dissipation,
                    RayTracer::Ray& diffusedRay
                ) = 0;

                virtual RayTracer::Color emit() const = 0;
            protected:
            private:
        };
    }
}

#endif /* !IMATERIAL_HPP_ */
