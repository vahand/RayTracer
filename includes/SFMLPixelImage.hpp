/*
** EPITECH PROJECT, 2024
** RAYTRACER
** File description:
** SFMLPixelImage
*/

#ifndef SFMLPIXELIMAGE_HPP_
    #define SFMLPIXELIMAGE_HPP_

#include "Point3D.hpp"
#include "Color.hpp"

#include <SFML/Graphics.hpp>
#include <unordered_map>

namespace Graphics
{
    namespace SFML
    {

        class PixelImage
        {
        public:
            PixelImage(int width, int height, sf::Vector2f origin)
                : m_width(width), m_height(height), m_origin(origin) {
                m_image.create(m_width, m_height, sf::Color::Black);

                for (int y = 0; y < m_height; y++) {
                    tmpImage[y].reserve(m_width);
                    for (int x = 0; x < m_width; x++) {
                        sf::Color color = sf::Color::Black;
                        tmpImage[y].push_back(color);
                    }
                }
            }
            ~PixelImage() = default;

            void setPixelColor(int x, int y, RayTracer::Color color) {
                if (x >= 0 && x < m_width && y >= 0 && y < m_height) {
                    tmpImage[y][x] = sf::Color(color._r, color._g, color._b);
                    m_image.setPixel(x, y, tmpImage[y][x]);
                }
            }

            void render(sf::RenderWindow& window, sf::Vector2f positionPercent) {
                sf::Vector2u windowSize = window.getSize();

                float size = std::min(windowSize.x, windowSize.y) * 0.5f;
                double aspectRatio = static_cast<double>(m_width) / static_cast<double>(m_height);

                double maxX = windowSize.x * 0.62;
                double maxY = windowSize.y * 0.96;
                double scaleX = maxX / m_width - 0.1;
                double scaleY = maxY / m_height - 0.1;
                double scale = std::min(scaleX, scaleY);

                float x = windowSize.x * (positionPercent.x / 100.0) - (m_width * scale) / 2 + 10;
                float y = windowSize.y * (positionPercent.y / 100.0) - (m_height * scale) / 2;

                sf::Texture texture;
                texture.loadFromImage(m_image);
                sf::Sprite sprite(texture);
                sprite.setScale(scale, scale);
                sprite.setPosition(x, y);

                window.draw(sprite);
            }

            sf::Vector2i getImageSize() const {
                return sf::Vector2i(m_width, m_height);
            }

        private:
            int m_width;
            int m_height;
            sf::Vector2f m_origin;
            sf::Image m_image;

            std::unordered_map<int, std::vector<sf::Color>> tmpImage;
        };
    }
}


#endif /* !SFMLPIXELIMAGE_HPP_ */
