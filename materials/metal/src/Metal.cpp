/*
** EPITECH PROJECT, 2024
** Raytracer
** File description:
** Metal
*/

#include "Metal.hpp"

extern "C" RayTracer::Material::IMaterial * initMaterial()
{
    std::cerr << "Metal entryPoint" << std::endl;
    return new RayTracer::Material::Metal();
}

extern "C" int getType()
{
    return 1001;
}
