/*
** EPITECH PROJECT, 2024
** BS_RAYTRACER
** File description:
** Rectangle3D
*/

#ifndef RECTANGLE3D_HPP_
    #define RECTANGLE3D_HPP_

    #include "Point3D.hpp"
    #include "Vector3D.hpp"

class Rectangle3D {
    public:
        Rectangle3D() = default;
        Rectangle3D(const Math::Point3D& origin, const Math::Vector3D& bottom_side, const Math::Vector3D& left_side)
            : _origin(origin), _bottom_side(bottom_side), _left_side(left_side) {}

        Math::Point3D pointAt(double u, double v) const {
            return _origin + _bottom_side * u + _left_side * v;
        }

    private:
        Math::Point3D _origin;
        Math::Vector3D _bottom_side;
        Math::Vector3D _left_side;
};


#endif /* !RECTANGLE3D_HPP_ */
