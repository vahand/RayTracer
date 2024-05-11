/*
** EPITECH PROJECT, 2024
** BS_RAYTRACER
** File description:
** AShape
*/

#ifndef AShape_HPP_
    #define AShape_HPP_

    #include "IShape.hpp"

namespace RayTracer {
    class AShape : public IShape {
        public:
            AShape() = default;
            virtual ~AShape() = default;

            const std::string& getName() const override { return _name; }
            void setName(const std::string& name) override { _name = name; }
            void translate(const Math::Vector3D& translation) override {
                _origin.X += translation.X;
                _origin.Y += translation.Y;
                _origin.Z += translation.Z;
            }

            void degreeToRadian(Math::Vector3D &angle) override {
                angle.X = (angle.x() * M_PI / 180);
                angle.Y = (angle.y() * M_PI / 180);
                angle.Z = (angle.z() * M_PI / 180);
            }

            bool operator==(const AShape &shape) const {
                return _origin == shape._origin && _color == shape._color && _type == shape._type;
            }

            void getNormalVectorRotate(Math::Vector3D &normal)const override {
                Math::Vector3D vecTemp;

                if (_rotation.X != 0) {
                    vecTemp.X = (1 * normal.X) + (0 * normal.Y) + (0 * normal.Z);
                    vecTemp.Y = (0 * normal.X) + (cos(_rotation.x()) * normal.Y) + (-sin(_rotation.x()) * normal.Z);
                    vecTemp.Z = (0 * normal.X) + (sin(_rotation.x()) * normal.Y) + (cos(_rotation.x()) * normal.Z);
                    normal = vecTemp;
                }
                if (_rotation.Y != 0) {
                    vecTemp.X = (cos(_rotation.y()) * normal.X) + (0 * normal.Y) + (sin(_rotation.y()) * normal.Z);
                    vecTemp.Y = (0 * normal.X) + (1 * normal.Y) + (0 * normal.Z);
                    vecTemp.Z = (-sin(_rotation.y()) * normal.X) + (0 * normal.Y) + (cos(_rotation.y()) * normal.Z);
                    normal = vecTemp;
                }
                if (_rotation.Z != 0) {
                    vecTemp.X = (cos(_rotation.z()) * normal.X) + (-sin(_rotation.z()) * normal.Y) + (0 * normal.Z);
                    vecTemp.Y = (sin(_rotation.z()) * normal.X) + (cos(_rotation.z()) * normal.Y) + (0 * normal.Z);
                    vecTemp.Z = (0 * normal.X) + (0 * normal.Y) + (1 * normal.Z);
                    normal = vecTemp;
                }
            }

            ShapeConfig::AXIS getAxisFromString(const std::string& axis)
            {
                if (axis == "X")
                    return ShapeConfig::AXIS::X;
                if (axis == "Y")
                    return ShapeConfig::AXIS::Y;
                if (axis == "Z")
                    return ShapeConfig::AXIS::Z;
                return ShapeConfig::AXIS::Y;
            }

            Math::Point3D _origin;
            RayTracer::Color _color;
            RayTracer::ShapeType _type;
            std::string _name;
            Math::Vector3D _rotation;

        protected:
            bool hasThisParameter(const RayTracer::ShapeConfig& config, const std::string& param, const std::string& shapeName) const
            {
                if (config._parameters.find(param) == config._parameters.end()) {
                    std::clog << RED << shapeName << ": Missing " << param << " parameter" << RESET << std::endl;
                    return false;
                }
                return true;
            }
    };
}

#endif /* !AShape_HPP_ */
