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

    #define CYAN "\033[0;36m"
    #define RED "\033[0;31m"
    #define GREEN "\033[0;32m"
    #define YELLOW "\033[0;33m"
    #define GRAY "\033[0;90m"
    #define BLUE "\033[0;34m"
    #define MAGENTA "\033[0;35m"
    #define WHITE "\033[0;37m"
    #define BOLD "\033[1m"
    #define UNDERLINE "\033[4m"
    #define ITALIC "\033[3m"
    #define BLINK "\033[5m"
    #define RESET "\033[0m"

namespace RayTracer {
    class IShape {
        public:
            class ShapeException : public std::exception {
                public:
                    ShapeException(const std::string& message) : _message(message) {}
                    const char* what() const noexcept override { return _message.c_str(); }

                private:
                    std::string _message;
            };
            IShape() = default;
            virtual ~IShape() = default;

            virtual bool hit(const RayTracer::Ray& ray, RayTracer::Range ray_range, HitData& data) const = 0;
            virtual void setup(const RayTracer::ShapeConfig& config) = 0;
            virtual bool hasAllParameters(const RayTracer::ShapeConfig& config) const = 0;
            virtual void translate(const Math::Vector3D& translation) = 0;
            virtual void rotate(const Math::Vector3D& rotation) = 0;
            virtual void degreeToRadian(Math::Vector3D &angle) = 0;
            virtual const std::string& getName() const = 0;
            virtual void setName(const std::string& name) = 0;

    };
}

#endif /* !ISHAPE_HPP_ */
