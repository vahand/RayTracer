/*
** EPITECH PROJECT, 2024
** Raytracer
** File description:
** Cylinder
*/

#ifndef CYLINDER_HPP_
#define CYLINDER_HPP_

    #include "../../../../includes/AShape.hpp"
    #include "../../../../includes/HitData.hpp"
    #include "../../../../includes/Range.hpp"
    #include "../../../../includes/Ray.hpp"
namespace RayTracer {
    class Cylinder : public AShape {
        public:
            struct CylinderHitData
            {
                double aDirection;
                double bDirection;
                double aRayOrigin;
                double bRayOrigin;
                double aOrigin;
                double bOrigin;
            };

            Cylinder() = default;
            Cylinder(Math::Point3D& origin, double radius, double height, std::shared_ptr<RayTracer::Material::IMaterial> material, RayTracer::ShapeConfig::AXIS axis)
            : _radius(radius), _height(height), _material(material), _axis(axis)
            {
                _origin = origin;
            }

            void setup(const RayTracer::ShapeConfig& config)
            {
                _origin = config._origin;
                _radius = config._radius;
                _height = config._height;
                _material = config._material;
                _axis = config._axis;
            }

            Math::Vector3D getVectorFromPoints(const Math::Point3D& lhs, const Math::Point3D& rhs) const
            {
                return Math::Vector3D(lhs.x() - rhs.x(), lhs.y() - rhs.y(), lhs.z() - rhs.z());
            }

            struct CylinderHitData getCylinderHitData(Math::Point3D origin, Math::Point3D rayOrigin, Math::Vector3D rayDirection) const
            {
                struct CylinderHitData data;
                RayTracer::ShapeConfig::AXIS axis = _axis;
                data.aDirection = (axis == ShapeConfig::Y || axis == ShapeConfig::Z) ? rayDirection.X : rayDirection.Y;
                data.bDirection = (axis == ShapeConfig::X || axis == ShapeConfig::Y) ? rayDirection.Z : rayDirection.Y;
                data.aRayOrigin = (axis == ShapeConfig::Y || axis == ShapeConfig::Z) ? rayOrigin.X : rayOrigin.Y;
                data.bRayOrigin = (axis == ShapeConfig::X || axis == ShapeConfig::Y) ? rayOrigin.Z : rayOrigin.Y;
                data.aOrigin = (axis == ShapeConfig::Y || axis == ShapeConfig::Z) ? origin.X : origin.Y;
                data.bOrigin = (axis == ShapeConfig::X || axis == ShapeConfig::Y) ? origin.Z : origin.Y;
                return data;
            }

            bool hit(const RayTracer::Ray& ray, RayTracer::Range ray_range, HitData& data) const override
            {
                double r = radius();
                Math::Point3D origin = center();
                Math::Point3D rayOrigin = ray.origin();
                Math::Vector3D rayDirection = ray.direction();
                getNormalVectorRotate(rayDirection);
                struct CylinderHitData hittingData = getCylinderHitData(origin, rayOrigin, rayDirection);
                double a = hittingData.aDirection * hittingData.aDirection + hittingData.bDirection * hittingData.bDirection;
                double b = 2.0 * (hittingData.aRayOrigin * hittingData.aDirection
                    + hittingData.bRayOrigin * hittingData.bDirection
                    - hittingData.aOrigin * hittingData.aDirection
                    - hittingData.bOrigin * hittingData.bDirection);
                double c = hittingData.aRayOrigin * hittingData.aRayOrigin
                    + hittingData.bRayOrigin * hittingData.bRayOrigin
                    + hittingData.aOrigin * hittingData.aOrigin
                    + hittingData.bOrigin * hittingData.bOrigin
                    - 2.0 * (hittingData.aRayOrigin * hittingData.aOrigin + hittingData.bRayOrigin * hittingData.bOrigin) - r * r;

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
            double radius() const { return _radius; }

            void rotate(const Math::Vector3D &rotation) override {
                _rotation = rotation;
                degreeToRadian(_rotation);
            }

        protected:
        private:
            double _radius;
            double _height;
            std::shared_ptr<RayTracer::Material::IMaterial> _material;
            RayTracer::ShapeConfig::AXIS _axis;
    };
}

#endif /* !CONE_HPP_ */
