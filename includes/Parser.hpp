/*
** EPITECH PROJECT, 2024
** Raytracer
** File description:
** Parser
*/

#ifndef PARSER_HPP_
    #define PARSER_HPP_

    #include <libconfig.h++>
    #include <libconfig.h>

    #include "Core.hpp"
    #include "ShapeConfig.hpp"
    #include "MaterialConfig.hpp"

namespace RayTracer {
    struct config_camere_s {
        int resolution[2];
        double position[3];
        double rotation[3];
        double fov;
    };
    class Parser {
        public:
            class ParserException : public std::exception {
                public:
                    ParserException(const std::string &message) : _message(message) {};
                    const char *what() const noexcept override { return _message.c_str(); }

                private:
                    std::string _message;
            };
            Parser(Core&, const std::string&);
            ~Parser();

            void parseConfig();
            void printConfig();

            config_camere_s camera_settings;
            Core &refCore;

        protected:
        private:
            std::string _path;
            libconfig::Config _cfg;

            // CAMERA SETTINGS
            libconfig::Setting *_cameraSection;

            void parseCameraSettings();

            // MATERIALS
            libconfig::Setting *_materialsSection;
            std::vector<std::string> _parsedMaterials;

            void parseMaterialsSection();
            std::string getMaterialName(libconfig::Setting &);

            // PRIMITIVES
            libconfig::Setting *_primitivesSection;
            std::vector<std::string> _parsedPrimitives;

            void parsePrimitives();
            std::string getPrimitiveName(libconfig::Setting &);
            void parseSpheres();
            void parsePlanes();
            RayTracer::ShapeConfig::AXIS getPlaneAxis(const std::string&);
            Math::Point3D getPlaneOrigin(double, RayTracer::ShapeConfig::AXIS);

            // LIGHTS
            libconfig::Setting *_lightsSection;
            std::vector<std::string> _parsedLights;

            bool _mainAmbientFactorIsDefined;
            bool _mainDiffuseFactorIsDefined;
            double _mainAmbientFactor;
            double _mainDiffuseFactor;

            std::string getLightName(libconfig::Setting &);
            double getAmbientFactor(libconfig::Setting &);
            double getDiffuseFactor(libconfig::Setting &);
            void parseLights();
            void parseMainAmbientFactor();
            void parseMainDiffuseFactor();
            void parsePointLight();
    };
}

#endif /* !PARSER_HPP_ */
