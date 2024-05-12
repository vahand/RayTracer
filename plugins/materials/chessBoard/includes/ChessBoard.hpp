/*
** EPITECH PROJECT, 2024
** Raytracer
** File description:
** ChessBoard
*/

#ifndef CHESSBOARD_HPP_
    #define CHESSBOARD_HPP_

    #include "../../../../includes/AMaterial.hpp"


namespace RayTracer {
    namespace Material {
        class ChessBoard : public AMaterial {
            public:
                ChessBoard() = default;
                ChessBoard(const RayTracer::Color color1, const RayTracer::Color color2)
                    : _texture(std::make_shared<RayTracer::Texture::ChessBoard>(5, color1, color2)),
                      _color1(color1), _color2(color2) {}

                void setup(MaterialConfig& config) override {
                    _texture = std::make_shared<RayTracer::Texture::ChessBoard>(5, config._color1, config._color2);
                    _color1 = config._color1;
                    _color2 = config._color2;
                }

                bool diffuse (
                    const RayTracer::Ray& r_in,
                    const HitData& data,
                    RayTracer::Color& dissipation,
                    RayTracer::Ray& diffusedRay
                ) override {
                    auto diffuse_dir = Math::Vector3D::randomUnit() + data.normal;
                    auto limit = 1e-8;

                    if (std::fabs(diffuse_dir.x()) <= limit
                     && std::fabs(diffuse_dir.y()) <= limit
                     && std::fabs(diffuse_dir.z()) <= limit)
                        diffuse_dir = data.normal;
                    diffusedRay = RayTracer::Ray(data.point, diffuse_dir);
                    dissipation = _texture->get(data.x, data.y, data.point);
                    return true;
                }

            protected:
            private:
                RayTracer::Color _color1;
                RayTracer::Color _color2;
                std::shared_ptr<RayTracer::Texture::ATexture> _texture;
        };
    }
}

#endif /* !CHESSBOARD_HPP_ */
