/*
** EPITECH PROJECT, 2024
** BS_RAYTRACER
** File description:
** IShape
*/

#ifndef ISHAPE_HPP_
    #define ISHAPE_HPP_

    #include "Ray.hpp"
    #include "Color.hpp"
    #include "HitData.hpp"
    #include "Range.hpp"

namespace RayTracer {
    enum class ShapeType {
        SPHERE,
        PLANE
    };

    class IShape {
        public:
            IShape() = default;
            virtual ~IShape() = default;

            virtual bool hit(const RayTracer::Ray& ray, RayTracer::Range ray_range, HitData& data) const = 0;
            virtual RayTracer::Color getColor() const = 0;

            bool operator==(const IShape &shape) const {
                return _origin == shape._origin && _color == shape._color && _type == shape._type;
            }


        private:
            Math::Point3D _origin;
            RayTracer::Color _color;
            RayTracer::ShapeType _type;
    };
}

#endif /* !ISHAPE_HPP_ */
