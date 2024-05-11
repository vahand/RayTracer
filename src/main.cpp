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

static std::vector<std::string> getVecOptions(int ac, char **av, int index)
{
    std::vector<std::string> options;
    while (index < ac && av[index][0] != '-') {
        options.push_back(av[index]);
        index++;
    }
    return options;
}

static std::vector<std::string> getOptionValues(int ac, char **av, const std::string &option, const std::string &shortOption = "")
{
    for (int i = 0; i < ac; i++)
    {
        if (std::string(av[i]) == option)
            return getVecOptions(ac, av, i + 1);
        if (shortOption != "" && std::string(av[i]) == shortOption)
            return getVecOptions(ac, av, i + 1);
    }
    return std::vector<std::string>();
}


int main(int ac, char **av)
{
    try
    {
        std::unique_ptr<Graphics::AGraphicals> display;
        std::vector<std::string> scenePath;
        bool fileConfig = false;

        if (hasOption(ac, av, "-h") || hasOption(ac, av, "--help"))
        {
            std::cerr << "Usage: ./raytracer [options] > [image_path]" << std::endl;
            std::cerr << "\nOptions:" << std::endl;
            std::cerr << "\t-h, --help:\t Display this help message" << std::endl;
            std::cerr << "\t-s, --scene <scene_path>:\t Load a scene (required)" << std::endl;
            std::cerr << "\t-t, --threads:\t Set the numbers of threads used for rendering" << std::endl;
            std::cerr << "\t-g, --gui:\t Enable the GUI" << std::endl;
            std::cerr << "\t-q, --quality <samples_count>:\t Override numbers of samples (quality)" << std::endl;
            return 0;
        }

        bool threadsOption = hasOption(ac, av, "-t") || hasOption(ac, av, "--threads");
        bool guiOption = hasOption(ac, av, "-g") || hasOption(ac, av, "--gui");
        bool sceneOption = hasOption(ac, av, "-s") || hasOption(ac, av, "--scene");
        bool qualityOption = hasOption(ac, av, "-q") || hasOption(ac, av, "--quality");

        int threadsCount = 1;
        if (threadsOption)
            threadsCount = std::stoi(static_cast<const char *>(getOptionValue(ac, av, "--threads", "-t")));

        if (!sceneOption) {
            std::cerr << RED << BOLD << "Error: " << RESET << "No scene file provided, see --help for more informations" << std::endl;
            return 84;
        } else {
            scenePath = getOptionValues(ac, av, "--scene", "-s");
        }

        std::shared_ptr<RayTracer::Core> core = std::make_shared<RayTracer::Core>(400, 400);
        std::shared_ptr<Workers> workers = std::make_shared<Workers>(threadsCount, 400, 400);
        core->loadLibrairies();

        RayTracer::FileManager fileManager(*core);
        for (const auto &path : scenePath)
            if (fileManager.addFileConfigPath(path))
                fileConfig = true;
        if (!fileConfig) {
            std::cerr << RED << BOLD << "Error: " << RESET << "No valid scene file provided" << std::endl;
            return 84;
        }
        fileManager.loadFileConfig();

        if (guiOption) {
            display = std::make_unique<Graphics::SFML::SFMLDisplay>();
            display->setup(core, workers);
            display->createWindow(1280, 720, "RayTracer", std::make_shared<RayTracer::FileManager>(fileManager));
        }

        if (qualityOption) {
            int quality = std::stoi(static_cast<const char *>(getOptionValue(ac, av, "--quality", "-q")));
            if (quality < 1 || quality > 1000000) {
                std::cerr << RED << BOLD << "Error: " << RESET << "Quality must be between 1 and 1M" << std::endl;
                return 84;
            }
            core->_camera._samples = quality;
        }

        // RayTracer::Parser parser(*core, "./configs/mathis_config3");
        RayTracer::Parser parser(*core, "./configs/room_config");
        parser.printConfig();

        // auto texture_chessboard = std::make_shared<RayTracer::Texture::ChessBoard>(5, RayTracer::Color(255, 255, 255), RayTracer::Color(0, 128, 255));
        // auto material_chessboard = std::make_shared<RayTracer::Material::Lambertian>(texture_chessboard);

        std::cerr << "Rendering settings: " << std::endl;
        std::cerr << " - Width: " << core->_camera._viewWidth << std::endl;
        std::cerr << " - Height: " << core->_camera._viewHeight << std::endl;
        std::cerr << " - Quality (samples): " << core->_camera._samples << std::endl;
        std::cerr << " - Max depth: " << core->_maxDepth << std::endl;
        std::cerr << " - Threads: " << workers->getThreadsCount() << std::endl;

        workers->initialize(*core);

        if (guiOption) {
            std::cerr << "[GUI] Successfully initialized" << std::endl;
            while (display->isWindowOpen()) {
                display->renderAll();
            }
        } else {
            workers->render(*core);
        }
    }
    catch (const std::exception &e)
    {
        std::clog << RED << BOLD << "An error occured: " << RESET << e.what() << std::endl;
        return 84;
    }
}
