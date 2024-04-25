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

    Math::Point3D cameraPosition(0, 0, 0);
    Math::Vector3D camera_direction(0, 0, 1);
    Math::Vector3D camera_up(0, 1, 0);

    this->_camera = RayTracer::Camera(cameraPosition, camera_direction, camera_up);
    this->_camera._aspect_ratio = static_cast<double>(screenWidth / screenHeight);
    this->_camera._fov_degrees = 30;
    this->_camera._samples = 100;
    this->_camera._image_width = screenWidth;
    this->_camera._image_height = screenHeight;
    this->_camera.initialize();
}

void RayTracer::Core::writeColor(RayTracer::Color &color)
{
    static const RayTracer::Range colorRange(0.0, 255.0);
    int r = colorRange.bound(color._r);
    int g = colorRange.bound(color._g);
    int b = colorRange.bound(color._b);

    std::cout << r << ' ' << g << ' ' << b << '\n';
}

RayTracer::Color getRayColor(const RayTracer::Ray& r, const RayTracer::Core& core, int limit = 10) {
    if (limit <= 0)
        return RayTracer::Color(0, 0, 0);

    HitData data;
    double infinity = std::numeric_limits<double>::infinity();
    if (core.hit(r, RayTracer::Range(0.001, infinity), data)) {
        Math::Vector3D direction = data.normal + Math::Vector3D::randomUnitVector();
        return getRayColor(RayTracer::Ray(data.point, direction), core, limit - 1) * 0.5;
    }

    Math::Vector3D unit_dir = r.direction().normalize();
    auto a = 0.5 * (unit_dir.y() + 1.0);
    Math::Vector3D vec = RayTracer::Color(255, 255, 255).getRangedColor() * (1.0 - a) + RayTracer::Color(0.5*255.0, 0.7*255.0, 1.0*255.0).getRangedColor() * a;
    return RayTracer::Color(vec.x() * 255.999, vec.y() * 255.999, vec.z() * 255.999);
}

void RayTracer::Core::run()
{
    std::cout << "P3\n" << this->_screenWidth << ' ' << this->_screenHeight << "\n255\n";
    auto startTime = std::chrono::high_resolution_clock::now();

    auto iterationTime = std::chrono::high_resolution_clock::now();
    for (int y = 0; y < this->_screenHeight; y++) {
        displayProgress(y, this->_screenHeight, iterationTime, startTime);
        iterationTime = std::chrono::high_resolution_clock::now();
        for (int x = 0; x < this->_screenWidth; x++) {
            double u = static_cast<double>(x) / this->_screenWidth;
            double v = static_cast<double>(y) / this->_screenHeight;

            RayTracer::Color finalColor(0, 0, 0);
            for (int sample = 0; sample < this->_camera._samples; sample++) {
                RayTracer::Ray ray = this->_camera.rayAround(u, v);
                finalColor += getRayColor(ray, *this);
            }
            finalColor *= this->_camera._samples_scale;
            writeColor(finalColor);

        }
    }
    auto endTime = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> elapsed = endTime - startTime;

    displayProgress(this->_screenHeight, this->_screenHeight, iterationTime, startTime);
    std::cerr << "\nDone! - Total Lines: " << this->_screenHeight << std::endl;
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
    DIR *dir;
    struct dirent *ent;
    if ((dir = opendir("./lib")) != NULL) {
        while ((ent = readdir(dir)) != NULL) {
            std::string filename = ent->d_name;
            if (filename.find(".so") != std::string::npos) {
                loadLibrary("./lib/" + filename);
            }
        }
        closedir(dir);
    } else {
        throw RayException("Failed to open directory");
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
