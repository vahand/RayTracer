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

    // core.addLight(light);

    // core.run();
}
