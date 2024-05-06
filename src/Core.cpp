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

    this->_camera = RayTracer::Camera(screenWidth, screenHeight);

    this->_camera._samples = 2000;

    this->_camera._fovInDegrees = 90;
    this->_camera._position = Math::Point3D(0, 6, -30);
    this->_camera._focusPoint = Math::Point3D(0, 2, 0);
    this->_camera._vecUp = Math::Vector3D(0, 1, 0);

    this->_camera.initialize();

    this->_maxDepth = 50;
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
    try
    {
        for (const auto &entry : std::filesystem::directory_iterator("./lib"))
        {
            std::string filename = entry.path().filename().string();
            if (filename.find(".so") != std::string::npos)
            {
                loadLibrary("./lib/" + filename);
            }
        }
    }
    catch (std::filesystem::filesystem_error &e)
    {
        throw RayException(e.what());
    }
}

RayTracer::IShape &RayTracer::Core::getNewShape(LIBRARY_TYPE type)
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

// std::shared_ptr<RayTracer::Material::IMaterial> RayTracer::Core::getNewMaterial(LIBRARY_TYPE type)
// {
//     std::shared_ptr<void> handle = _handles[type];

//     if (!isMaterialType(type))
//         throw RayTracer::Core::RayException("getNewMaterial: Must have a material type");
//     if (handle == nullptr)
//         throw RayTracer::Core::RayException("No library found for type " + type);
//     void *func_ptr = dlsym(handle.get(), "initMaterial");
//     if (func_ptr == nullptr)
//         throw RayTracer::Core::RayException(dlerror());
//     RayTracer::Material::IMaterial *(*func_ptr_casted)() = reinterpret_cast<RayTracer::Material::IMaterial *(*)()>(func_ptr);
//     std::cerr << "Material of type " << type << " created succesfully" << std::endl;
//     return std::make_shared<RayTracer::Material::AMaterial>(*func_ptr_casted());
// }

// void RayTracer::Core::addMaterial(RayTracer::Material::IMaterial &material, LIBRARY_TYPE type, MaterialConfig& config, const std::string& name)
// {
//     if (type == LIBRARY_TYPE::LAMBERTIAN)
//         static_cast<RayTracer::Material::Lambertian&>(material).setup(config);
//     else if (type == LIBRARY_TYPE::METAL)
//         static_cast<RayTracer::Material::Metal&>(material).setup(config);
//     else if (type == LIBRARY_TYPE::LIGHT_DIFFUSE)
//         static_cast<RayTracer::Material::LightDiffuse&>(material).setup(config);
//     _loadedMaterials[name] = std::make_shared<RayTracer::Material::AMaterial>(material);
// }

void RayTracer::Core::loadNewMaterial(LIBRARY_TYPE type, MaterialConfig& config, const std::string& name)
{
    std::shared_ptr<void> handle = _handles[type];

    if (!isMaterialType(type))
        throw RayTracer::Core::RayException("getNewMaterial: Must have a material type");
    if (handle == nullptr)
        throw RayTracer::Core::RayException("No library found for type " + type);
    void *func_ptr = dlsym(handle.get(), "initMaterial");
    if (func_ptr == nullptr)
        throw RayTracer::Core::RayException(dlerror());
    RayTracer::Material::IMaterial *(*func_ptr_casted)() = reinterpret_cast<RayTracer::Material::IMaterial *(*)()>(func_ptr);
    std::cerr << "Material of type " << type << " created succesfully" << std::endl;
    if (type == LIBRARY_TYPE::LAMBERTIAN) {
        _loadedMaterials[name] = std::make_shared<RayTracer::Material::Lambertian>();
        _loadedMaterials[name]->setup(config);
    }
    else if (type == LIBRARY_TYPE::METAL) {
        _loadedMaterials[name] = std::make_shared<RayTracer::Material::Metal>();
        _loadedMaterials[name]->setup(config);
    }
    else if (type == LIBRARY_TYPE::LIGHT_DIFFUSE) {
        _loadedMaterials[name] = std::make_shared<RayTracer::Material::LightDiffuse>();
        _loadedMaterials[name]->setup(config);
    }
    // RayTracer::Material::AMaterial material = *func_ptr_casted();
    // if (type == LIBRARY_TYPE::LAMBERTIAN)
    //     static_cast<RayTracer::Material::Lambertian&>(material).setup(config);
    // else if (type == LIBRARY_TYPE::METAL)
    //     static_cast<RayTracer::Material::Metal&>(material).setup(config);
    // else if (type == LIBRARY_TYPE::LIGHT_DIFFUSE)
    //     static_cast<RayTracer::Material::LightDiffuse&>(material).setup(config);
    // _loadedMaterials[name] = std::make_shared<RayTracer::Material::AMaterial>(material);
    // _loadedMaterials[name]->setup(config);
}
