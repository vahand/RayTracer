/*
** EPITECH PROJECT, 2024
** RAYTRACER
** File description:
** Core
*/

#include "../includes/Core.hpp"
#include "../includes/Loader.hpp"

RayTracer::Core::Core(int screenWidth, int screenHeight)
{
    _screenWidth = screenWidth;
    _screenHeight = screenHeight;

    double aspectRatio = static_cast<double>(screenWidth) / static_cast<double>(screenHeight);

    Math::Point3D cameraPosition(0, 0, 0);
    Math::Vector3D camera_direction(0, 0, 1);
    Math::Vector3D camera_up(0, 1, 0);

    this->_camera = RayTracer::Camera(cameraPosition, camera_direction, camera_up);
    this->_camera._aspectRatio = aspectRatio;
    this->_camera._fovDegrees = 45;
    this->_camera._samples = 10;
    this->_camera._imageWidth = screenWidth;
    this->_camera._imageHeight = screenHeight;
    this->_camera.initialize();

    this->_maxDepth = 10;
    this->sceneBackground = RayTracer::Color(0, 0, 0);
}

void RayTracer::Core::loadLibrary(std::string path)
{
    Loader loader(path);
    if (loader._handle == nullptr)
        throw RayException("Failed to load library " + path);
    LIBRARY_TYPE type = loader.call<LIBRARY_TYPE>("getType");
    _handles[type] = loader._handle;
    std::cerr << "Library " << path << " loaded successfully" << std::endl;
}

void RayTracer::Core::loadLibrairies()
{
    try {
        for (const auto &entry : std::filesystem::directory_iterator("./lib")) {
            std::string filename = entry.path().filename().string();
            if (filename.find(".so") != std::string::npos) {
                loadLibrary("./lib/" + filename);
            }
        }
    } catch (std::filesystem::filesystem_error &e) {
        throw RayException(e.what());
    }
}

RayTracer::IShape& RayTracer::Core::getNewShape(LIBRARY_TYPE type)
{
    std::shared_ptr<void> handle = _handles[type];

    if (!isShapeType(type))
        throw RayTracer::Core::RayException("getNewShape: Must have a shape type");
    if (handle == nullptr)
        throw RayTracer::Core::RayException("No library loaded for type " + type);
    void *func_ptr = dlsym(handle.get(), "initShape");
    if (func_ptr == nullptr)
        throw RayTracer::Core::RayException(dlerror());
    RayTracer::IShape *(*func_ptr_casted)() = reinterpret_cast<RayTracer::IShape *(*)()>(func_ptr);
    std::cerr << "Shape of type " << type << " created successfully" << std::endl;
    return *func_ptr_casted();
}
