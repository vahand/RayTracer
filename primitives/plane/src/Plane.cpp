/*
** EPITECH PROJECT, 2024
** Raytracer
** File description:
** Plane
*/

#include "Plane.hpp"

extern "C" RayTracer::IShape * initShape()
{
    std::cerr << "Plane entryPoint" << std::endl;
    return new RayTracer::Plane();
}

extern "C" int getType()
{
    return 1;
}
