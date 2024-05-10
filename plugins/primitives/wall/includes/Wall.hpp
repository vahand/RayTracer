/*
** EPITECH PROJECT, 2024
** Raytracer
** File description:
** Wall
*/

#ifndef WALL_HPP_
    #define WALL_HPP_

    #include "../../../../includes/AShape.hpp"
    #include "../../../../includes/HitData.hpp"
    #include "../../../../includes/Range.hpp"
    #include "../../../../includes/Ray.hpp"
    #include "../../../../includes/AMaterial.hpp"
    #include <cmath>

namespace RayTracer {
    class Wall : public AShape {
        public:
            Wall() = default;
            Wall(Math::Point3D origin, RayTracer::ShapeConfig::AXIS axis, std::shared_ptr<RayTracer::Material::IMaterial> material, double width, double height)
             : _origin(origin), _axis(axis), _material(material), _width(width), _height(height)
            {
                if (_axis == RayTracer::ShapeConfig::AXIS::X) {
                    _normal = Math::Vector3D(1, 0, 0);
                } else if (_axis == RayTracer::ShapeConfig::AXIS::Y) {
                    _normal = Math::Vector3D(0, 1, 0);
                } else {
                    _normal = Math::Vector3D(0, 0, 1);
                }
                _rotation = Math::Vector3D(0, 0, 0);
            }

            bool hasAllParameters(const RayTracer::ShapeConfig& config) const override
            {
                if (hasThisParameter(config, "x", "WALL") == false)
                    return false;
                if (hasThisParameter(config, "y", "WALL") == false)
                    return false;
                if (hasThisParameter(config, "z", "WALL") == false)
                    return false;
                if (hasThisParameter(config, "axis", "WALL") == false)
                    return false;
                if (hasThisParameter(config, "material", "WALL") == false)
                    return false;
                if (hasThisParameter(config, "width", "WALL") == false)
                    return false;
                if (hasThisParameter(config, "height", "WALL") == false)
                    return false;
                return true;
            }

            void setup(const RayTracer::ShapeConfig& config) override
            {
                if (!hasAllParameters(config))
                    throw ShapeException("WALL: Missing parameters in config file");
                setName(config._parameters.at("name"));
                _origin = Math::Point3D(atof(config._parameters.at("x").c_str()), atof(config._parameters.at("y").c_str()), atof(config._parameters.at("z").c_str()));
                _axis = getAxisFromString(config._parameters.at("axis"));
                _material = config._loadedMaterials.at(config._parameters.at("material"));
                _width = atof(config._parameters.at("width").c_str());
                _height = atof(config._parameters.at("height").c_str());
                if (_axis == RayTracer::ShapeConfig::AXIS::X) {
                    _normal = Math::Vector3D(1, 0, 0);
                } else if (_axis == RayTracer::ShapeConfig::AXIS::Y) {
                    _normal = Math::Vector3D(0, 1, 0);
                } else {
                    _normal = Math::Vector3D(0, 0, 1);
                }
                _min_X = _origin.X - _width / 2;
                _max_X = _origin.X + _width / 2;
                _min_Y = _origin.Y - _height / 2;
                _max_Y = _origin.Y + _height / 2;
                if (_axis == RayTracer::ShapeConfig::AXIS::Y) {
                    _min_Z = _origin.Z - _height / 2;
                    _max_Z = _origin.Z + _height / 2;
                } else {
                    _min_Z = _origin.Z - _width / 2;
                    _max_Z = _origin.Z + _width / 2;
                }
            }

            Math::Vector3D getVectorFromPoints(const Math::Point3D& lhs, const Math::Point3D& rhs) const
            {
                return Math::Vector3D(lhs.x() - rhs.x(), lhs.y() - rhs.y(), lhs.z() - rhs.z());
            }

            double getDConstante() const
            {
                Math::Vector3D n = getNormalVector();
                Math::Point3D o = getOrigin();
                double d = n.X * o.X + n.Y * o.Y + n.Z * o.Z;
                return d;
            }

            bool hit(const RayTracer::Ray& ray, RayTracer::Range ray_range, HitData& data) const override
            {
                double d = getDConstante();
                double t = (d - ray.origin().DotProduct(getNormalVector())) / getNormalVector().DotProduct(ray.direction());
                if (t < ray_range.min || t > ray_range.max)
                    return false;
                Math::Point3D ray_point = ray.at(t);
                if (ray_point.X < _min_X || ray_point.X > _max_X)
                    return false;
                if (ray_point.Y < _min_Y || ray_point.Y > _max_Y)
                    return false;
                if (ray_point.Z < _min_Z || ray_point.Z > _max_Z)
                    return false;
                data.tValue = t;
                data.point = ray.at(data.tValue);
                data.normal = getNormalVector();
                data.determineFace(ray, data.normal);
                data.material = _material;
                return true;
            }

            Math::Vector3D getNormalVector() const
            {
                return _normal;
            }

            Math::Point3D getOrigin() const
            {
                return _origin;
            }

            void rotate(const Math::Vector3D &rotation) override {
                _rotation = rotation;
                degreeToRadian(_rotation);
                getNormalVectorRotate(_normal);
            }

        protected:
        private:
            RayTracer::ShapeConfig::AXIS _axis;
            Math::Point3D _origin;
            Math::Vector3D _normal;
            std::shared_ptr<RayTracer::Material::IMaterial> _material;
            double _width;
            double _height;

            double _min_X;
            double _max_X;
            double _min_Y;
            double _max_Y;
            double _min_Z;
            double _max_Z;
    };
}

#endif /* !WALL_HPP_ */
