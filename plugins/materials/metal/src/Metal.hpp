/*
** EPITECH PROJECT, 2024
** Raytracer
** File description:
** Metal
*/

#ifndef METAL_HPP_
#define METAL_HPP_

    #include "../../../../includes/AMaterial.hpp"

namespace RayTracer {
    namespace Material {

        class Metal : public AMaterial {
            public:
                Metal() = default;
                Metal(const RayTracer::Color reflectance, double fuzziness)
                    : _reflectance(reflectance), _fuzziness(fuzziness < 1 ? fuzziness : 1)
                {}

                void setup(MaterialConfig& config) override
                {
                    _reflectance = config._color;
                    _fuzziness = config._fuzziness;
                }

                bool diffuse (
                    const RayTracer::Ray& r_in,
                    const HitData& data,
                    RayTracer::Color& dissipation,
                    RayTracer::Ray& diffusedRay
                ) override {
                    auto reflected = Math::Vector3D::reflect(r_in.direction(), data.normal);
                    reflected = reflected.normalize() + (Math::Vector3D::randomUnitVector() * _fuzziness);
                    diffusedRay = RayTracer::Ray(data.point, reflected);
                    dissipation = _reflectance;
                    return (diffusedRay.direction().DotProduct(data.normal)) > 0;
                }

            private:
                RayTracer::Color _reflectance;
                double _fuzziness;
        };

    }
}

#endif /* !METAL_HPP_ */
