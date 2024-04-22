/*
** EPITECH PROJECT, 2024
** BS_RAYTRACER
** File description:
** Core
*/

#include "../includes/Core.hpp"

RayTracer::Core::Core(int screenWidth, int screenHeight)
{
    _screenWidth = screenWidth;
    _screenHeight = screenHeight;

    Math::Point3D cameraPosition(0, 0, 0);
    Math::Vector3D camera_direction(0, 0, 1);
    Math::Vector3D camera_up(0, 1, 0);
    double aspect_ratio = static_cast<double>(screenWidth / screenHeight);
    double fov = 30;

    this->_camera = RayTracer::Camera(cameraPosition, camera_direction, camera_up, aspect_ratio, fov);

}

void RayTracer::Core::writeColor(RayTracer::Color &color)
{
    int r = color._r;
    int g = color._g;
    int b = color._b;

    std::cout << r << ' ' << g << ' ' << b << '\n';
}

void RayTracer::Core::run()
{
    std::cout << "P3\n" << this->_screenWidth << ' ' << this->_screenHeight << "\n255\n";

    for (int y = this->_screenHeight; y > 0; y--) {
        for (int x = 0; x < this->_screenWidth; x++) {
            double u = static_cast<double>(x) / this->_screenWidth;
            double v = static_cast<double>(y) / this->_screenHeight;

            Ray ray = this->_camera.ray(u, v);
            // std::cerr << "Ray: " << u << " " << v << std::endl;

            std::unique_ptr<RayTracer::Color> finalColor = nullptr;

            for (auto &shape : this->_shapes) {
                // std::cerr << "Shape: " << shape.get().getColor()._r << " " << shape.get().getColor()._g << " " << shape.get().getColor()._b << std::endl;
                RayTracer::HitResult hitResult = shape.get().hits(ray);

                if (hitResult.hit) {
                    // std::cerr << "Hit at: " << hitResult.intersectionPoint.x() << " " << hitResult.intersectionPoint.y() << " " << hitResult.intersectionPoint.z() << std::endl;
                    Math::Point3D intersectionPoint = hitResult.intersectionPoint;

                    // loop over light and loop over objects
                    for (auto &light : this->_lights) {
                        // std::cerr << "Light: " << light.get().position().x() << " " << light.get().position().y() << " " << light.get().position().z() << std::endl;

                        Ray rayToLight = Ray(intersectionPoint, light.get().position() - intersectionPoint);
                        double distanceToLight = rayToLight.direction().magnitude();

                        for (auto &innerObj : this->_shapes) {
                            std::cerr << "Shape: " << shape.get().getColor()._r << " " << shape.get().getColor()._g << " " << shape.get().getColor()._b << std::endl;
                            if (innerObj.get() == shape.get()) {
                                RayTracer::Color pixelColor = shape.get().getColor();
                                // pixelColor.applyIntensity(light.get().intensity());
                                pixelColor.setBrightnessFromDistanceToLight(distanceToLight, light.get().intensity());
                                if (finalColor == nullptr) {
                                    finalColor = std::make_unique<RayTracer::Color>(pixelColor);
                                } else {
                                    finalColor->colorAverage(pixelColor);
                                }
                                continue;
                            }

                            RayTracer::HitResult hitResult = innerObj.get().hits(rayToLight);
                            RayTracer::Color pixelColor = shape.get().getColor();

                            if (hitResult.hit) {
                                std::cerr << "Hit" << std::endl;
                                pixelColor = RayTracer::Color(0, 0, 0);
                                pixelColor.colorAverage(innerObj.get().getColor());
                                pixelColor.setBrightnessFromDistanceToLight(distanceToLight, light.get().intensity());
                                // pixelColor.applyIntensity(light.get().intensity());
                                if (finalColor == nullptr) {
                                    finalColor = std::make_unique<RayTracer::Color>(pixelColor);
                                } else {
                                    finalColor->colorAverage(pixelColor);
                                }
                                break;
                            } else {
                                std::cerr << "No hit" << std::endl;
                                pixelColor = shape.get().getColor();
                                pixelColor.setBrightnessFromDistanceToLight(distanceToLight, light.get().intensity());
                                // pixelColor.applyIntensity(light.get().intensity());
                                if (finalColor == nullptr) {
                                    finalColor = std::make_unique<RayTracer::Color>(pixelColor);
                                } else {
                                    finalColor->colorAverage(pixelColor);
                                }
                            }
                        }
                    }
                }

            }

            if (finalColor != nullptr) {
                writeColor(*finalColor);
            } else {
                RayTracer::Color color = RayTracer::Color(0, 0, 0);
                writeColor(color);
            }
        }
    }
}

RayTracer::Color RayTracer::Core::castLight(const RayTracer::Ray &ray) const
{
    (void)ray;
    return RayTracer::Color();
}