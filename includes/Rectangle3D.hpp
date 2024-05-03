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
            : _origin(origin), _bottomSide(bottom_side), _leftSide(left_side) {}

        Math::Point3D pointAt(double u, double v) const {
            return _origin + _bottomSide * u + _leftSide * v;
        }

    private:
        Math::Point3D _origin;
        Math::Vector3D _bottomSide;
        Math::Vector3D _leftSide;
};


#endif /* !RECTANGLE3D_HPP_ */
