/*
** EPITECH PROJECT, 2024
** Raytracer
** File description:
** Cube
*/

#include "../includes/Cube.hpp"

extern "C" RayTracer::IShape * initShape()
{
    std::cerr << "Cube entryPoint" << std::endl;
    return new RayTracer::Cube();
}

extern "C" int getType()
{
    return 4;
}
