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

            bool operator==(const AShape &shape) const {
                return _origin == shape._origin && _color == shape._color && _type == shape._type;
            }

            Math::Point3D _origin;
            RayTracer::Color _color;
            RayTracer::ShapeType _type;
            std::string _name;
    };
}

#endif /* !AShape_HPP_ */
