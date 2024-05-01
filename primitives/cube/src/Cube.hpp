/*
** EPITECH PROJECT, 2024
** Raytracer
** File description:
** Cube
*/

#ifndef CUBE_HPP_
#define CUBE_HPP_

    #include "../../../includes/AShape.hpp"
    #include "../../../includes/HitData.hpp"
    #include "../../../includes/Range.hpp"
    #include "../../../includes/Ray.hpp"
    #include "../../../includes/AMaterial.hpp"
    #include "../../../includes/Color.hpp"
    #include "../../../includes/ShapeConfig.hpp"
    #include <unordered_map>

namespace RayTracer {
    class Cube : public AShape {
        public:
            class CubeFace {
                public:
                    CubeFace(Math::Point3D highLeftCorner, Math::Point3D highRightCorner, Math::Point3D lowLeftCorner, Math::Point3D lowRightCorner);
                    ~CubeFace();
            };
            Cube() = default;
            Cube(const Math::Point3D origin, double xDim, double yDim, double zDim, std::shared_ptr<RayTracer::Material::IMaterial> material)
                : _material(material), _origin(origin), _xDim(xDim), _yDim(yDim), _zDim(zDim)
            {

            }

            bool hit(const RayTracer::Ray& ray, RayTracer::Range ray_range, HitData& data) const override
            {
                return false;
            }

            Math::Point3D center() const { return _origin; }
            double xDim() const { return _xDim; }
            double yDim() const { return _yDim; }
            double zDim() const { return _zDim; }

        protected:
        private:
            Math::Point3D _origin;
            double _xDim;
            double _yDim;
            double _zDim;
            std::shared_ptr<RayTracer::Material::IMaterial> _material;
            std::unordered_map<std::string, Math::Point3D> _vertexes;

            double xO() { return _origin.x(); }
            double yO() { return _origin.y(); }
            double zO() { return _origin.z(); }

            void init_vertexes()
            {
                _vertexes["A"] = Math::Point3D(xO() - _xDim / 2.0, yO() - _yDim / 2.0, zO() - _zDim / 2.0);
                _vertexes["B"] = Math::Point3D(xO() + _xDim / 2.0, yO() - _yDim / 2.0, zO() - _zDim / 2.0);
                _vertexes["C"] = Math::Point3D(xO() - _xDim / 2.0, yO() + _yDim / 2.0, zO() - _zDim / 2.0);
                _vertexes["D"] = Math::Point3D(xO() + _xDim / 2.0, yO() + _yDim / 2.0, zO() - _zDim / 2.0);
                _vertexes["E"] = Math::Point3D(xO() - _xDim / 2.0, yO() - _yDim / 2.0, zO() + _zDim / 2.0);
                _vertexes["F"] = Math::Point3D(xO() + _xDim / 2.0, yO() - _yDim / 2.0, zO() + _zDim / 2.0);
                _vertexes["G"] = Math::Point3D(xO() - _xDim / 2.0, yO() + _yDim / 2.0, zO() + _zDim / 2.0);
                _vertexes["H"] = Math::Point3D(xO() + _xDim / 2.0, yO() + _yDim / 2.0, zO() + _zDim / 2.0);

            }
    };
}

#endif /* !CUBE_HPP_ */
