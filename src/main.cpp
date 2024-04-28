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
#include "../includes/Light.hpp"

#include "../includes/Workers.hpp"

int main()
{
    RayTracer::Core core(400, 400);
    Workers workers(14, 400, 400);
    core.loadLibrairies();

    // RayTracer::Parser parser(core, "./configs/subject_config");
    // parser.printConfig();

    double sphereRadius = 2.0;

    auto material_ground = std::make_shared<RayTracer::Material::Lambertian>(RayTracer::Color(210, 210, 20));
    auto material_center = std::make_shared<RayTracer::Material::LightDiffuse>(RayTracer::Color(20, 200, 200));
    auto material_left   = std::make_shared<RayTracer::Material::Metal>(RayTracer::Color(48, 48, 48), 0.0);
    auto material_right  = std::make_shared<RayTracer::Material::Metal>(RayTracer::Color(128, 128, 50), 0.8);

    Math::Point3D sphere_left_pos(2.5, 8, 20);
    RayTracer::Sphere sphere_left(sphere_left_pos, sphereRadius, material_left);

    Math::Point3D sphere_center_pos(7.5, 8, 20);
    RayTracer::Sphere sphere_center(sphere_center_pos, sphereRadius, material_center);

    Math::Point3D sphere_right_pos(12.5, 8, 20);
    RayTracer::Sphere sphere_right(sphere_right_pos, sphereRadius, material_right);

    Math::Point3D sphere_ground_pos(7.5, 108, 0);
    RayTracer::Sphere sphere_ground(sphere_ground_pos, 100, material_ground);

    core.addShape(sphere_ground);
    core.addShape(sphere_center);
    core.addShape(sphere_left);
    core.addShape(sphere_right);

    // RayTracer::Plane plane;
    // RayTracer::Color planeColor(0, 255, 0);
    // Math::Point3D planeOrigin(0, 15, 0);
    // plane.setup(planeColor, planeOrigin, RayTracer::Plane::AXIS::Y);
    // core.addShape(plane);

    std::cerr << "Rendering settings: " << std::endl;
    std::cerr << " - Width: " << core._camera._image_width << std::endl;
    std::cerr << " - Height: " << core._camera._image_height << std::endl;
    std::cerr << " - Quality (samples): " << core._camera._samples << std::endl;
    std::cerr << " - Max depth: " << core._maxDepth << std::endl;
    std::cerr << " - Threads: " << workers.getThreadsCount() << std::endl;

    workers.initialize(core);
    workers.render(core);
}
