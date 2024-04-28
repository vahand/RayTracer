/*
** EPITECH PROJECT, 2024
** BS_RAYTRACER
** File description:
** Sphere
*/

#ifndef SPHERE_HPP_
    #define SPHERE_HPP_

    #include "../../../includes/IShape.hpp"
    #include "../../../includes/HitData.hpp"
    #include "../../../includes/Range.hpp"
    #include "../../../includes/Ray.hpp"
    #include "../../../includes/Material.hpp"
    #include "../../../includes/Color.hpp"
    #include <cmath>

namespace RayTracer {
    class Sphere : public IShape {
        public:
            Sphere() = default;
            Sphere(const Math::Point3D& center, double radius, std::shared_ptr<RayTracer::Material::AMaterial> material)
                : _material(material), _origin(center), _radius(radius) {}

            Math::Vector3D getVectorFromPoints(const Math::Point3D& lhs, const Math::Point3D& rhs) const
            {
                return Math::Vector3D(lhs.x() - rhs.x(), lhs.y() - rhs.y(), lhs.z() - rhs.z());
            }

            bool hit(const RayTracer::Ray& ray, RayTracer::Range ray_range, HitData& data) const override
            {
                Math::Vector3D oc = getVectorFromPoints(_origin, ray.origin());
                double a = ray.direction().lengthSquared();
                double h = ray.direction().DotProduct(oc);
                double c = oc.lengthSquared() - (_radius * _radius);

                double discriminant = h * h - a * c;
                if (discriminant < 0)
                    return false;

                double rootedDiscriminant = sqrt(discriminant);
                double root = (h - rootedDiscriminant) / a;
                if (!ray_range.around(root)) {
                    root = (h + rootedDiscriminant) / a;
                    if (!ray_range.around(root))
                        return false;
                }

                data.tValue = root;
                data.point = ray.at(data.tValue);
                data.normal = (data.point - _origin) / _radius;
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
            RayTracer::Color getColor() const override { return _color; }

        private:
            Math::Point3D _origin;
            double _radius;
            RayTracer::Color _color;
            std::shared_ptr<RayTracer::Material::AMaterial> _material;
    };
}

#endif /* !SPHERE_HPP_ */
