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
    #include "Utils.hpp"

namespace RayTracer
{
    class Camera {
        public:
            Camera() = default;
            Camera(const Math::Point3D& origin, const Math::Vector3D direction, const Math::Vector3D up)
                : _origin(origin), _direction(direction), _up(up) {};
            Camera(const Camera &camera) : _origin(camera._origin), _direction(camera._direction), _up(camera._up) {};
            ~Camera() = default;

            Camera& operator=(const Camera &camera) {
                if (this != &camera) {
                    _origin = camera._origin;
                    _direction = camera._direction;
                    _up = camera._up;
                }
                return *this;
            }

            RayTracer::Ray rayAt(double u, double v) const {
                return RayTracer::Ray(_origin, _screen.pointAt(u, v) - _origin);
            }

            RayTracer::Ray rayAround(double u, double v) const {
                auto offset = squaredSample(_pixelDelta_x.x(), _pixelDelta_y.y());
                Math::Point3D neighbor_pixel = _screen.pointAt(u + offset.x(), v + offset.y());

                return RayTracer::Ray(_origin, neighbor_pixel - _origin);
            }

            Math::Vector3D squaredSample(double pixelDelta_x, double pixelDelta_y) const {
                return Math::Vector3D(
                    Utils::randomRangedDouble(pixelDelta_x) - (0.5 * pixelDelta_x),
                    Utils::randomRangedDouble(pixelDelta_y) - (0.5 * pixelDelta_y),
                    0
                );
            }

            void printVector(const Math::Vector3D &vec, std::string name = "Vector") {
                std::cerr << name << ": (" << vec.x() << ", " << vec.y() << ", " << vec.z() << ")" << std::endl;
            }

            void printPoint(const Math::Point3D &point, std::string name = "Point") {
                std::cerr << name << ": (" << point.x() << ", " << point.y() << ", " << point.z() << ")" << std::endl;
            }

            void initialize() {
                double theta = _fov_degrees * M_PI / 180;
                double half_height = tan(theta / 2);
                double half_width = _aspect_ratio * half_height;
                this->_samples = _samples;
                this->_samples_scale = 1.0 / _samples;

                Math::Vector3D offset = _direction.normalize();
                Math::Vector3D upper = _up.CrossProduct(offset);
                Math::Vector3D leftCross = offset.CrossProduct(upper);

                _screen_center = _origin + offset;
                _bottom_side = (upper * half_width) * 2;
                _left_side = (leftCross * half_height) * 2;

                _screen = Rectangle3D(_screen_center, _bottom_side, _left_side);

                _pixelDelta_x = _bottom_side * (1.0 / _image_width);
                _pixelDelta_y = _left_side * (1.0 / _image_height);

                std::cerr << "Camera initialized" << std::endl;
                printPoint(_origin, "Origin");
                printVector(_direction, "Direction");
                printVector(_up, "Up");
                printPoint(_screen_center, "Screen Center");
                printVector(_bottom_side, "Bottom Side");
                printVector(_left_side, "Left Side");
                printVector(_pixelDelta_x, "Pixel Delta X");
                printVector(_pixelDelta_y, "Pixel Delta Y");
            }


            double _samples_scale;
            double _samples;
            Math::Point3D _origin;

            Math::Vector3D _direction;
            Math::Vector3D _up;
            double _aspect_ratio;
            double _fov_degrees;
            double _image_width;
            double _image_height;

            Math::Vector3D _pixelDelta_x;
            Math::Vector3D _pixelDelta_y;
        private:
            Rectangle3D _screen;

            Math::Point3D _screen_center;
            Math::Vector3D _bottom_side;
            Math::Vector3D _left_side;
    };
}

#endif /* !CAMERA_HPP_ */
