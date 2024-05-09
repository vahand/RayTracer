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
#include "../includes/FileManager.hpp"

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

        RayTracer::FileManager fileManager(*core);
        fileManager.addFileConfigPath("./configs/new_parser_config");
        fileManager.addFileConfigPath("./configs/new_parser_config2");
        fileManager.loadFileConfig();

        if (guiOption)
        {
            display = std::make_unique<Graphics::SFML::SFMLDisplay>();
            display->setup(core, workers);
            display->createWindow(1280, 720, "RayTracer");
        }

        // auto texture_chessboard = std::make_shared<RayTracer::Texture::ChessBoard>(5, RayTracer::Color(255, 255, 255), RayTracer::Color(0, 128, 255));
        // auto material_chessboard = std::make_shared<RayTracer::Material::Lambertian>(texture_chessboard);

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
