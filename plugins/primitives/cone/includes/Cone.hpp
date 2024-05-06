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
            Cone() = default;
            Cone(Math::Point3D& origin, double radius, double height, std::shared_ptr<RayTracer::Material::IMaterial> material, RayTracer::ShapeConfig::AXIS axis, double angle)
            : _origin(origin), _radius(radius), _height(height), _material(material), _axis(axis), _angle(angle)
            {
                _vertex = Math::Point3D(_origin.x(), _origin.y(), _origin.z() + height);
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
                double alpha = _angle;
                double squaredTan = tan(alpha) * tan(alpha);
                Math::Vector3D rayDirection = ray.direction();
                Math::Point3D rayOrigin = ray.origin();
                Math::Point3D origin = center();
                double a = (rayDirection.X * rayDirection.X) + (rayDirection.Z * rayDirection.Z) - (squaredTan * rayDirection.Y * rayDirection.Y);
                double b = 2.0 * ((rayOrigin.X * rayDirection.X) - (rayDirection.X * origin.X) + (rayOrigin.Z * rayDirection.Z)
                    - (rayDirection.Z * origin.Z) - (squaredTan * rayOrigin.Y * rayDirection.Y) + (squaredTan * rayDirection.Y * origin.Y));
                double c = (rayOrigin.X * rayOrigin.X) - 2.0 * (rayOrigin.X * origin.X) + (origin.X * origin.X)
                    + (rayOrigin.Z * rayOrigin.Z) - 2.0 * (rayOrigin.Z * origin.Z) + (origin.Z * origin.Z)
                    - (squaredTan * rayOrigin.Y * rayOrigin.Y) + (squaredTan * 2.0 * rayOrigin.Y * origin.Y) - squaredTan * (origin.Y * origin.Y);

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


        protected:
        private:
            Math::Point3D _origin;
            Math::Point3D _vertex;
            double _radius;
            double _height;
            std::shared_ptr<RayTracer::Material::IMaterial> _material;
            RayTracer::ShapeConfig::AXIS _axis;
            double _angle;
    };
}

#endif /* !CONE_HPP_ */
