/*
** EPITECH PROJECT, 2024
** RAYTRACER
** File description:
** SFMLButton
*/

#ifndef SFMLBUTTON_HPP_
    #define SFMLBUTTON_HPP_

#include "AGraphicals.hpp"

#include <SFML/Graphics.hpp>
#include <vector>
#include <iostream>
#include <functional>

namespace Graphics
{
    namespace SFML
    {
        class SFMLButton
        {
        public:
            SFMLButton(sf::Vector2f percentPosition, sf::Vector2f percentSize, const std::string &text, sf::Color buttonColor, sf::Color hoverColor, sf::Color textColor)
            {
                m_buttonColor = buttonColor;
                m_hoverColor = hoverColor;
                m_textColor = textColor;

                _percentPosition = percentPosition;
                _percentSize = percentSize;

                m_font.loadFromFile("assets/code.ttf");
                m_text.setCharacterSize(24);
                m_text.setFont(m_font);
                m_text.setString(text);
            }

            void setTriggerFunction(std::function<void(sf::RenderWindow &)> triggerFunction)
            {
                m_triggerFunction = triggerFunction;
            }

            void setButtonColor(const sf::Color &color)
            {
                m_button.setFillColor(color);
            }

            void setTextColor(const sf::Color &color)
            {
                m_text.setFillColor(color);
            }

            bool isHovered(sf::RenderWindow &window, const sf::Vector2f &mousePosition)
            {
                sf::Vector2f buttonPosition = m_button.getPosition();
                sf::Vector2f buttonSize = m_button.getSize();

                if (mousePosition.x >= buttonPosition.x && mousePosition.x <= buttonPosition.x + buttonSize.x)
                {
                    if (mousePosition.y >= buttonPosition.y && mousePosition.y <= buttonPosition.y + buttonSize.y)
                    {
                        return true;
                    }
                }
                return false;
            }

            bool isClicked(sf::RenderWindow &window, const sf::Vector2f &mousePosition, const sf::Event &event)
            {
                if (event.type == sf::Event::MouseButtonPressed)
                {
                    if (event.mouseButton.button == sf::Mouse::Left)
                    {
                        if (isHovered(window, mousePosition))
                        {
                            return true;
                        }
                    }
                }
                return false;
            }

            void setButtonText(const std::string &text)
            {
                m_text.setString(text);
            }

            void render(sf::RenderWindow &window)
            {
                if (isHovered(window, sf::Vector2f(sf::Mouse::getPosition(window))))
                {
                    m_button.setFillColor(m_hoverColor);
                }
                else
                {
                    m_button.setFillColor(m_buttonColor);
                }
                window.draw(m_button);
                if (m_font.getInfo().family != "")
                    window.draw(m_text);
            }

            void update(sf::RenderWindow &window, const sf::Vector2f &mousePosition, const std::vector<sf::Event> &events)
            {
                double sizeX = std::ceil((static_cast<double>(_percentSize.x) / 100.0) * window.getSize().x);
                double sizeY = std::ceil((static_cast<double>(_percentSize.y) / 100.0) * window.getSize().y);
                double posX = ((static_cast<double>(_percentPosition.x) / 100.0) * window.getSize().x);
                double posY = ((static_cast<double>(_percentPosition.y) / 100.0) * window.getSize().y);

                m_button.setSize(sf::Vector2f(sizeX, sizeY));
                m_button.setPosition(sf::Vector2f(posX, posY));

                // set the text to bold
                m_text.setStyle(sf::Text::Bold);

                // increase the text size according to the button size
                m_text.setCharacterSize(sizeY / 2);
                if (sizeX < m_text.getLocalBounds().width)
                    m_text.setCharacterSize(sizeX / 5);

                // center the text on the button
                sf::FloatRect textBounds = m_text.getLocalBounds();
                m_text.setPosition(posX + (sizeX - textBounds.width) / 2, posY + (sizeY - textBounds.height) / 3);

                for (auto &event : events)
                {
                    if (isClicked(window, mousePosition, event))
                    {
                        m_triggerFunction(window);
                    }
                }
            }

        protected:
        private:
            sf::Vector2f _percentPosition;
            sf::Vector2f _percentSize;

            sf::RectangleShape m_button;
            sf::Text m_text;
            sf::Font m_font;

            sf::Color m_buttonColor;
            sf::Color m_hoverColor;
            sf::Color m_textColor;

            std::function<void(sf::RenderWindow &)> m_triggerFunction;
        };

    }
}

#endif /* !SFMLBUTTON_HPP_ */
