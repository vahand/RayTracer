/*
** EPITECH PROJECT, 2024
** RAYTRACER
** File description:
** SFMLSelector
*/

#ifndef SFMLSELECTOR_HPP_
#define SFMLSELECTOR_HPP_

#include "AGraphicals.hpp"
#include "SFMLResponsive.hpp"

#include <SFML/Graphics.hpp>
#include <vector>
#include <iostream>
#include <functional>

namespace Graphics {
    namespace SFML {
        class SFMLSelector : public ResponsiveElement {
            public:
                SFMLSelector(sf::Vector2f percentPosition, sf::Vector2f percentSize, sf::Color backgroundColor, sf::Color hoverColor, sf::Color textColor, std::function<void()> contentGetterFunction, bool avoidLocking = false)
                    :   _percentPosition(percentPosition), _percentSize(percentSize), _avoidLocking(avoidLocking)
                {
                    m_rect.setFillColor(backgroundColor);
                    m_rect.setOutlineThickness(2);
                    m_rect.setOutlineColor(hoverColor);

                    m_font.loadFromFile("assets/code.ttf");
                    m_text.setCharacterSize(24);
                    m_text.setFont(m_font);
                    m_text.setString("<Empty>");
                    m_text.setFillColor(textColor);
                    m_text.setStyle(sf::Text::Bold);

                    _contentGetter = contentGetterFunction;
                    _contentGetter();
                }

                ~SFMLSelector() = default;

                void setBackgroundColor(const sf::Color &color) override {
                    m_rect.setFillColor(color);
                }

                int getValue() const override {
                    return m_selectedIndex;
                }

                void setContent(const std::vector<std::string> content) {
                    m_content = content;
                }

                void setHoverColor(const sf::Color &color) {
                    m_rect.setOutlineColor(color);
                }

                void setTextColor(const sf::Color &color) {
                    m_text.setFillColor(color);
                }

                bool isHovered(sf::RenderWindow &window, const sf::Vector2f &mousePosition)
                {
                    sf::Vector2f buttonPosition = m_rect.getPosition();
                    sf::Vector2f buttonSize = m_rect.getSize();

                    if (mousePosition.x >= buttonPosition.x && mousePosition.x <= buttonPosition.x + buttonSize.x &&
                        mousePosition.y >= buttonPosition.y && mousePosition.y <= buttonPosition.y + buttonSize.y) {
                        return true;
                    }
                    return false;
                }

                void render(sf::RenderWindow &window) const override
                {
                    window.draw(m_rect);
                    if (m_font.getInfo().family != "")
                        window.draw(m_text);
                }

                void update(sf::RenderWindow &window, bool locked = false) override
                {
                    double sizeX = std::ceil((static_cast<double>(_percentSize.x) / 100.0) * window.getSize().x);
                    double sizeY = std::ceil((static_cast<double>(_percentSize.y) / 100.0) * window.getSize().y);
                    double posX = ((static_cast<double>(_percentPosition.x) / 100.0) * window.getSize().x);
                    double posY = ((static_cast<double>(_percentPosition.y) / 100.0) * window.getSize().y);

                    m_rect.setSize(sf::Vector2f(sizeX, sizeY));
                    m_rect.setPosition(sf::Vector2f(posX, posY));

                    if (_avoidLocking)
                        locked = false;

                    if (isHovered(window, sf::Vector2f(sf::Mouse::getPosition(window)))) {
                        m_rect.setOutlineColor(sf::Color::White);
                    } else
                        m_rect.setOutlineColor(sf::Color::Transparent);

                    if (locked)
                        m_rect.setFillColor(sf::Color(100, 100, 100));
                    else
                        m_rect.setFillColor(sf::Color(50, 50, 50));

                    if (m_content.size() > 0)
                        m_text.setString(m_content[m_selectedIndex]);
                    else
                        m_text.setString("<Empty>");

                    m_text.setStyle(sf::Text::Bold);

                    m_text.setCharacterSize(sizeY / 2);
                    if (sizeX < m_text.getLocalBounds().width)
                        m_text.setCharacterSize(sizeX / 5);

                    sf::FloatRect textRect = m_text.getLocalBounds();
                    m_text.setOrigin(textRect.left + textRect.width / 2.0f, textRect.top + textRect.height / 2.0f);
                    m_text.setPosition(m_rect.getPosition().x + m_rect.getSize().x / 2, m_rect.getPosition().y + m_rect.getSize().y / 2);

                    render(window);
                }


            private:
                sf::Vector2f _percentPosition;
                sf::Vector2f _percentSize;
                sf::RectangleShape m_rect;

                std::vector<std::string> m_content;
                int m_selectedIndex = 0;

                sf::Text m_text;
                sf::Font m_font;

                bool _avoidLocking = false;
                std::function<void()> _contentGetter;

        };
    }
}

#endif /* !SFMLSELECTOR_HPP_ */
