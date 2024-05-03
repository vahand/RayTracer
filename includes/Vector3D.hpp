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
    #include "Utils.hpp"

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

            Vector3D operator-() const { return Vector3D(-X, -Y, -Z); }

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

            Vector3D operator/(const Vector3D &vec) {
                return Vector3D(X / vec.X, Y / vec.Y, Z / vec.Z);
            }

            Math::Vector3D operator/(const double &val) {
                return Vector3D(this->x() / val, this->y() / val, this->z() / val);
            }

            Vector3D operator*(const Vector3D &vec) {
                return Vector3D(X * vec.X, Y * vec.Y, Z * vec.Z);
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

            Vector3D divByDouble(const double &val) const {
                return Vector3D(X / val, Y / val, Z / val);
            }

            double X;
            double Y;
            double Z;

            inline double x() const { return X; }
            inline double y() const { return Y; }
            inline double z() const { return Z; }

            double DotProduct(const Vector3D &vec) {
                return X * vec.X + Y * vec.Y + Z * vec.Z;
            }

            Vector3D CrossProduct(const Vector3D& other) const {
                double x_result = y() * other.z() - z() * other.y();
                double y_result = z() * other.x() - x() * other.z();
                double z_result = x() * other.y() - y() * other.x();
                return Vector3D(x_result, y_result, z_result);
            }

            double length() const {
                return sqrt(lengthSquared());
            }

            static Vector3D unit_vector(const Vector3D& v) {
                return v.divByDouble(v.length());
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

            static Vector3D random(double scale = 0.005) {
                return Vector3D(Utils::randomScaledDouble(scale), Utils::randomScaledDouble(scale), Utils::randomScaledDouble(scale));
            }

            static Vector3D randomUnitSphereVector(double scale = 0.005) {
                while (true) {
                    Vector3D randomVector = Vector3D::random(scale);
                    if (randomVector.lengthSquared() < 1)
                        return randomVector;
                }
            }

            static Vector3D randomUnitVector(double scale = 0.005) {
                return randomUnitSphereVector(scale).normalize();
            }

            static Vector3D randomHemisphere(const Vector3D& normal) {
                Vector3D onSphere = randomUnitVector();
                return onSphere.DotProduct(normal) > 0.0 ? onSphere : -onSphere;
            }

            static Vector3D reflect(const Vector3D& v, const Vector3D& n) {
                Vector3D tmp_v = v;
                Vector3D tmp_n = n;
                return tmp_v - (tmp_n * (tmp_v.DotProduct(tmp_n) * 2));
            }

        protected:
        private:
    };
}

#endif /* !VECTOR3D_HPP_ */
