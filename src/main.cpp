/*
** EPITECH PROJECT, 2024
** RAYTRACER
** File description:
** main
*/

#include "../includes/Core.hpp"
#include "../shapes/sphere/src/Sphere.hpp"

int main()
{
    RayTracer::Core core(400, 400);

    Math::Point3D lightPosition(0, 10, 0);
    double lightIntensity = 1.0;
    Math::Vector3D lightColor(1, 1, 1);
    RayTracer::Light light(lightPosition, lightIntensity, lightColor);

    Math::Point3D sphereCenter(5, 5, 30);
    double sphereRadius = 2.0;
    RayTracer::Color sphereColor(255, 0, 0);
    RayTracer::Sphere sphere(sphereCenter, sphereRadius, sphereColor);

    core.loadLibrairies();

    core.addShape(sphere);
    core.addShape(core.getNewShape(RayTracer::Core::LIBRARY_TYPE::SPHERE));
    core.addLight(light);

    core.run();
}
