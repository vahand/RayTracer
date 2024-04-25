/*
** EPITECH PROJECT, 2024
** RAYTRACER
** File description:
** Utils
*/

#ifndef UTILS_HPP_
    #define UTILS_HPP_

    #include <cstdlib>
    #include <chrono>
    #include <vector>
    #include <memory>

class Utils {
    public:

        static double randomRangedDouble(double x) {
            return (2 * x * randomOneDouble()) - x;
        }

        static double randomOneDouble() {
            return rand() / (RAND_MAX + 1.0);
        }

        Utils() = default;
        ~Utils() = default;

    protected:
    private:
};

#endif /* !UTILS_HPP_ */
