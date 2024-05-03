/*
** EPITECH PROJECT, 2024
** Raytracer
** File description:
** Cylinder
*/

#include "../includes/Cylinder.hpp"

extern "C" RayTracer::IShape * initShape()
{
    std::cerr << "Cylinder entryPoint" << std::endl;
    return new RayTracer::Cylinder();
}

extern "C" int getType()
{
    return 1;
}
