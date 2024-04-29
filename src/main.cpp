/*
** EPITECH PROJECT, 2024
** RAYTRACER
** File description:
** main
*/

#include "../includes/Core.hpp"
#include "../primitives/sphere/src/Sphere.hpp"
#include "../primitives/plane/src/Plane.hpp"
#include "../includes/Parser.hpp"
#include "../includes/Light.hpp"

int main()
{
    RayTracer::Core core(400, 400);
    core.loadLibrairies();

    RayTracer::Parser parser(core, "./configs/subject_config");
    parser.printConfig();

    double sphereRadius = 2.0;

    // RayTracer::Color sphereColor(255, 0, 0);
    // Math::Point3D sphereCenter(5, 5, 30);
    // RayTracer::Sphere sphere(sphereCenter, sphereRadius, sphereColor);

    // RayTracer::Color sphereColor2(0, 255, 0);
    // Math::Point3D sphereCenter2(5, 5, 20);
    // RayTracer::Sphere sphere2(sphereCenter2, sphereRadius, sphereColor2);

    // RayTracer::Color sphereColor3(0, 0, 255);
    // Math::Point3D sphereCenter3(30, 100, 50);
    // RayTracer::Sphere sphere3(sphereCenter3, 100, sphereColor3);

    // core.addShape(sphere);
    // core.addShape(sphere2);
    // core.addShape(sphere3);

    // RayTracer::Plane plane;
    // RayTracer::Color planeColor(0, 255, 0);
    // Math::Point3D planeOrigin(0, 15, 0);
    // plane.setup(planeColor, planeOrigin, RayTracer::Plane::AXIS::Y);
    // core.addShape(plane);

    core.run();
}
