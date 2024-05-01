/*
** EPITECH PROJECT, 2024
** Raytracer
** File description:
** Lambertian
*/

#include "Lambertian.hpp"

extern "C" RayTracer::Material::IMaterial * initMaterial()
{
    std::cerr << "Lambertian entryPoint" << std::endl;
    return new RayTracer::Material::Lambertian();
}

extern "C" int getType()
{
    return 1000;
}
