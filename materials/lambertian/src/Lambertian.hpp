/*
** EPITECH PROJECT, 2024
** Raytracer
** File description:
** Lambertian
*/

#ifndef LAMBERTIAN_HPP_
#define LAMBERTIAN_HPP_

    #include "../../../includes/AMaterial.hpp"

namespace RayTracer {
    namespace Material {

        class Lambertian : public AMaterial {
            public:
                Lambertian() = default;
                Lambertian(const RayTracer::Color reflectance)
                    : _texture(std::make_shared<RayTracer::Texture::Solid>(reflectance)) {}

                void setup(MaterialConfig& config) override
                {
                    _texture = std::make_shared<RayTracer::Texture::Solid>(config._color);
                }

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

    }
}


#endif /* !LAMBERTIAN_HPP_ */
