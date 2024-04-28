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

namespace RayTracer {
    namespace Material {

        class AMaterial {
            public:
                AMaterial() = default;
                ~AMaterial() = default;

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

        class Lambertian : public AMaterial {
            public:
                Lambertian(const RayTracer::Color& reflectance)
                    : _texture(std::make_shared<RayTracer::Texture::Solid>(reflectance)) {}

                bool diffuse (
                    const RayTracer::Ray& r_in,
                    const HitData& data,
                    RayTracer::Color& dissipation,
                    RayTracer::Ray& diffusedRay
                ) override {
                    auto diffuse_dir = Math::Vector3D::randomUnitVector() + data.normal;
                    auto limit = 1e-8;

                    if (std::fabs(diffuse_dir.x()) < limit
                     && std::fabs(diffuse_dir.y()) < limit
                     && std::fabs(diffuse_dir.z()) < limit)
                        diffuse_dir = data.normal;
                    diffusedRay = RayTracer::Ray(data.point, diffuse_dir);
                    dissipation = _texture->get();
                    return true;
                }

            private:
                std::shared_ptr<RayTracer::Texture::ATexture> _texture;
        };

        class Metal : public AMaterial {
            public:
                Metal(const RayTracer::Color& reflectance, double fuzziness)
                    : _reflectance(reflectance), _fuzziness(fuzziness < 1 ? fuzziness : 1)
                {}

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

        class LightDiffuse : public AMaterial {
            public:
                LightDiffuse(std::shared_ptr<RayTracer::Texture::ATexture> texture)
                    : _texture(texture) {}
                LightDiffuse(const RayTracer::Color& emitColor)
                    : _texture(std::make_shared<RayTracer::Texture::Solid>(emitColor)) {}

                RayTracer::Color emit() const override {
                    return _texture->get();
                }

            private:
                std::shared_ptr<RayTracer::Texture::ATexture> _texture;
        };

    }
}


#endif /* !MATERIAL_HPP_ */
