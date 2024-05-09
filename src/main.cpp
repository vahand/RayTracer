/*
** EPITECH PROJECT, 2024
** RAYTRACER
** File description:
** main
*/

#include "../includes/Core.hpp"
#include "../plugins/primitives/sphere/includes/Sphere.hpp"
#include "../plugins/primitives/plane/includes/Plane.hpp"
#include "../plugins/primitives/cube/includes/Cube.hpp"
#include "../plugins/primitives/cone/includes/Cone.hpp"
#include "../plugins/primitives/cylinder/includes/Cylinder.hpp"
#include "../plugins/primitives/cone/includes/Cone.hpp"
#include "../plugins/primitives/cylinder/includes/Cylinder.hpp"
#include "../plugins/materials/lambertian/includes/Lambertian.hpp"
#include "../plugins/materials/metal/includes/Metal.hpp"
#include "../plugins/materials/lightDiffuse/includes/LightDiffuse.hpp"
#include "../includes/Parser.hpp"
#include "../includes/Light.hpp"

#include "../includes/Workers.hpp"
#include "../includes/SFMLDisplay.hpp"

static bool hasOption(int ac, char **av, const std::string &option)
{
    for (int i = 0; i < ac; i++)
    {
        if (std::string(av[i]) == option)
            return true;
    }
    return false;
}

static void *getOptionValue(int ac, char **av, const std::string &option, const std::string &shortOption = "")
{
    for (int i = 0; i < ac; i++)
    {
        if (std::string(av[i]) == option)
            return av[i + 1];
        if (shortOption != "" && std::string(av[i]) == shortOption)
            return av[i + 1];
    }
    return nullptr;
}

int main(int ac, char **av)
{
    try
    {
        std::unique_ptr<Graphics::AGraphicals> display;

        if (hasOption(ac, av, "-h") || hasOption(ac, av, "--help"))
        {
            std::cerr << "Usage: ./raytracer [options] > [image_path]" << std::endl;
            std::cerr << "\nOptions:" << std::endl;
            std::cerr << "\t-h, --help:\t Display this help message" << std::endl;
            std::cerr << "\t-t, --threads:\t Set the numbers of threads used for rendering" << std::endl;
            std::cerr << "\t-g, --gui:\t Enable the GUI" << std::endl;
            return 0;
        }

        bool threadsOption = hasOption(ac, av, "-t") || hasOption(ac, av, "--threads");
        int threadsCount = 1;
        if (threadsOption)
        {
            threadsCount = std::stoi(static_cast<const char *>(getOptionValue(ac, av, "--threads", "-t")));
        }

        bool guiOption = hasOption(ac, av, "-g") || hasOption(ac, av, "--gui");

        std::shared_ptr<RayTracer::Core> core = std::make_shared<RayTracer::Core>(400, 400);
        std::shared_ptr<Workers> workers = std::make_shared<Workers>(threadsCount, 400, 400);
        core->loadLibrairies();

        if (guiOption)
        {
            display = std::make_unique<Graphics::SFML::SFMLDisplay>();
            display->setup(core, workers);
            display->createWindow(1280, 720, "RayTracer");
        }

        // RayTracer::Parser parser(*core, "./configs/mathis_config3");
        // parser.printConfig();

        double sphereRadius = 2.0;

        auto material_ground = std::make_shared<RayTracer::Material::Lambertian>(RayTracer::Color(255, 255, 0));
        auto material_center = std::make_shared<RayTracer::Material::Lambertian>(RayTracer::Color(0, 255, 255));
        auto material_cube = std::make_shared<RayTracer::Material::Lambertian>(RayTracer::Color(0, 0, 255));
        auto material_cube_wall = std::make_shared<RayTracer::Material::Lambertian>(RayTracer::Color(255, 128, 64));

        auto material_red_metal = std::make_shared<RayTracer::Material::Metal>(RayTracer::Color(255, 0, 0), 0.0);
        auto material_light = std::make_shared<RayTracer::Material::LightDiffuse>(RayTracer::Color(255, 255, 255));
        auto material_gray_metal = std::make_shared<RayTracer::Material::Metal>(RayTracer::Color(128, 128, 128), 0.5);

        auto texture_chessboard = std::make_shared<RayTracer::Texture::ChessBoard>(5, RayTracer::Color(255, 255, 255), RayTracer::Color(0, 128, 255));
        auto material_chessboard = std::make_shared<RayTracer::Material::Lambertian>(texture_chessboard);

        Math::Point3D sphere_left_pos(0, 2, 0);
        RayTracer::Sphere sphere_left(sphere_left_pos, sphereRadius, material_red_metal);
        Math::Point3D sphere_right_pos(10, 2, 0);
        RayTracer::Sphere sphere_right(sphere_right_pos, sphereRadius, material_light);

        Math::Point3D plane_position(0, 0, 0);
        RayTracer::Plane plane(plane_position, RayTracer::ShapeConfig::AXIS::Y, material_chessboard);

        Math::Point3D sphere_light4_pos(-5, 2, -20);
        RayTracer::Sphere sphere_light4(sphere_light4_pos, sphereRadius, material_light);
        Math::Point3D cylinder_position(-8, 0, 8);
        RayTracer::Cylinder cylinder(cylinder_position, 2, 5, material_ground, RayTracer::ShapeConfig::AXIS::Y);
        Math::Point3D sky_pos(0, 60, 0);
        RayTracer::Sphere sky(sky_pos, 30, material_light);

        // Math::Point3D box_ground_position(0, 0, -10);
        // Math::Point3D box_wall_left_pos(-10, 0, 0);
        // Math::Point3D box_wall_right_pos(10, 0, 0);
        // Math::Point3D box_wall_back_pos(0, 0, 0);

        // RayTracer::Cube box_ground(box_ground_position, 20, 1, 20, material_cube);
        // RayTracer::Cube box_wall_left(box_wall_left_pos, 1, 20, 20, material_cube);
        // RayTracer::Cube box_wall_right(box_wall_right_pos, 1, 20, 20, material_cube);
        // RayTracer::Cube box_wall_back(box_wall_back_pos, 20, 20, 1, material_cube);

        Math::Point3D cone_position(5, 0, 5);
        RayTracer::Cone cone(cone_position, 2, 5, material_center, RayTracer::ShapeConfig::AXIS::Y, 45);

        core->addShape(sphere_light4);
        core->addShape(plane);
        core->addShape(sky);

        cylinder.rotate(Math::Vector3D(0, 0, -45));
        plane.rotate(Math::Vector3D(0, 0, 0));
        cone.rotate(Math::Vector3D(0, 0, 45));
        core->addShape(cone);
        core->addShape(plane);
        core->addShape(sphere_left);
        core->addShape(sphere_right);

        // core->addShape(box_ground);
        // core->addShape(box_wall_left);
        // core->addShape(box_wall_right);
        // core->addShape(box_wall_back);

        core->addShape(cylinder);

        std::cerr << "Rendering settings: " << std::endl;
        std::cerr << " - Width: " << core->_camera._viewWidth << std::endl;
        std::cerr << " - Height: " << core->_camera._viewHeight << std::endl;
        std::cerr << " - Quality (samples): " << core->_camera._samples << std::endl;
        std::cerr << " - Max depth: " << core->_maxDepth << std::endl;
        std::cerr << " - Threads: " << workers->getThreadsCount() << std::endl;

        workers->initialize(*core);

        if (guiOption)
        {
            std::cerr << "Rendering with GUI" << std::endl;
            while (display->isWindowOpen())
            {
                display->renderAll();
            }
        }
        else
        {
            workers->render(*core);
        }
    }
    catch (const std::exception &e)
    {
        std::clog << RED << BOLD << "An error occured: " << RESET << e.what() << std::endl;
        return 84;
    }
}
