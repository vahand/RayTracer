/*
** EPITECH PROJECT, 2024
** BS_RAYTRACER
** File description:
** Color
*/

#ifndef COLOR_HPP_
    #define COLOR_HPP_

    #include "Vector3D.hpp"

namespace RayTracer {
    class Color {
        public:
            Color() = default;
            Color(double r, double g, double b) : _r(r), _g(g), _b(b) {}
            ~Color() = default;

            double _r;
            double _g;
            double _b;

            Color operator+(const Color &color) const {
                return Color(_r + color._r, _g + color._g, _b + color._b);
            }

            Color operator-(const Color &color) const {
                return Color(_r - color._r, _g - color._g, _b - color._b);
            }

            Color operator*(const Color &color) const {
                return Color(_r * color._r, _g * color._g, _b * color._b);
            }

            Color operator*(double scalar) const {
                return Color(_r * scalar, _g * scalar, _b * scalar);
            }

            Color operator/(double scalar) const {
                return Color(_r / scalar, _g / scalar, _b / scalar);
            }

            Color& operator+=(const Color &color) {
                _r += color._r;
                _g += color._g;
                _b += color._b;
                return *this;
            }

            Color& operator-=(const Color &color) {
                _r -= color._r;
                _g -= color._g;
                _b -= color._b;
                return *this;
            }

            Color& operator*=(const Color &color) {
                _r *= color._r;
                _g *= color._g;
                _b *= color._b;
                return *this;
            }

            Color& operator*=(double scalar) {
                _r *= scalar;
                _g *= scalar;
                _b *= scalar;
                return *this;
            }

            Color& operator/=(double scalar) {
                _r /= scalar;
                _g /= scalar;
                _b /= scalar;
                return *this;
            }

            bool operator==(const Color &color) const {
                return _r == color._r && _g == color._g && _b == color._b;
            }

            Math::Vector3D getRangedColor() const {
                return Math::Vector3D(_r / 255, _g / 255, _b / 255);
            }

            void applyIntensity(double intensity) {
                _r *= intensity;
                _g *= intensity;
                _b *= intensity;
            }

            void applyColorLight(const Color &color, double intensity) {
                _r *= color._r * intensity;
                _g *= color._g * intensity;
                _b *= color._b * intensity;
            }

            void colorAverage(const Color &color) {
                _r = (_r + color._r) / 2;
                _g = (_g + color._g) / 2;
                _b = (_b + color._b) / 2;
            }

            void setBrightnessFromDistanceToLight(double distanceToLight, double intensity = 1) {
                double maxDistance = 60.0;
                double brightness = 1 - (distanceToLight / maxDistance) * intensity;
                _r *= brightness;
                _g *= brightness;
                _b *= brightness;
                if (_r < 0) _r = 0;
                if (_g < 0) _g = 0;
                if (_b < 0) _b = 0;
            }

            void copyColor(const Color &color) {
                _r = color._r;
                _g = color._g;
                _b = color._b;
                if (_r < 0) _r = 0;
                if (_g < 0) _g = 0;
                if (_b < 0) _b = 0;
                if (_r > 255) _r = 255;
                if (_g > 255) _g = 255;
                if (_b > 255) _b = 255;
            }

            bool compareColor(const Color &color) {
                return _r == color._r && _g == color._g && _b == color._b;
            }

            RayTracer::Color invert() {
                return RayTracer::Color(255 - _r, 255 - _g, 255 - _b);
            }

            double r() const { return _r; }
            double g() const { return _g; }
            double b() const { return _b; }

    };
}

#endif /* !COLOR_HPP_ */