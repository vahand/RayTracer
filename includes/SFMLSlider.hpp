/*
** EPITECH PROJECT, 2024
** RAYTRACER
** File description:
** SFMLSlider
*/

#ifndef SFMLSLIDER_HPP_
    #define SFMLSLIDER_HPP_

#include "AGraphicals.hpp"
#include "SFMLResponsive.hpp"

namespace Graphics {
    namespace SFML {
        class SFMLSlider : public ResponsiveElement {
            public:
                SFMLSlider(
                    sf::Vector2i range,
                    int value,
                    sf::Color backgroundColor,
                    sf::Color sliderColor,
                    sf::Vector2f percentPosition,
                    sf::Vector2f percentSize,
                    std::string name = "Slider",
                    std::function<void(void)> callback = nullptr,
                    bool callbackEveryActions = false
                ) {
                    _range = range;
                    _value = value;
                    m_backgroundColor = backgroundColor;
                    m_sliderColor = sliderColor;
                    _percentPosition = percentPosition;
                    _percentSize = percentSize;

                    m_background.setSize(sf::Vector2f(0, 0));
                    m_slider.setSize(sf::Vector2f(0, 0));

                    m_font.loadFromFile("assets/code.ttf");
                    m_textValue.setCharacterSize(24);
                    m_textValue.setFont(m_font);
                    m_textValue.setString("0/0");

                    m_textName.setCharacterSize(24);
                    m_textName.setFont(m_font);
                    m_textName.setString(name);

                    _callback = callback;
                    _callbackEveryActions = callbackEveryActions;
                    m_textValue.setString(std::to_string(_value) + "/" + std::to_string(_range.y));
                };
                ~SFMLSlider() = default;

                void setSliderColor(const sf::Color &color) {
                    m_sliderColor = color;
                    m_slider.setFillColor(m_sliderColor);
                }

                void setBackgroundColor(const sf::Color &color) override {
                    m_backgroundColor = color;
                    m_background.setFillColor(m_backgroundColor);
                }

                void setValue(int value, bool callback = false) {
                    _value = value;
                    if (_value <= _range.x)
                        _value = _range.x;
                    if (_value >= _range.y)
                        _value = _range.y;

                    m_textValue.setString(std::to_string(_value) + "/" + std::to_string(_range.y));
                    if (callback && _callback)
                        _callback();
                }

                void setRange(sf::Vector2i range) {
                    _range = range;
                }

                void render(sf::RenderWindow &window) const override {
                    window.draw(m_background);
                    window.draw(m_slider);
                    window.draw(m_textValue);
                    window.draw(m_textName);
                }

                bool isHovered(sf::RenderWindow &window, double posX, double posY, double sizeX, double sizeY) {
                    sf::Vector2i mousePos = sf::Mouse::getPosition(window);
                    if (mousePos.x >= posX && mousePos.x < posX + sizeX + 1)
                        if (mousePos.y >= posY && mousePos.y <= posY + sizeY + 1)
                            return true;
                    return false;
                }

                void update(sf::RenderWindow &window, bool locked = false) override {
                    double sizeX = std::ceil((static_cast<double>(_percentSize.x) / 100.0) * window.getSize().x);
                    double sizeY = std::ceil((static_cast<double>(_percentSize.y) / 100.0) * window.getSize().y);
                    double posX = ((static_cast<double>(_percentPosition.x) / 100.0) * window.getSize().x);
                    double posY = ((static_cast<double>(_percentPosition.y) / 100.0) * window.getSize().y);

                    m_textName.setFillColor(sf::Color::White);
                    m_textName.setStyle(sf::Text::Bold);
                    m_textName.setCharacterSize(sizeY / 1.2);
                    double width = m_textName.getLocalBounds().width;
                    if (sizeX < m_textName.getLocalBounds().width)
                        m_textName.setCharacterSize(sizeX / 2);
                    posX -= width;
                    m_textName.setPosition(posX, posY - 5);
                    posX += m_textName.getLocalBounds().width + 15;

                    static bool isDragging = false;
                    static int prevValue = _value;
                    if (!locked) {
                        sf::Vector2i mousePos = sf::Mouse::getPosition(window);
                        if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
                            if (isHovered(window, posX, posY, sizeX, sizeY)) {
                                isDragging = true;
                                _value = ((mousePos.x - posX) * (_range.y - _range.x) / sizeX) + _range.x;
                            }
                            setValue(_value, _callbackEveryActions);
                        } else {
                            if (isDragging) {
                                isDragging = false;
                                if (_value != prevValue) {
                                    setValue(_value, true);
                                    prevValue = _value;
                                }
                            }
                        }

                        if (isHovered(window, posX, posY, sizeX, sizeY)) {
                            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
                                _value -= 1;
                                setValue(_value, true);
                            }
                            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
                                _value += 1;
                                setValue(_value, true);
                            }
                        }
                    }

                    m_background.setSize(sf::Vector2f(sizeX, sizeY));
                    m_background.setPosition(posX, posY);
                    m_background.setFillColor(m_backgroundColor);

                    int percentLoaded = (_value - _range.x) * 100 / (_range.y - _range.x);
                    m_slider.setSize(sf::Vector2f((m_background.getSize().x * percentLoaded) / 100, m_background.getSize().y));
                    m_slider.setPosition(posX, posY);
                    m_slider.setFillColor(m_sliderColor);

                    sf::FloatRect textRect = m_textValue.getLocalBounds();
                    m_textValue.setOrigin(textRect.left + textRect.width / 2.0f, textRect.top + textRect.height / 2.0f);
                    m_textValue.setPosition(posX + sizeX + 10 + textRect.width / 2.0f, posY + sizeY / 2.0f);
                    m_textValue.setFillColor(sf::Color::White);
                    m_textValue.setStyle(sf::Text::Bold);
                    m_textValue.setCharacterSize(sizeY / 1.5);
                    if (sizeX < m_textValue.getLocalBounds().width)
                        m_textValue.setCharacterSize(sizeX / 3);
                }

                int getValue() const override {
                    return _value;
                }

            private:
                sf::RectangleShape m_background;
                sf::RectangleShape m_slider;
                sf::Color m_backgroundColor;
                sf::Color m_sliderColor;
                sf::Vector2f _percentPosition;
                sf::Vector2f _percentSize;
                sf::Vector2i _range;
                int _value;
                std::function<void(void)> _callback;
                bool _callbackEveryActions = false;

                sf::Text m_textValue;
                sf::Text m_textName;
                sf::Font m_font;
        };
    }
}

#endif /* !SFMLSLIDER_HPP_ */
