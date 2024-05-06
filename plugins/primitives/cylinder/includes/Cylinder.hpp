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
            Cylinder() = default;
            Cylinder(Math::Point3D& origin, double radius, double height, std::shared_ptr<RayTracer::Material::IMaterial> material, RayTracer::ShapeConfig::AXIS axis)
            : _radius(radius), _height(height), _material(material), _axis(axis)
            {
                _origin = origin;
            }

            void setup(const RayTracer::ShapeConfig& config)
            {
            }

            Math::Vector3D getVectorFromPoints(const Math::Point3D& lhs, const Math::Point3D& rhs) const
            {
                return Math::Vector3D(lhs.x() - rhs.x(), lhs.y() - rhs.y(), lhs.z() - rhs.z());
            }

            bool hit(const RayTracer::Ray& ray, RayTracer::Range ray_range, HitData& data) const override
            {
                double r = radius();
                Math::Point3D origin = center();
                Math::Point3D rayOrigin = ray.origin();
                Math::Vector3D rayDirection = ray.direction();
                double a = rayDirection.x() * rayDirection.x() + rayDirection.z() * rayDirection.z();
                double b = 2.0 * (rayOrigin.X * rayDirection.X + rayOrigin.Z * rayDirection.Z - origin.X * rayDirection.X - origin.Z * rayDirection.Z);
                double c = rayOrigin.X * rayOrigin.X + rayOrigin.Z * rayOrigin.Z + origin.X * origin.X + origin.Z * origin.Z
                    - 2.0 * (rayOrigin.X * origin.X + rayOrigin.Z * origin.Z) - r * r;

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

        protected:
        private:
            double _radius;
            double _height;
            std::shared_ptr<RayTracer::Material::IMaterial> _material;
            RayTracer::ShapeConfig::AXIS _axis;
    };
}

#endif /* !CONE_HPP_ */
