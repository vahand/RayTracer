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

                virtual RayTracer::Color get() const = 0;

            protected:
            private:
        };

        class Solid : public ATexture {
            public:
                Solid(const RayTracer::Color& reflectance) : _reflectance(reflectance) {}
                Solid(double red, double green, double blue) : Solid(RayTracer::Color(red, green, blue)) {}
                ~Solid() = default;

                RayTracer::Color get() const override {
                    return _reflectance;
                }

            private:
                RayTracer::Color _reflectance;
        };
    }
}

#endif /* !TEXTURE_HPP_ */
