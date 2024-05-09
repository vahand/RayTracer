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
    std::cerr << "Position: [" << camera_settings.position.X  << " ; " << camera_settings.position.Y << " ; " << camera_settings.position.Z << "]" << std::endl;
    std::cerr << "FOV: " << camera_settings.fov << " degrees" << std::endl;
    std::cerr << "Samples: " << camera_settings.samples << std::endl;
    std::cerr << "Max depth: " << camera_settings.maxDepth << std::endl;
    std::cerr << "Focus point: [" << camera_settings.focusPoint.X << " ; " << camera_settings.focusPoint.Y << " ; " << camera_settings.focusPoint.Z << "]" << std::endl;
    std::cerr << "Scene background: [" << camera_settings.sceneBackGround.r() << " ; " << camera_settings.sceneBackGround.g() << " ; " << camera_settings.sceneBackGround.b() << "]" << std::endl;
    std::cerr << std::endl;
    std::cerr << "Materials:" << std::endl;
    std::cerr << _loadedMaterials.size() << " materials loaded" << std::endl;
    printMaterials();
    std::cerr << std::endl;
    std::cerr << "Primitives:" << std::endl;
    std::cerr << refCore._shapes.size() << " shapes loaded" << std::endl;
    refCore.printShape();
    std::cerr << std::endl;
    // std::cerr << "Lights:" << std::endl;
    // std::cerr << refCore._lights.size() << " lights loaded" << std::endl;
    // refCore.printLight();
    // std::cerr << std::endl;
    std::cerr << " ---- END CONFIG ---- " << std::endl;
}

void RayTracer::Parser::parseCameraOptionalParameters()
{
    try {
        camera_settings.fov = _cameraSection->lookup("fieldOfView");
        camera_settings.samples = _cameraSection->lookup("samples");
        camera_settings.maxDepth = _cameraSection->lookup("maxDepth");
        libconfig::Setting &focusPoint = _cameraSection->lookup("focusPoint");
        camera_settings.focusPoint = Math::Point3D(focusPoint[0], focusPoint[1], focusPoint[2]);
        libconfig::Setting &sceneBackground = _cameraSection->lookup("sceneBackground");
        camera_settings.sceneBackGround = RayTracer::Color(sceneBackground[0], sceneBackground[1], sceneBackground[2]);
    } catch (const libconfig::SettingNotFoundException &e) {
        std::cerr << BOLD << CYAN << "INFO: " << RESET << CYAN << "Some optional camera parameters are not defined in config file \"" << _path << "\"" << RESET << std::endl;
    } catch (const libconfig::SettingTypeException &e) {
        throw RayTracer::Parser::ParserException("Some settings are bad formatted for camera in config file \"" + _path + "\"");
    }
}

void RayTracer::Parser::parseCameraSettings()
{
    try {
        camera_settings.resolution[0] = _cameraSection->lookup("resolution")[0];
        camera_settings.resolution[1] = _cameraSection->lookup("resolution")[1];
        libconfig::Setting &position = _cameraSection->lookup("position");
        camera_settings.position = Math::Point3D(position[0], position[1], position[2]);
        parseCameraOptionalParameters();
    } catch (const libconfig::SettingNotFoundException &e) {
        throw RayTracer::Parser::ParserException("Some mandatory settings are missing for camera in config file \"" + _path + "\"");
    } catch (const libconfig::SettingTypeException &e) {
        throw RayTracer::Parser::ParserException("Some settings are bad formatted for camera in config file \"" + _path + "\"");
    }
}

std::string RayTracer::Parser::getPrimitiveName(libconfig::Setting &primitiveSetting)
{
    std::string name = primitiveSetting.getName();
    if (name.empty())
        throw RayTracer::Parser::ParserException("Primitives: Invalid name parameter");
    if (_parsedPrimitives.size() > 0) {
        for (auto &parsedPrimitive : _parsedPrimitives) {
            if (parsedPrimitive == name)
                throw RayTracer::Parser::ParserException("Primitives: Duplicate name parameter");
        }
    }
    _parsedPrimitives.push_back(name);
    return name;
}
std::string RayTracer::Parser::getLightName(libconfig::Setting &lightSetting)
{
    std::string name = lightSetting.getName();
    if (name.empty())
        throw RayTracer::Parser::ParserException("Lights: Invalid name parameter");
    if (_parsedLights.size() > 0) {
        for (auto &parsedLight : _parsedLights) {
            if (parsedLight == name)
                throw RayTracer::Parser::ParserException("Lights: Duplicate name parameter");
        }
    }
    _parsedLights.push_back(name);
    return name;
}

std::string RayTracer::Parser::getMaterialName(libconfig::Setting &materialSetting)
{
    std::string name = materialSetting.getName();
    if (name.empty())
        throw RayTracer::Parser::ParserException("Materials: Invalid name parameter");
    if (_parsedMaterials.size() > 0) {
        for (auto &parsedMaterial : _parsedMaterials) {
            if (parsedMaterial == name)
                throw RayTracer::Parser::ParserException("Materials: Duplicate name parameter");
        }
    }
    _parsedMaterials.push_back(name);
    return name;
}

RayTracer::ShapeConfig::AXIS RayTracer::Parser::getParsedAxis(const std::string& parsedAxis)
{
    if (parsedAxis == "X")
        return RayTracer::ShapeConfig::AXIS::X;
    else if (parsedAxis == "Y")
        return RayTracer::ShapeConfig::AXIS::Y;
    else if (parsedAxis == "Z")
        return RayTracer::ShapeConfig::AXIS::Z;
    else
        throw RayTracer::Parser::ParserException("Invalid axis parameter");
}

Math::Point3D RayTracer::Parser::getPlaneOrigin(double position, RayTracer::ShapeConfig::AXIS axis)
{
    if (axis == RayTracer::ShapeConfig::AXIS::X)
        return Math::Point3D(position, 0, 0);
    else if (axis == RayTracer::ShapeConfig::AXIS::Y)
        return Math::Point3D(0, position, 0);
    else if (axis == RayTracer::ShapeConfig::AXIS::Z)
        return Math::Point3D(0, 0, position);
    else
        return Math::Point3D(0, 0, 0);
}

void RayTracer::Parser::parseMainAmbientFactor()
{
    try {
        _mainAmbientFactor = _lightsSection->lookup("ambient");
        std::cerr << "-->> Ambient light factor found in config file!"<< std::endl;
        _mainAmbientFactorIsDefined = true;
    }  catch (const libconfig::SettingNotFoundException &e){
        std::cerr << "-->> Ambient light factor is not defined in config file" << std::endl;
    }
}
void RayTracer::Parser::parseMainDiffuseFactor()
{
    try {
        _mainDiffuseFactor = _lightsSection->lookup("diffuse");
        std::cerr << "-->> Diffuse light factor found in config file!"<< std::endl;
        _mainDiffuseFactorIsDefined = true;
    }  catch (const libconfig::SettingNotFoundException &e){
        std::cerr << "-->> Diffuse light factor is not defined in config file" << std::endl;
    }
}

double RayTracer::Parser::getAmbientFactor(libconfig::Setting &pointLight)
{
    try {
        return pointLight.lookup("ambient");
    } catch (const libconfig::SettingNotFoundException &e) {
        if (_mainAmbientFactorIsDefined)
            return _mainAmbientFactor;
        else
            throw RayTracer::Parser::ParserException("Ambient factor is not defined for light in config file \"" + _path + "\"");
    }
}
double RayTracer::Parser::getDiffuseFactor(libconfig::Setting &pointLight)
{
    try {
        return pointLight.lookup("diffuse");
    } catch (const libconfig::SettingNotFoundException &e) {
        if (_mainDiffuseFactorIsDefined)
            return _mainDiffuseFactor;
        else
            throw RayTracer::Parser::ParserException("Diffuse factor is not defined for light in config file \"" + _path + "\"");
    }
}

void RayTracer::Parser::parsePointLight()
{
    try {
        libconfig::Setting *pointLights = &_lightsSection->lookup("point");
        std::cerr << "-->> Point lights found in config file!" << std::endl;
        for (int i = 0; i < pointLights->getLength(); i++) {
            libconfig::Setting &subPointLight = pointLights->operator[](i);
            libconfig::Setting &pointLight = subPointLight.operator[](0);
            const std::string &name = getLightName(pointLight);
            Math::Point3D position(pointLight[0], pointLight[1], pointLight[2]);
            double ambient = getAmbientFactor(pointLight);
            double diffuse = getDiffuseFactor(pointLight);
            std::unique_ptr<RayTracer::Light> newLight = std::make_unique<RayTracer::Light>(position, ambient, diffuse, RayTracer::Light::LightType::POINT);
            newLight->setName(name);
            refCore.addLight(*newLight);
        }
    } catch (const libconfig::SettingNotFoundException &e) {
        std::cerr << "-->> No point lights found in config file!" << std::endl;
    } catch (const libconfig::SettingTypeException &e) {
        throw RayTracer::Parser::ParserException("Some settings are missing or bad formatted for point lights in config file \"" + _path + "\"");
    }
}

void RayTracer::Parser::parseLights()
{
    parseMainAmbientFactor();
    parseMainDiffuseFactor();
    parsePointLight();
}

RayTracer::Core::LIBRARY_TYPE getMaterialTypeFromString(std::string& typeStr)
{
    if (typeStr == "lambertian")
        return RayTracer::Core::LIBRARY_TYPE::LAMBERTIAN;
    else if (typeStr == "metal")
        return RayTracer::Core::LIBRARY_TYPE::METAL;
    else if (typeStr == "lightDiffuse")
        return RayTracer::Core::LIBRARY_TYPE::LIGHT_DIFFUSE;
    else
        throw RayTracer::Parser::ParserException("Unknown material \"" + typeStr + "\" type in config file");
}

double getFuzzinessValue(libconfig::Setting &material)
{
    try {
        double fuzziness = material.lookup("fuzziness");
        return fuzziness;
    } catch (const libconfig::SettingNotFoundException &e) {
        std::cerr << "No fuzziness defined for " << material.getName() << "material" << std::endl;
        return 0.0;
    }
}

void RayTracer::Parser::parseMaterialsSection()
{
    try {
        for (int i = 0; i < _materialsSection->getLength(); i++) {
            MaterialConfig config;
            libconfig::Setting &material = _materialsSection->operator[](i);
            const std::string &name = getMaterialName(material);
            std::string typeStr = material.lookup("type");
            RayTracer::Core::LIBRARY_TYPE type = getMaterialTypeFromString(typeStr);
            config._type = type;
            config._fuzziness = getFuzzinessValue(material);
            libconfig::Setting &color = material.lookup("color");
            RayTracer::Color materialColor(color[0], color[1], color[2]);
            config._color = materialColor;
            loadNewMaterial(type, config, name);
        }
    } catch (const libconfig::SettingNotFoundException &e) {
        throw RayTracer::Parser::ParserException("Some settings are missing in config file \"" + _path + "\"");
    } catch (const libconfig::SettingTypeException &e) {
        throw RayTracer::Parser::ParserException("Some settings are bad formatted for point lights in config file \"" + _path + "\"");
    }
}

std::string RayTracer::Parser::getShapeNameForTransformation(libconfig::Setting &config)
{
    std::string name = config.getName();
    if (name.empty())
        throw RayTracer::Parser::ParserException("Transformations: Invalid name parameter");
    if (_parsedPrimitives.size() > 0) {
        for (auto &parsedPrimitive : _parsedPrimitives) {
            if (parsedPrimitive == name)
                return name;
        }
    }
    std::clog << MAGENTA << BOLD << "WARNING: " << RESET << MAGENTA << "Shape \"" << name << "\" not found in config file" << RESET << std::endl;
    return "";
}

void RayTracer::Parser::callTransformationMethod(const std::string& type, const std::string& shapeName, const Math::Vector3D& vector)
{
    if (type != "translate" && type != "rotate" && type != "scale") {
        std::clog << MAGENTA << BOLD << "WARNING: " << RESET << MAGENTA << "Unknown transformation type \"" << type << "\" in config file" << RESET << std::endl;
        return;
    }
    if (shapeName.empty())
        return;
    IShape &shape = refCore.getShape(shapeName);
    if (type == "translate") {
        std::cerr << "Translation for shape " << shapeName << std::endl;
        shape.translate(vector);
    } else if (type == "rotate") {
        std::cerr << "Rotation for shape " << shapeName << std::endl;
        shape.rotate(vector);
    }
}

void RayTracer::Parser::parseTransformationsSection()
{
    try {
        for (int i = 0; i < _transformationsSection->getLength(); i++) {
            libconfig::Setting &transformation = _transformationsSection->operator[](i);
            const std::string &name = getShapeNameForTransformation(transformation);
            if (name.empty())
                continue;
            const std::string transformationType = transformation.lookup("type");
            libconfig::Setting &transformationVector = transformation.lookup("vector");
            Math::Vector3D vector(transformationVector[0], transformationVector[1], transformationVector[2]);
            callTransformationMethod(transformationType, name, vector);
        }
    } catch (const libconfig::SettingNotFoundException &e) {
        throw RayTracer::Parser::ParserException("Some settings are missing for transformations in config file \"" + _path + "\"");
    } catch (const libconfig::SettingTypeException &e) {
        throw RayTracer::Parser::ParserException("Some settings are bad formatted for transformations in config file \"" + _path + "\"");
    }
}

void RayTracer::Parser::lookUpDoubleValue(libconfig::Setting &setting, const std::string& paramName, RayTracer::ShapeConfig& config)
{
    const std::string &name = setting.getName();
    try {
        double value = setting.lookup(paramName);
        config._parameters[paramName] = std::to_string(value);
    } catch (const libconfig::SettingNotFoundException &e) {
        std::clog << CYAN << BOLD << "INFO: " << RESET << CYAN << "For primitive <" << BOLD << name << RESET << CYAN << ">, setting \"" << paramName << "\" is missing" << RESET << std::endl;
    } catch (const libconfig::SettingTypeException &e) {
        throw RayTracer::Parser::ParserException("Some settings are bad formatted for primitive \"" + name + "\" in config file \"" + _path + "\"");
    }
}
void RayTracer::Parser::lookUpStringValue(libconfig::Setting &setting, const std::string& paramName, RayTracer::ShapeConfig& config)
{
    const std::string &name = setting.getName();
    try {
        std::string value = setting.lookup(paramName);
        config._parameters[paramName] = value;
    } catch (const libconfig::SettingNotFoundException &e) {
        std::clog << CYAN << BOLD << "INFO: " << RESET << CYAN << "For primitive <" << BOLD << name << RESET << CYAN << ">, setting \"" << paramName << "\" is missing" << RESET << std::endl;
    } catch (const libconfig::SettingTypeException &e) {
        throw RayTracer::Parser::ParserException("Some settings are bad formatted for primitive \"" + name + "\" in config file \"" + _path + "\"");
    }
}

void RayTracer::Parser::getPrimitiveConfig(libconfig::Setting &primitive, RayTracer::ShapeConfig& config)
{
    const std::string &name = getPrimitiveName(primitive);
    if (name.empty())
        throw RayTracer::Parser::ParserException("Primitives: Invalid name parameter");
    config._parameters["name"] = name;
    libconfig::Setting &origin = primitive.lookup("origin");
    lookUpDoubleValue(origin, "x", config);
    lookUpDoubleValue(origin, "y", config);
    lookUpDoubleValue(origin, "z", config);
    lookUpStringValue(primitive, "material", config);
    lookUpDoubleValue(primitive, "radius", config);
    lookUpDoubleValue(primitive, "height", config);
    lookUpDoubleValue(primitive, "angle", config);
    lookUpStringValue(primitive, "axis", config);
    lookUpDoubleValue(primitive, "xDim", config);
    lookUpDoubleValue(primitive, "yDim", config);
    lookUpDoubleValue(primitive, "zDim", config);
}

void RayTracer::Parser::parsePrimitives()
{
    std::string parsedPrimitiveName = "";
    try {
        for (int i = 0; i < _primitivesSection->getLength(); i++) {
            RayTracer::ShapeConfig config(_loadedMaterials);
            libconfig::Setting &primitive = _primitivesSection->operator[](i);
            parsedPrimitiveName = primitive.getName();
            int type = primitive.lookup("type");
            getPrimitiveConfig(primitive, config);
            IShape &newShape = refCore.getNewShape(static_cast<RayTracer::Core::LIBRARY_TYPE>(type));
            static_cast<RayTracer::Cone&>(newShape).setup(config);
            refCore.addShape(newShape);
        }
    } catch (const libconfig::SettingNotFoundException &e) {
        std::clog << CYAN << BOLD << "INFO: " << RESET << CYAN << "For primitive <" << BOLD << parsedPrimitiveName << RESET << CYAN << ">, setting <" << BOLD << e.getPath() << RESET << CYAN << "> is missing" << RESET << std::endl;
    } catch (const libconfig::SettingTypeException &e) {
        throw RayTracer::Parser::ParserException("Some settings are missing or bad formatted for primitives in config file \"" + _path + "\"");
    }
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

        _materialsSection = &_cfg.lookup("materials");
        if (_materialsSection != nullptr) {
            std::cerr << ">> Materials found in config file!" << std::endl;
            parseMaterialsSection();
        } else {
            std::cerr << "WARNING: No materials have been defined in config file" << std::endl;
        }

        _primitivesSection = &_cfg.lookup("primitives");
        if (_primitivesSection != nullptr) {
            std::cerr << ">> Primitives found in config file!" << std::endl;
            parsePrimitives();
        } else {
            throw RayTracer::Parser::ParserException("Failed to find primitives settings in config file \"" + _path + "\"");
        }

        try {
            _transformationsSection = &_cfg.lookup("transformations");
            if (_transformationsSection != nullptr) {
                std::cerr << ">> Transformations found in config file!" << std::endl;
                parseTransformationsSection();
            } else {
                std::clog << RED << "WARNING: No transformations have been defined in config file" << RESET << std::endl;
            }
        } catch (const libconfig::SettingNotFoundException &e) {
            std::clog << BOLD <<  MAGENTA << "WARNING: " << RESET << MAGENTA << "No transformations have been defined in config file" << RESET << std::endl;
        }

        // _lightsSection = &_cfg.lookup("lights");
        // if (_lightsSection != nullptr) {
        //     std::cerr << ">> Lights found in config file!" << std::endl;
        //     parseLights();
        // } else {
        //     std::cerr << ">> No lights found in config file!" << std::endl;
        // }
    } catch (const libconfig::FileIOException &e) {
        throw RayTracer::Parser::ParserException("Failed to read config file \"" + _path + "\": " + e.what());
    } catch (const libconfig::ParseException &e) {
        throw RayTracer::Parser::ParserException("Failed to parse config file \"" + _path + "\": " + e.getError());
    }

}
