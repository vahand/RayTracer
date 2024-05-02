/*
** EPITECH PROJECT, 2024
** Raytracer
** File description:
** LightDiffuse
*/

#ifndef LIGHTDIFFUSE_HPP_
#define LIGHTDIFFUSE_HPP_

    #include "../../../../includes/AMaterial.hpp"

namespace RayTracer {
    namespace Material {
        class LightDiffuse : public AMaterial {
            public:
                LightDiffuse() = default;
                LightDiffuse(std::shared_ptr<RayTracer::Texture::ATexture> texture)
                    : _texture(texture) {}
                LightDiffuse(const RayTracer::Color emitColor)
                    : _texture(std::make_shared<RayTracer::Texture::Solid>(emitColor)) {}

                void setup(MaterialConfig& config) override
                {
                    _texture = std::make_shared<RayTracer::Texture::Solid>(config._color);
                }

                RayTracer::Color emit() const override {
                    return _texture->get();
                }

            private:
                std::shared_ptr<RayTracer::Texture::ATexture> _texture;
        };
    }
}

#endif /* !LIGHTDIFFUSE_HPP_ */
