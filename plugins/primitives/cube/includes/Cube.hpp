/*
** EPITECH PROJECT, 2024
** Raytracer
** File description:
** Cube
*/

#ifndef CUBE_HPP_
#define CUBE_HPP_

    #include "../../../../includes/AShape.hpp"
    #include "../../../../includes/HitData.hpp"
    #include "../../../../includes/Range.hpp"
    #include "../../../../includes/Ray.hpp"
    #include <unordered_map>

namespace RayTracer {
    class CubeFace {
        public:
            CubeFace() = default;
            CubeFace(Math::Point3D topLeftCorner, Math::Point3D topRightCorner,
            Math::Point3D bottomLeftCorner, Math::Point3D bottomRightCorner,
            Math::Vector3D normal)
            : _topLeftCorner(topLeftCorner), _topRightCorner(topRightCorner),
            _bottomLeftCorner(bottomLeftCorner), _bottomRightCorner(bottomRightCorner),
            _normal(normal) {
                _min_X = topLeftCorner.X;
                _max_X = topRightCorner.X;
                _min_Y = topLeftCorner.Y;
                _max_Y = bottomLeftCorner.Y;
                _min_Z = topLeftCorner.Z;
                _max_Z = bottomLeftCorner.Z;
            }

            ~CubeFace() = default;

            double getDConstante() const
            {
                double d = _normal.X * _topLeftCorner.X + _normal.Y * _topLeftCorner.Y + _normal.Z * _topLeftCorner.Z;
                return d;
            }

            Math::Point3D _topLeftCorner;
            Math::Point3D _topRightCorner;
            Math::Point3D _bottomLeftCorner;
            Math::Point3D _bottomRightCorner;
            double _min_X;
            double _max_X;
            double _min_Y;
            double _max_Y;
            double _min_Z;
            double _max_Z;

            Math::Vector3D _normal;

            double d = getDConstante();

            Math::Vector3D getVectorFromPoints(const Math::Point3D& lhs, const Math::Point3D& rhs) const
            {
                return Math::Vector3D(lhs.x() - rhs.x(), lhs.y() - rhs.y(), lhs.z() - rhs.z());
            }

            bool hit(const RayTracer::Ray& ray, RayTracer::Range &ray_range, HitData& data) const
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
                    ray_range.max = sqrt(getVectorFromPoints(ray_point, ray.origin()).lengthSquared());
                    data.tValue = t;
                    return true;
            }

            Math::Vector3D getNormalVector() const
            {
                return _normal;
            }
    };
    class Cube : public AShape {
        public:

            Cube() = default;
            Cube(const Math::Point3D origin, double xDim, double yDim, double zDim, std::shared_ptr<RayTracer::Material::IMaterial> material)
                : _material(material), _xDim(xDim), _yDim(yDim), _zDim(zDim)
            {
                _origin = origin;
                initVertexes();
                initFaces();
            }

            void setup(const RayTracer::ShapeConfig& config)
            {
            }

            bool hit(const RayTracer::Ray& ray, RayTracer::Range ray_range, HitData& data) const override
            {
                // call hit for each face
                // update HitData with the closest face's data
                bool isTouched = false;
                for (auto& face : _faces) {
                    if (face.second.hit(ray, ray_range, data)) {
                        data.point = ray.at(data.tValue);
                        data.normal = face.second.getNormalVector();
                        data.determineFace(ray, data.normal);
                        data.material = _material;
                        isTouched = true;
                    }
                }
                return isTouched;
            }

            Math::Point3D center() const { return _origin; }
            double xDim() const { return _xDim; }
            double yDim() const { return _yDim; }
            double zDim() const { return _zDim; }

        protected:
        private:
            double _xDim;
            double _yDim;
            double _zDim;
            std::shared_ptr<RayTracer::Material::IMaterial> _material;
            std::unordered_map<std::string, Math::Point3D> _vertexes;
            std::unordered_map<std::string, CubeFace> _faces;

            double xO() const { return _origin.x(); }
            double yO() const { return _origin.y(); }
            double zO() const { return _origin.z(); }

            Math::Point3D A() { return _vertexes["A"]; }
            Math::Point3D B() { return _vertexes["B"]; }
            Math::Point3D C() { return _vertexes["C"]; }
            Math::Point3D D() { return _vertexes["D"]; }
            Math::Point3D E() { return _vertexes["E"]; }
            Math::Point3D F() { return _vertexes["F"]; }
            Math::Point3D G() { return _vertexes["G"]; }
            Math::Point3D H() { return _vertexes["H"]; }

            CubeFace frontFace() { return _faces["frontFace"]; }
            CubeFace backFace() { return _faces["backFace"]; }
            CubeFace topFace() { return _faces["topFace"]; }
            CubeFace bottomFace() { return _faces["bottomFace"]; }
            CubeFace leftFace() { return _faces["leftFace"]; }
            CubeFace rightFace() { return _faces["rightFace"]; }

            void initVertexes()
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

            void initFaces() {
                _faces["frontFace"] = CubeFace(A(), B(), C(), D(), Math::Vector3D(0, 0, 1));
                _faces["backFace"] = CubeFace(E(), F(), G(), H(), Math::Vector3D(0, 0, 1));
                _faces["topFace"] = CubeFace(E(), F(), A(), B(), Math::Vector3D(0, 1, 0));
                _faces["bottomFace"] = CubeFace(G(), H(), C(), D(), Math::Vector3D(0, 1, 0));
                _faces["leftFace"] = CubeFace(E(), A(), G(), C(), Math::Vector3D(1, 0, 0));
                _faces["rightFace"] = CubeFace(B(), D(), F(), H(), Math::Vector3D(1, 0, 0));
            }
    };
}

#endif /* !CUBE_HPP_ */
