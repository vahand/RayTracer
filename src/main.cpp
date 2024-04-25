/*
** EPITECH PROJECT, 2024
** RAYTRACER
** File description:
** main
*/

#include "../includes/Core.hpp"
#include "../shapes/sphere/src/Sphere.hpp"
#include "../shapes/plane/src/Plane.hpp"
#include "../includes/Parser.hpp"

int main()
{
    RayTracer::Core core(400, 400);
    core.loadLibrairies();

    RayTracer::Parser parser(core, "./configs/subject_config");
    parser.printConfig();

    // Math::Point3D lightPosition(0, 10, 0);
    // double lightIntensity = 1.0;
    // Math::Vector3D lightColor(1, 1, 1);
    // RayTracer::Light light(lightPosition, lightIntensity, lightColor);

    // Math::Point3D sphereCenter(5, 5, 30);
    // double sphereRadius = 2.0;
    // RayTracer::Color sphereColor(255, 0, 0);
    // RayTracer::Sphere sphere(sphereCenter, sphereRadius, sphereColor);


    // RayTracer::Plane plane;
    // RayTracer::Color planeColor(0, 255, 0);
    // Math::Point3D planeOrigin(0, 15, 0);
    // plane.setup(planeColor, planeOrigin, RayTracer::Plane::AXIS::Y);

    // core.addShape(sphere);
    // core.addShape(plane);
    // core.addLight(light);

    // core.run();
}
