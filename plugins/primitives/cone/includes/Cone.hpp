/*
** EPITECH PROJECT, 2024
** Raytracer
** File description:
** Cone
*/

#ifndef CONE_HPP_
#define CONE_HPP_

    #include "../../../../includes/AShape.hpp"
    #include "../../../../includes/HitData.hpp"
    #include "../../../../includes/Range.hpp"
    #include "../../../../includes/Ray.hpp"
namespace RayTracer {
    class Cone : public AShape {
        public:
            struct ConeHitData
            {
                double aDirection;
                double bDirection;
                double cDirection;
                double aRayOrigin;
                double bRayOrigin;
                double cRayOrigin;
                double aOrigin;
                double bOrigin;
                double cOrigin;
            };
            Cone() = default;
            Cone(Math::Point3D& origin, double radius, double height, std::shared_ptr<RayTracer::Material::IMaterial> material, RayTracer::ShapeConfig::AXIS axis, double angle)
            : _radius(radius), _height(height), _material(material), _axis(axis), _angle(angle)
            {
                _origin = origin;
                _vertex = Math::Point3D(_origin.x(), _origin.y(), _origin.z() + height);
            }

            bool hasAllParameters(const RayTracer::ShapeConfig& config) const override
            {
                if (config._parameters.find("x") == config._parameters.end()) {
                    std::clog << RED << "CONE: Missing x parameter" << RESET << std::endl;
                    return false;
                }
                if (config._parameters.find("y") == config._parameters.end()) {
                    std::clog << RED << "CONE: Missing y parameter" << RESET << std::endl;
                    return false;
                }
                if (config._parameters.find("z") == config._parameters.end()) {
                    std::clog << RED << "CONE: Missing z parameter" << RESET << std::endl;
                    return false;
                }
                if (config._parameters.find("axis") == config._parameters.end()) {
                    std::clog << RED << "CONE: Missing axis parameter" << RESET << std::endl;
                    return false;
                }
                if (config._parameters.find("material") == config._parameters.end()) {
                    std::clog << RED << "CONE: Missing material parameter" << RESET << std::endl;
                    return false;
                }
                if (config._parameters.find("radius") == config._parameters.end()) {
                    std::clog << RED << "CONE: Missing radius parameter" << RESET << std::endl;
                    return false;
                }
                // if (config._parameters.find("height") == config._parameters.end())
                //     return false;
                if (config._parameters.find("angle") == config._parameters.end()) {
                    std::clog << RED << "CONE: Missing angle parameter" << RESET << std::endl;
                    return false;
                }
                return true;
            }

            void setup(const RayTracer::ShapeConfig& config) override
            {
                if (hasAllParameters(config) == false)
                    throw ShapeException("CONE: Missing parameters in config file");
                setName(config._parameters.at("name"));
                _origin = Math::Point3D(atof(config._parameters.at("x").c_str()), atof(config._parameters.at("y").c_str()), atof(config._parameters.at("z").c_str()));
                _axis = getAxisFromString(config._parameters.at("axis"));
                _material = config._loadedMaterials.at(config._parameters.at("material"));
                _radius = atof(config._parameters.at("radius").c_str());
                // _height = atof(config._parameters.at("height").c_str());
                _angle = atof(config._parameters.at("angle").c_str());
                _vertex = Math::Point3D(_origin.x(), _origin.y(), _origin.z() + _height);
            }

            Math::Vector3D getVectorFromPoints(const Math::Point3D& lhs, const Math::Point3D& rhs) const
            {
                return Math::Vector3D(lhs.x() - rhs.x(), lhs.y() - rhs.y(), lhs.z() - rhs.z());
            }

            struct ConeHitData getConeHitData(Math::Vector3D rayDirection, Math::Point3D origin, Math::Point3D rayOrigin) const
            {
                struct ConeHitData data;
                RayTracer::ShapeConfig::AXIS axis = _axis;
                data.aDirection = (axis == ShapeConfig::Y || axis == ShapeConfig::Z) ? rayDirection.X : rayDirection.Y;
                data.bDirection = (axis == ShapeConfig::X || axis == ShapeConfig::Y) ? rayDirection.Z : rayDirection.Y;
                data.aRayOrigin = (axis == ShapeConfig::Y || axis == ShapeConfig::Z) ? rayOrigin.X : rayOrigin.Y;
                data.bRayOrigin = (axis == ShapeConfig::X || axis == ShapeConfig::Y) ? rayOrigin.Z : rayOrigin.Y;
                data.aOrigin = (axis == ShapeConfig::Y || axis == ShapeConfig::Z) ? origin.X : origin.Y;
                data.bOrigin = (axis == ShapeConfig::X || axis == ShapeConfig::Y) ? origin.Z : origin.Y;
                if (axis == ShapeConfig::X) {
                    data.cDirection = rayDirection.X;
                    data.cRayOrigin = rayOrigin.X;
                    data.cOrigin = origin.X;
                } else if (axis == ShapeConfig::Y) {
                    data.cDirection = rayDirection.Y;
                    data.cRayOrigin = rayOrigin.Y;
                    data.cOrigin = origin.Y;
                } else {
                    data.cDirection = rayDirection.Z;
                    data.cRayOrigin = rayOrigin.Z;
                    data.cOrigin = origin.Z;
                }
                return data;
            }

            bool hit(const RayTracer::Ray& ray, RayTracer::Range ray_range, HitData& data) const override
            {
                double alpha = _angle;
                double squaredTan = tan(alpha) * tan(alpha);
                Math::Vector3D rayDirection = ray.direction();
                getNormalVectorRotate(rayDirection);
                Math::Point3D rayOrigin = ray.origin();
                Math::Point3D origin = center();
                struct ConeHitData hittingData = getConeHitData(rayDirection, origin, rayOrigin);
                double a = (hittingData.aDirection * hittingData.aDirection)
                    + (hittingData.bDirection * hittingData.bDirection)
                    - (squaredTan * hittingData.cDirection * hittingData.cDirection);
                double b = 2.0 * ((hittingData.aRayOrigin * hittingData.aDirection)
                    - (hittingData.aDirection * hittingData.aOrigin)
                    + (hittingData.bRayOrigin * hittingData.bDirection)
                    - (hittingData.bDirection * hittingData.bOrigin)
                    - (squaredTan * hittingData.cRayOrigin * hittingData.cDirection)
                    + (squaredTan * hittingData.cDirection * hittingData.cOrigin));
                double c = (hittingData.aRayOrigin * hittingData.aRayOrigin)
                    - 2.0 * (hittingData.aRayOrigin * hittingData.aOrigin)
                    + (hittingData.aOrigin * hittingData.aOrigin)
                    + (hittingData.bRayOrigin * hittingData.bRayOrigin)
                    - 2.0 * (hittingData.bRayOrigin * hittingData.bOrigin)
                    + (hittingData.bOrigin * hittingData.bOrigin)
                    - (squaredTan * hittingData.cRayOrigin * hittingData.cRayOrigin)
                    + (squaredTan * 2.0 * hittingData.cRayOrigin * hittingData.cOrigin)
                    - squaredTan * (hittingData.cOrigin * hittingData.cOrigin);

                double discriminant = b * b - 4.0 * a * c;
                if (discriminant < 0)
                    return false;
                double root = (-b - sqrt(discriminant)) / (2.0 * a);
                if (!ray_range.around(root)) {
                    root = (-b + sqrt(discriminant)) / (2.0 * a);
                    if (!ray_range.around(root))
                        return false;
                }
                data.tValue = root;
                data.point = ray.at(data.tValue);
                data.normal = normal(data.point);
                data.determineFace(ray, data.normal);
                data.material = _material;
                return true;
            }

            Math::Vector3D normal(const Math::Point3D& point) const
            {
                Math::Vector3D normal = getVectorFromPoints(_origin, point).normalize();
                return normal;
            };

            Math::Point3D center() const { return _origin; }
            Math::Point3D vertex() const { return _vertex; }
            double radius() const { return _radius; }

            void rotate(const Math::Vector3D &rotation) override {
                _rotation = rotation;
                degreeToRadian(_rotation);
            }


        protected:
        private:
            Math::Point3D _vertex;
            double _radius;
            double _height;
            std::shared_ptr<RayTracer::Material::IMaterial> _material;
            RayTracer::ShapeConfig::AXIS _axis;
            double _angle;
    };
}

#endif /* !CONE_HPP_ */
