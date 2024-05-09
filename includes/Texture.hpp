/*
** EPITECH PROJECT, 2024
** RAYTRACER
** File description:
** Texture
*/

#ifndef TEXTURE_HPP_
    #define TEXTURE_HPP_

    #include "Ray.hpp"
    #include "Color.hpp"
    #include "Vector3D.hpp"
    #include "HitData.hpp"

namespace RayTracer {
    namespace Texture {
        class ATexture {
            public:
                ATexture() = default;
                ~ATexture() = default;

                virtual RayTracer::Color get(double x, double y, const Math::Point3D &intersectionPoint) const = 0;

            protected:
            private:
        };

        class Solid : public ATexture {
            public:
                Solid(const RayTracer::Color reflectance) : _reflectance(reflectance) {}
                Solid(double red, double green, double blue) : Solid(RayTracer::Color(red, green, blue)) {}
                ~Solid() = default;

                RayTracer::Color get(double x, double y, const Math::Point3D &intersectionPoint) const override {
                    (void)x;
                    (void)y;
                    (void)intersectionPoint;
                    return _reflectance;
                }

            private:
                RayTracer::Color _reflectance;
        };

        class ChessBoard : public ATexture {
            public:
                ChessBoard(double scale, std::shared_ptr<ATexture> primary, std::shared_ptr<ATexture> secondary)
                    : _scale(1.0 / scale), _primary(primary), _secondary(secondary) {}

                ChessBoard(double scale, const RayTracer::Color& primaryColor, const RayTracer::Color& secondaryColor)
                    : _scale(1.0 / scale),
                      _primary(std::make_shared<Solid>(primaryColor)),
                      _secondary(std::make_shared<Solid>(secondaryColor)) {}

                RayTracer::Color get(double x, double y, const Math::Point3D &intersectionPoint) const override {
                    auto x_ = int(std::floor(_scale * (x + intersectionPoint.x())));
                    auto y_ = int(std::floor(_scale * (y + intersectionPoint.y())));
                    auto z_ = int(std::floor(_scale * intersectionPoint.z()));

                    if ((x_ + y_ + z_) % 2 == 0)
                        return _primary->get(x, y, intersectionPoint);
                    return _secondary->get(x, y, intersectionPoint);
                }

                private:
                    double _scale;
                    std::shared_ptr<ATexture> _primary;
                    std::shared_ptr<ATexture> _secondary;

        };
    }
}

#endif /* !TEXTURE_HPP_ */
