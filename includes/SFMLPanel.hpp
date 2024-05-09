/*
** EPITECH PROJECT, 2024
** RAYTRACER
** File description:
** SFMLPanel
*/

#ifndef SFMLPANEL_HPP_
    #define SFMLPANEL_HPP_

#include "SFMLResponsive.hpp"
#include <SFML/Graphics.hpp>
#include <cmath>

namespace Graphics
{
    namespace SFML
    {

        class Panel : public ResponsiveElement
        {
        public:
            Panel(const sf::Vector2f &positionPercent, const sf::Vector2f &sizePercent)
            {
                _positionPercent = positionPercent;
                _sizePercent = sizePercent;

                _panel = sf::RectangleShape(sf::Vector2f(0, 0));
                _defaultAspectRatio = 16.0 / 9.0;
            }

            void update(sf::RenderWindow &window, bool locked = false) override
            {
                double sizeX = std::ceil((static_cast<double>(_sizePercent.x) / 100.0) * window.getSize().x);
                double sizeY = std::ceil((static_cast<double>(_sizePercent.y) / 100.0) * window.getSize().y);
                double posX = ((static_cast<double>(_positionPercent.x) / 100.0) * window.getSize().x);
                double posY = ((static_cast<double>(_positionPercent.y) / 100.0) * window.getSize().y);

                _size = sf::Vector2f(sizeX, sizeY);
                _position = sf::Vector2f(posX, posY);

                _panel.setSize(_size);
                _panel.setPosition(_position);
                _panel.setFillColor(_backgroundColor);
            }

            void render(sf::RenderWindow &window) const override
            {
                window.draw(_panel);
            }

            void setBackgroundColor(const sf::Color &color)
            {
                _backgroundColor = color;
            }

        private:
            sf::Vector2f _positionPercent;
            sf::Vector2f _sizePercent;

            sf::Vector2f _position;
            sf::Vector2f _size;

            sf::RectangleShape _panel;
            double _defaultAspectRatio;

            sf::Color _backgroundColor = sf::Color(20, 20, 20, 255);
        };
    }
}

#endif /* !SFMLPANEL_HPP_ */
