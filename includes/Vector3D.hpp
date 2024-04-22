/*
** EPITECH PROJECT, 2024
** BS_RAYTRACER
** File description:
** Vector3D
*/

#ifndef VECTOR3D_HPP_
    #define VECTOR3D_HPP_

    #include <stdio.h>
    #include <iostream>
    #include <string>
    #include <vector>
    #include <cmath>

namespace Math {
    class Vector3D {
        public:
            Vector3D() : X(0), Y(0), Z(0) {};
            Vector3D(double x, double y, double z) : X(x), Y(y), Z(z) {};
            Vector3D(const Vector3D &vec) : X(vec.X), Y(vec.Y), Z(vec.Z) {};
            Vector3D(Vector3D &&vec) noexcept : X(vec.X), Y(vec.Y), Z(vec.Z) {
                vec.X = 0;
                vec.Y = 0;
                vec.Z = 0;
            }
            ~Vector3D() = default;

            Vector3D& operator=(const Vector3D &vec) {
                if (this != &vec) {
                    X = vec.X;
                    Y = vec.Y;
                    Z = vec.Z;
                }
                return *this;
            }

            Vector3D& operator=(Vector3D &&vec) noexcept {
                if (this != &vec) {
                    X = vec.X;
                    Y = vec.Y;
                    Z = vec.Z;
                    vec.X = 0;
                    vec.Y = 0;
                    vec.Z = 0;
                }
                return *this;
            }

            Vector3D operator*(double scalar) const {
                return Vector3D(X * scalar, Y * scalar, Z * scalar);
            }

            Vector3D operator*(const double &val) {
                return Vector3D(X * val, Y * val, Z * val);
            }

            Vector3D operator/(const double &val) {
                return Vector3D(X / val, Y / val, Z / val);
            }

            Vector3D& operator*=(const double &val) {
                X *= val;
                Y *= val;
                Z *= val;
                return *this;
            }

            Vector3D& operator/=(const double &val) {
                X /= val;
                Y /= val;
                Z /= val;
                return *this;
            }

            Vector3D operator+(const Vector3D &vec) {
                return Vector3D(X + vec.X, Y + vec.Y, Z + vec.Z);
            }

            Vector3D operator-(const Vector3D &vec) {
                return Vector3D(X - vec.X, Y - vec.Y, Z - vec.Z);
            }

            Vector3D operator*(const Vector3D &vec) {
                return Vector3D(X * vec.X, Y * vec.Y, Z * vec.Z);
            }

            Vector3D operator/(const Vector3D &vec) {
                return Vector3D(X / vec.X, Y / vec.Y, Z / vec.Z);
            }

            Vector3D& operator+=(const Vector3D &vec) {
                X += vec.X;
                Y += vec.Y;
                Z += vec.Z;
                return *this;
            }

            Vector3D& operator-=(const Vector3D &vec) {
                X -= vec.X;
                Y -= vec.Y;
                Z -= vec.Z;
                return *this;
            }

            Vector3D& operator*=(const Vector3D &vec) {
                X *= vec.X;
                Y *= vec.Y;
                Z *= vec.Z;
                return *this;
            }

            Vector3D& operator/=(const Vector3D &vec) {
                X /= vec.X;
                Y /= vec.Y;
                Z /= vec.Z;
                return *this;
            }

            double X;
            double Y;
            double Z;

            double x() const { return X; }
            double y() const { return Y; }
            double z() const { return Z; }

            double DotProduct(const Vector3D &vec) {
                return X * vec.X + Y * vec.Y + Z * vec.Z;
            }

            Vector3D CrossProduct(const Vector3D& other) const {
                double x_result = y() * other.z() - z() * other.y();
                double y_result = z() * other.x() - x() * other.z();
                double z_result = x() * other.y() - y() * other.x();
                return Vector3D(x_result, y_result, z_result);
            }

            Vector3D normalize() const {
                double length = sqrt(this->lengthSquared());
                return Vector3D(x() / length, y() / length, z() / length);
            }

            double lengthSquared() const {
                return X * X + Y * Y + Z * Z;
            }

            double magnitude() const {
                return sqrt(lengthSquared());
            }

        protected:
        private:
    };
}

#endif /* !VECTOR3D_HPP_ */
