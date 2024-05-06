/*
** EPITECH PROJECT, 2024
** Raytracer
** File description:
** LightDiffuse
*/

#include "../includes/LightDiffuse.hpp"

extern "C" RayTracer::Material::IMaterial * initMaterial()
{
    std::cerr << "LightDiffuse entryPoint" << std::endl;
    return new RayTracer::Material::LightDiffuse();
}

extern "C" int getType()
{
    return 1002;
}
