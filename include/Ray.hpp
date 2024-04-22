/*
** EPITECH PROJECT, 2024
** BS_RAYTRACER
** File description:
** Ray
*/

#ifndef RAY_HPP_
    #define RAY_HPP_

    #include "Point3D.hpp"

namespace RayTracer
{
    class Ray {
        public:
            Ray() = default;
            Ray(const Math::Point3D &origin, const Math::Vector3D &direction) : _origin(origin), _direction(direction) {};
            Ray(const Ray &ray) : _origin(ray._origin), _direction(ray._direction) {};
            Ray(Ray &&ray) noexcept : _origin(ray._origin), _direction(ray._direction) {
                ray._origin = Math::Point3D();
                ray._direction = Math::Vector3D();
            }
            ~Ray() = default;

            Math::Point3D _origin;
            Math::Vector3D _direction;

            Ray& operator=(const Ray &ray) {
                if (this != &ray) {
                    _origin = ray._origin;
                    _direction = ray._direction;
                }
                return *this;
            }

            Ray& operator=(Ray &&ray) noexcept {
                if (this != &ray) {
                    _origin = ray._origin;
                    _direction = ray._direction;
                    ray._origin = Math::Point3D();
                    ray._direction = Math::Vector3D();
                }
                return *this;
            }

            Math::Point3D origin() const { return _origin; }
            Math::Vector3D direction() const { return _direction; }

        protected:
        private:
    };
}

#endif /* !RAY_HPP_ */
