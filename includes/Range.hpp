/*
** EPITECH PROJECT, 2024
** RAYTRACER
** File description:
** Range
*/

#ifndef RANGE_HPP_
    #define RANGE_HPP_

    #include <limits>

namespace RayTracer {

    class Range {
    public:
        double min, max;
        const double _infinity = std::numeric_limits<double>::infinity();

        Range() : min(+_infinity), max(-_infinity) {}
        Range(double min, double max) : min(min), max(max) {}

        double getSize() const {
            return max - min;
        }

        bool contain(double x) const {
            return min <= x && x <= max;
        }

        bool around(double x) const {
            return min < x && x < max;
        }

        double bound(double x) const {
            if (x < min) return min;
            if (x > max) return max;
            return x;
        }

    };
}

// const interval interval::empty    = interval(+infinity, -infinity);
// const interval interval::universe = interval(-infinity, +infinity);

#endif /* !RANGE_HPP_ */
