/*
** EPITECH PROJECT, 2024
** BS_RAYTRACER
** File description:
** Camera
*/

#ifndef CAMERA_HPP_
    #define CAMERA_HPP_

    #include "Rectangle3D.hpp"
    #include "Ray.hpp"
    #include <cmath>

namespace RayTracer
{
    class Camera {
        public:
            Camera() = default;
            Camera(const Math::Point3D& origin, const Math::Vector3D& direction, const Math::Vector3D& up,
                double aspect_ratio, double fov_degrees) : _origin(origin)
            {
                double theta = fov_degrees * M_PI / 180; // in randians
                double half_height = tan(theta / 2);
                double half_width = aspect_ratio * half_height;

                Math::Vector3D w = direction.normalize();
                Math::Vector3D u = up.CrossProduct(w);
                Math::Vector3D v = w.CrossProduct(u);

                Math::Point3D screen_center = _origin + w;
                Math::Vector3D bottom_side = (u * half_width) * 2;
                Math::Vector3D left_side = (v * half_height) * 2;

                _screen = Rectangle3D(screen_center, bottom_side, left_side);
            }

            RayTracer::Ray ray(double u, double v) const {
                return RayTracer::Ray(_origin, _screen.pointAt(u, v) - _origin);
            }

        private:
            Math::Point3D _origin;
            Rectangle3D _screen;
    };
}

#endif /* !CAMERA_HPP_ */
