/*
** EPITECH PROJECT, 2024
** Raytracer
** File description:
** Parser
*/

#include "../includes/Parser.hpp"

RayTracer::Parser::Parser(Core& core, const std::string& path) : _path(path), refCore(core)
{
    parseConfig();
}

RayTracer::Parser::~Parser()
{
}

void RayTracer::Parser::printConfig()
{
    std::cerr << " ---- CONFIG ---- " << std::endl;
    std::cerr << "Camera settings:" << std::endl;
    std::cerr << "Resolution: " << camera_settings.resolution[0] << "x" << camera_settings.resolution[1] << std::endl;
    std::cerr << "Position: [" << camera_settings.position[0] << ", " << camera_settings.position[1] << ", " << camera_settings.position[2] << "]" << std::endl;
    std::cerr << "Rotation: [" << camera_settings.rotation[0] << ", " << camera_settings.rotation[1] << ", " << camera_settings.rotation[2] << "]" << std::endl;
    std::cerr << "FOV: " << camera_settings.fov << " degrees" << std::endl;
    std::cerr << std::endl;
    std::cerr << refCore._shapes.size() << " shapes loaded" << std::endl;
    std::cerr << " ---- END CONFIG ---- " << std::endl;
}

void RayTracer::Parser::parseCameraSettings()
{
    try {
        camera_settings.resolution[0] = _cameraSection->lookup("resolution")[0];
        camera_settings.resolution[1] = _cameraSection->lookup("resolution")[1];
        camera_settings.position[0] = _cameraSection->lookup("position")[0];
        camera_settings.position[1] = _cameraSection->lookup("position")[1];
        camera_settings.position[2] = _cameraSection->lookup("position")[2];
        camera_settings.rotation[0] = _cameraSection->lookup("rotation")[0];
        camera_settings.rotation[1] = _cameraSection->lookup("rotation")[1];
        camera_settings.rotation[2] = _cameraSection->lookup("rotation")[2];
        camera_settings.fov = _cameraSection->lookup("fieldOfView");
    } catch (const libconfig::SettingNotFoundException &e) {
        throw RayTracer::Parser::ParserException("Some settings are missing or bad formatted for camera in config file \"" + _path + "\"");
    }
}

void RayTracer::Parser::parseSpheres()
{
    try {
        libconfig::Setting *spheres = &_primitivesSection->lookup("spheres");
        std::cerr << "-->> Spheres found in config file!" << std::endl;
        for (int i = 0; i < spheres->getLength(); i++) {
            libconfig::Setting &sphere = spheres->operator[](i).lookup("sphere" + std::to_string(i + 1));
            Math::Point3D center(sphere[0], sphere[1], sphere[2]);
            double radius = sphere[3];
            libconfig::Setting &color = sphere.lookup("color");
            RayTracer::Color sphereColor(color[0], color[1], color[2]);
            IShape &newShape = refCore.getNewShape(RayTracer::Core::LIBRARY_TYPE::SPHERE);
            static_cast<RayTracer::Sphere&>(newShape).setup(center, radius, sphereColor);
            refCore.addShape(newShape);
        }
    } catch (const libconfig::SettingNotFoundException &e) {
        std::cerr << "-->> No spheres found in config file!" << std::endl;
    } catch (const libconfig::SettingTypeException &e) {
        throw RayTracer::Parser::ParserException("Some settings are missing or bad formatted for spheres in config file \"" + _path + "\"");
    }
}

RayTracer::Plane::AXIS RayTracer::Parser::getPlaneAxis(const std::string& parsedAxis)
{
    if (parsedAxis == "X")
        return RayTracer::Plane::AXIS::X;
    else if (parsedAxis == "Y")
        return RayTracer::Plane::AXIS::Y;
    else if (parsedAxis == "Z")
        return RayTracer::Plane::AXIS::Z;
    else
        throw RayTracer::Parser::ParserException("Planes: Invalid axis parameter");
}

Math::Point3D RayTracer::Parser::getPlaneOrigin(double position, RayTracer::Plane::AXIS axis)
{
    if (axis == RayTracer::Plane::AXIS::X)
        return Math::Point3D(position, 0, 0);
    else if (axis == RayTracer::Plane::AXIS::Y)
        return Math::Point3D(0, position, 0);
    else if (axis == RayTracer::Plane::AXIS::Z)
        return Math::Point3D(0, 0, position);
    else
        return Math::Point3D(0, 0, 0);
}

void RayTracer::Parser::parsePlanes()
{
    try {
        libconfig::Setting *planes = &_primitivesSection->lookup("planes");
        std::cerr << "-->> Planes found in config file!" << std::endl;
        for (int i = 0; i < planes->getLength(); i++) {
            libconfig::Setting &plane = planes->operator[](i).lookup("plane" + std::to_string(i + 1));
            RayTracer:Plane::AXIS axis = getPlaneAxis(plane[0]);
            Math::Point3D origin = getPlaneOrigin(plane[1], axis);
            libconfig::Setting &color = plane.lookup("color");
            RayTracer::Color planeColor(color[0], color[1], color[2]);
            IShape &newShape = refCore.getNewShape(RayTracer::Core::LIBRARY_TYPE::PLANE);
            static_cast<RayTracer::Plane&>(newShape).setup(planeColor, origin, axis);
            refCore.addShape(newShape);
        }
    } catch (const libconfig::SettingNotFoundException &e) {
        std::cerr << "-->> No planes found in config file!" << std::endl;
    } catch (const libconfig::SettingTypeException &e) {
        throw RayTracer::Parser::ParserException("Some settings are missing or bad formatted for planes in config file \"" + _path + "\"");
    }
}

void RayTracer::Parser::parsePrimitives()
{
    parseSpheres();
    parsePlanes();
}

void RayTracer::Parser::parseConfig()
{
    try {
        _cfg.readFile(_path.c_str());

        _cameraSection = &_cfg.lookup("camera");
        if (_cameraSection != nullptr) {
            std::cerr << ">> Camera found in config file!" << std::endl;
            parseCameraSettings();
        } else {
            throw RayTracer::Parser::ParserException("Failed to find camera settings in config file \"" + _path + "\"");
        }

        _primitivesSection = &_cfg.lookup("primitives");
        if (_primitivesSection != nullptr) {
            std::cerr << ">> Primitives found in config file!" << std::endl;
            parsePrimitives();
        } else {
            throw RayTracer::Parser::ParserException("Failed to find primitives settings in config file \"" + _path + "\"");
        }
    } catch (const libconfig::FileIOException &e) {
        throw RayTracer::Parser::ParserException("Failed to read config file \"" + _path + "\"");
    } catch (const libconfig::ParseException &e) {
        throw RayTracer::Parser::ParserException("Failed to parse config file \"" + _path + "\"");
    }

}
