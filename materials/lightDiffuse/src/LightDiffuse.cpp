/*
** EPITECH PROJECT, 2024
** Raytracer
** File description:
** LightDiffuse
*/

#include "LightDiffuse.hpp"

extern "C" RayTracer::Material::AMaterial * initMaterial()
{
    std::cerr << "LightDiffuse entryPoint" << std::endl;
    return new RayTracer::Material::LightDiffuse();
}

extern "C" int getType()
{
    return 1002;
}
