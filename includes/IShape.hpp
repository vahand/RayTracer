/*
** EPITECH PROJECT, 2024
** BS_RAYTRACER
** File description:
** IShape
*/

#ifndef ISHAPE_HPP_
    #define ISHAPE_HPP_

namespace RayTracer {
    enum ShapeType {
        SPHERE,
        PLANE
    };
}

    #include "Ray.hpp"
    #include "Color.hpp"
    #include "HitData.hpp"
    #include "Range.hpp"
    #include "ShapeConfig.hpp"

namespace RayTracer {
    class IShape {
        public:
            IShape() = default;
            virtual ~IShape() = default;

            virtual bool hit(const RayTracer::Ray& ray, RayTracer::Range ray_range, HitData& data) const = 0;
            virtual void setup(const RayTracer::ShapeConfig& config) = 0;
            virtual void translate(const Math::Vector3D& translation) = 0;
            virtual void rotate(const Math::Vector3D& rotation) = 0;

            virtual const std::string& getName() const = 0;
            virtual void setName(const std::string& name) = 0;

    };
}

#endif /* !ISHAPE_HPP_ */
