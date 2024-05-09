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
#include "Core.hpp"

namespace RayTracer
{
    class Camera
    {
    public:
        Camera() = default;
        Camera(int width, int height) : _viewWidth(width), _viewHeight(height) {}
        Camera(const Camera &camera) : _viewWidth(camera._viewWidth), _viewHeight(camera._viewHeight), _initialPosition(nullptr) {}
        ~Camera() = default;

        Camera operator=(const Camera &camera)
        {
            if (this != &camera)
            {
                _viewWidth = camera._viewWidth;
                _viewHeight = camera._viewHeight;
                _initialPosition = nullptr;
            }
            return *this;
        }

        double _aspectRatio = 1.0;
        int _viewWidth = 100;
        int _viewHeight = 100;
        int _samples = 10;
        double _samplesScale;

        double _fovInDegrees = 90;
        Math::Point3D _position = Math::Point3D(0, 0, 0);
        Math::Point3D _focusPoint = Math::Point3D(0, 0, -1);
        Math::Vector3D _vecUp = Math::Vector3D(0, 1, 0);

        Math::Vector3D getSampleOffset()
        {
            return Math::Vector3D(Utils::randomRangedDouble(0, 1) - 0.5, Utils::randomRangedDouble(0, 1) - 0.5, 0);
        }

        RayTracer::Ray rayAround(int x, int y)
        {
            Math::Vector3D offset = getSampleOffset();
            Math::Vector3D appliedX = _pixelDeltaX * (offset.x() + x);
            Math::Vector3D appliedY = _pixelDeltaY * (y + offset.y());
            Math::Point3D pixel_sample = _firstPixelOrigin + appliedX + appliedY;

            return RayTracer::Ray(_position, pixel_sample - _position);
        }

        void initialize()
        {
            _aspectRatio = static_cast<double>(_viewWidth) / static_cast<double>(_viewHeight);
            _samplesScale = 1.0 / static_cast<double>(_samples);

            double theta = _fovInDegrees * M_PI / 180.0;
            double h = tan(theta / 2);
            double window_height = 2 * h;
            double window_width = window_height * _aspectRatio;

            Math::Vector3D w = (_position - _focusPoint).normalize();
            Math::Vector3D u = _vecUp.CrossProduct(w).normalize();
            Math::Vector3D v = w.CrossProduct(u);

            Math::Vector3D window_u = u * window_width;
            Math::Vector3D window_v = -v * window_height;

            _pixelDeltaX = window_u / _viewWidth;
            _pixelDeltaY = window_v / _viewHeight;

            Math::Point3D topLeftWin = _position - w - (window_u / 2) - (window_v / 2);
            _firstPixelOrigin = topLeftWin + (_pixelDeltaX + _pixelDeltaY) * 0.5;
        }

        void setRotationAroundFocus(double angleDegrees) {
            if (_initialPosition == nullptr)
                _initialPosition = std::make_unique<Math::Point3D>(_position);

            double angleRadians = angleDegrees * M_PI / 180.0;

            double translateX = -_focusPoint.x();
            double translateY = -_focusPoint.y();
            double translateZ = -_focusPoint.z();

            double cosAngle = cos(angleRadians);
            double sinAngle = sin(angleRadians);

            double newX = _initialPosition->x() * cosAngle + _initialPosition->z() * sinAngle;
            double newY = _initialPosition->y();
            double newZ = -_initialPosition->x() * sinAngle + _initialPosition->z() * cosAngle;

            newX += _focusPoint.x();
            newZ += _focusPoint.z();

            _position = Math::Point3D(newX, newY, newZ);
        }

    private:
        Math::Point3D _firstPixelOrigin;
        Math::Vector3D _pixelDeltaX;
        Math::Vector3D _pixelDeltaY;

        std::unique_ptr<Math::Point3D> _initialPosition;
    };
}

#endif /* !CAMERA_HPP_ */
