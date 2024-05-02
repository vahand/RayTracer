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
                double theta = _fovDegrees * M_PI / 180;
                double half_height = tan(theta / 2);
                double half_width = _aspectRatio * half_height;
                this->_samplesScale = 1.0 / _samples;

                Math::Vector3D offset = _direction.normalize();
                Math::Vector3D upper = _up.CrossProduct(offset);
                Math::Vector3D leftCross = offset.CrossProduct(upper);

                _screenCenter = _origin + offset;
                _bottomSide = (upper * half_width) * 2;
                _leftSide = (leftCross * half_height) * 2;

                _screen = Rectangle3D(_screenCenter, _bottomSide, _leftSide);

                _pixelDelta_x = _bottomSide * (1.0 / _imageWidth);
                _pixelDelta_y = _leftSide * (1.0 / _imageHeight);

                std::cerr << "Camera initialized" << std::endl;
            }

            double _samplesScale;
            double _samples;
            Math::Point3D _origin;

            Math::Vector3D _direction;
            Math::Vector3D _up;
            double _aspectRatio;
            double _fovDegrees;
            double _imageWidth;
            double _imageHeight;

            Math::Vector3D _pixelDelta_x;
            Math::Vector3D _pixelDelta_y;

        private:
            Rectangle3D _screen;

            Math::Point3D _screenCenter;
            Math::Vector3D _bottomSide;
            Math::Vector3D _leftSide;
    };
}

#endif /* !CAMERA_HPP_ */
