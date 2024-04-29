/*
** EPITECH PROJECT, 2024
** Raytracer
** File description:
** Sphere
*/

#include "Sphere.hpp"

extern "C" RayTracer::IShape * initShape()
{
    std::cerr << "Sphere entryPoint" << std::endl;
    return new RayTracer::Sphere();
}

extern "C" int getType()
{
    return 0;
}
