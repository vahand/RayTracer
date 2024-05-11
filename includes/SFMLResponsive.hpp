/*
** EPITECH PROJECT, 2024
** RAYTRACER
** File description:
** SFMLResponsive
*/

#ifndef SFMLRESPONSIVE_HPP_
    #define SFMLRESPONSIVE_HPP_

#include <SFML/Graphics.hpp>
#include <vector>
#include <iostream>
#include <functional>

namespace Graphics {
    namespace SFML {
        class ResponsiveElement {
            public:
                virtual void update(sf::RenderWindow &window, bool locked = false) = 0;
                virtual void render(sf::RenderWindow &window) const = 0;
                virtual void setBackgroundColor(const sf::Color &color) = 0;

                virtual int getValue() const { return -1; };
                virtual void setContent(const std::vector<std::string> content) {};
        };
    }
}

#endif /* !SFMLRESPONSIVE_HPP_ */
