/*
** EPITECH PROJECT, 2024
** BS_RAYTRACER
** File description:
** HitData
*/

#ifndef HITDATA_HPP_
    #define HITDATA_HPP_

    #include "Vector3D.hpp"
    #include "Point3D.hpp"
    #include "Ray.hpp"
    #include <memory>

namespace RayTracer {
    namespace Material {
        class AMaterial;
    }
}

class HitData {
    public:
        HitData() = default;
        ~HitData() = default;

        Math::Point3D point;
        Math::Vector3D normal;
        double tValue;
        bool isFront;

        void determineFace(const RayTracer::Ray &r, const Math::Vector3D &united_normal) {
            isFront = r.direction().DotProduct(united_normal) < 0;
            if (isFront)
                normal = united_normal;
            else
                normal = -united_normal;
        }

        std::shared_ptr<RayTracer::Material::AMaterial> material;
};

#include "Material.hpp"

#endif /* !HITDATA_HPP_ */
