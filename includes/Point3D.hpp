/*
** EPITECH PROJECT, 2024
** BS_RAYTRACER
** File description:
** Point3D
*/

#ifndef POINT3D_HPP_
    #define POINT3D_HPP_

    #include "Vector3D.hpp"

namespace Math {
    class Point3D {
        public:
            Point3D() : X(0), Y(0), Z(0) {};
            Point3D(double x, double y, double z) : X(x), Y(y), Z(z) {};
            Point3D(const Point3D &point) : X(point.X), Y(point.Y), Z(point.Z) {};
            Point3D(Point3D &&point) noexcept : X(point.X), Y(point.Y), Z(point.Z) {
                point.X = 0;
                point.Y = 0;
                point.Z = 0;
            }
            ~Point3D() = default;

            Point3D& operator=(const Point3D &point) {
                if (this != &point) {
                    X = point.X;
                    Y = point.Y;
                    Z = point.Z;
                }
                return *this;
            }

            Point3D& operator=(Point3D &&point) noexcept {
                if (this != &point) {
                    X = point.X;
                    Y = point.Y;
                    Z = point.Z;
                    point.X = 0;
                    point.Y = 0;
                    point.Z = 0;
                }
                return *this;
            }

            Point3D operator+(const Point3D &point) {
                return Point3D(X + point.X, Y + point.Y, Z + point.Z);
            }

            Vector3D operator-(const Point3D &point) {
                return Vector3D(X - point.X, Y - point.Y, Z - point.Z);
            }

            Point3D operator*(const Point3D &point) {
                return Point3D(X * point.X, Y * point.Y, Z * point.Z);
            }

            Point3D operator/(const Point3D &point) {
                return Point3D(X / point.X, Y / point.Y, Z / point.Z);
            }

            Point3D operator+(const Math::Vector3D &vec) {
                return Point3D(X + vec.X, Y + vec.Y, Z + vec.Z);
            }

            Point3D operator+(const Math::Vector3D& vec) const {
                return Point3D(X + vec.x(), Y + vec.y(), Z + vec.z());
            }

            bool operator==(const Point3D &point) const {
                return X == point.X && Y == point.Y && Z == point.Z;
            }

            double X;
            double Y;
            double Z;

            double x() const { return X; }
            double y() const { return Y; }
            double z() const { return Z; }

        protected:
        private:
    };

}

#endif /* !POINT3D_HPP_ */
