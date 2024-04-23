/*
** EPITECH PROJECT, 2024
** Raytracer
** File description:
** Cone
*/

#include "Cone.hpp"

extern "C" RayTracer::IShape * initShape()
{
    std::cerr << "Cone entryPoint" << std::endl;
    return new RayTracer::Cone();
}

extern "C" int getType()
{
    return 2;
}
