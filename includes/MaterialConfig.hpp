/*
** EPITECH PROJECT, 2024
** Raytracer
** File description:
** MaterialConfig
*/

#ifndef MATERIALCONFIG_HPP_
#define MATERIALCONFIG_HPP_

    #include "Color.hpp"

namespace RayTracer {
    class MaterialConfig {
        public:
            MaterialConfig() = default;
            ~MaterialConfig() = default;

            double _fuzziness;
            RayTracer::Color _color;
            int _type;

        protected:
        private:
    };
}

#endif /* !MATERIALCONFIG_HPP_ */
