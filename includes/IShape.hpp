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

namespace RayTracer {
    struct HitResult {
        Math::Point3D intersectionPoint;
        bool hit;
    };

    enum class ShapeType {
        SPHERE,
        PLANE
    };

    class IShape {
        public:
            IShape() = default;
            virtual ~IShape() = default;

            virtual HitResult hits(const RayTracer::Ray &ray) = 0;
            virtual RayTracer::Color getColor() const = 0;

            virtual RayTracer::Ray objectRay(const Math::Point3D& objectPosition) const = 0;

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
