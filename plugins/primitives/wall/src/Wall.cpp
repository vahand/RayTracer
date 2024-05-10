/*
** EPITECH PROJECT, 2024
** Raytracer
** File description:
** Wall
*/

#include "../includes/Wall.hpp"

extern "C" RayTracer::IShape * initShape()
{
    std::cerr << "Plane entryPoint" << std::endl;
    return new RayTracer::Wall();
}

extern "C" int getType()
{
    return 5;
}
