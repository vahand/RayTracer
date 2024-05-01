/*
** EPITECH PROJECT, 2024
** RAYTRACER
** File description:
** SFMLDisplay
*/

#ifndef SFMLDisplay_HPP_
#define SFMLDisplay_HPP_

#include "AGraphicals.hpp"

#include <SFML/Graphics.hpp>
#include <vector>
#include <iostream>
#include <functional>

class ResponsiveElement
{
public:
    virtual void update(sf::RenderWindow &window) = 0;
    virtual void render(sf::RenderWindow &window) const = 0;
    virtual void setBackgroundColor(const sf::Color &color) = 0;
};

namespace Graphics
{
    namespace SFML
    {

        class PixelImage
        {
        public:
            PixelImage(int width, int height, sf::Vector2f origin) : m_width(width), m_height(height), m_origin(origin)
            {
                m_image.create(m_width, m_height, sf::Color::Black);
            }

            void setPixelColor(int x, int y, sf::Color color, bool replace = false)
            {
                if (!replace) {
                    if (tmpImage.find(y) != tmpImage.end()){
                        if (tmpImage[y].size() > x) {
                            return;
                        }
                    }
                }

                if (x >= 0 && x < m_width && y >= 0 && y < m_height) {
                    tmpImage[y].push_back(RayTracer::Color(color.r, color.g, color.b));
                    m_image.setPixel(x, y, color);
                }
            }

            void render(sf::RenderWindow& window, sf::Vector2f positionPercent) {
                sf::Vector2u windowSize = window.getSize();

                // Calculate the size of the image
                float size = std::min(windowSize.x, windowSize.y) * 0.5f;
                double aspectRatio = static_cast<double>(m_width) / static_cast<double>(m_height);

                double maxX = windowSize.x * 0.62;
                double maxY = windowSize.y * 0.96;

                double scaleX = maxX / m_width - 0.1;
                double scaleY = maxY / m_height - 0.1;
                double scale = std::min(scaleX, scaleY);

                // Calculate the position based on percentage values
                float x = windowSize.x * (positionPercent.x / 100.0);
                float y = windowSize.y * (positionPercent.y / 100.0);

                // Calculate the position to center the image
                x -= (m_width * scale) / 2 + 10;
                y -= (m_height * scale) / 2;

                // Create a texture from the image
                sf::Texture texture;
                texture.loadFromImage(m_image);

                // Create a sprite to display the texture
                sf::Sprite sprite(texture);
                sprite.setScale(scale, scale);
                sprite.setPosition(x, y);

                // Draw the sprite
                window.draw(sprite);
            }

        private:
            int m_width;
            int m_height;
            sf::Vector2f m_origin;
            sf::Image m_image;

            std::unordered_map<int, std::vector<RayTracer::Color>> tmpImage;
        };

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

            void update(sf::RenderWindow &window) override
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

        /**
         * @brief Class of the SFML Display
         *
         * @details This class is used to create a window with SFML
         */
        class SFMLDisplay : public AGraphicals
        {
        public:
            SFMLDisplay() = default;
            ~SFMLDisplay()
            {
                m_window.close();
            }

            void setup(std::shared_ptr<RayTracer::Core> core, std::shared_ptr<Workers> workers)
            {
                _core = core;
                _workers = workers;
            }

            void createWindow(int width, int height, const std::string &title) override
            {
                std::cerr << "[SFMLDisplay] Creating window with width: " << width << " and height: " << height << " and title: " << title << std::endl;
                if (!m_window.isOpen())
                {
                    sf::VideoMode videoMode(width, height);
                    m_window.create(videoMode, title);
                    displayWindow();
                }
                else
                {
                    m_window.close();
                    createWindow(width, height, title);
                }

                m_window.setFramerateLimit(60);

                m_view = sf::View(sf::FloatRect(0.f, 0.f, static_cast<float>(width), static_cast<float>(height)));
                m_window.setView(m_view);
                _aspect_ratio = static_cast<double>(width) / static_cast<double>(height);

                initRayTracerWindow();
            }

            void initRayTracerWindow()
            {
                std::cerr << "[SFMLDisplay] Initing the RayTracer window" << std::endl;

                if (!m_font.loadFromFile("assets/code.ttf"))
                {
                    std::cerr << "Error: Could not load font" << std::endl;
                }

                double ratioX = 33;
                double leftX = 2 * ratioX;
                double rightX = ratioX;
                double globalY = 100;

                double borderWidth = 1;
                leftX -= borderWidth;
                globalY -= borderWidth * 2;

                m_elements.push_back(std::make_unique<Panel>(sf::Vector2f(0, 0), sf::Vector2f(100, 100)));
                m_elements[0]->setBackgroundColor(sf::Color(0, 50, 70, 255));

                m_elements.push_back(std::make_unique<Panel>(sf::Vector2f(borderWidth, borderWidth), sf::Vector2f(leftX, globalY)));
                m_elements[1]->setBackgroundColor(sf::Color(20, 20, 20, 255));

                m_elements.push_back(std::make_unique<Panel>(sf::Vector2f(leftX + borderWidth, borderWidth), sf::Vector2f(rightX, globalY)));
                m_elements[2]->setBackgroundColor(sf::Color(186, 186, 186, 255));

                std::unique_ptr<SFMLButton> renderButton = std::make_unique<SFMLButton>(sf::Vector2f(66 + 33 / 2 - 14 / 2, 90), sf::Vector2f(14, 6), "RENDER", sf::Color(0, 156, 227), sf::Color(0, 110, 162), sf::Color::White);
                renderButton->setTriggerFunction([this](sf::RenderWindow &window) {
                    std::cerr << "Render button clicked" << std::endl;
                    _workers->initialize(*_core);
                    _workers->beginRender();
                    m_renderedImage = std::make_unique<PixelImage>(_core->_screenWidth, _core->_screenHeight, sf::Vector2f(0, 0));
                    _workers->setRendering(true);
                });

                std::unique_ptr<SFMLButton> fastRenderButton = std::make_unique<SFMLButton>(sf::Vector2f(66 + 33 / 2 - 14 / 2, 85), sf::Vector2f(14, 4), "FAST-RENDER", sf::Color(0, 170, 100), sf::Color(0, 100, 60), sf::Color::White);
                fastRenderButton->setTriggerFunction([this](sf::RenderWindow &window) {
                    std::cerr << "Render button clicked" << std::endl;
                });

                m_buttons.push_back(std::move(renderButton));
                m_buttons.push_back(std::move(fastRenderButton));

                m_renderedImage = std::make_unique<PixelImage>(1280, 720, sf::Vector2f(0, 0));
                for (int x = 0; x < 1280; x++)
                {
                    for (int y = 0; y < 720; y++)
                    {
                        sf::Color randomColor(rand() % 256, rand() % 256, rand() % 256);
                        m_renderedImage->setPixelColor(x, y, randomColor);
                    }
                }
            }

            int getWindowWidth() const
            {
                return m_window.getSize().x;
            }

            int getWindowHeight() const
            {
                return m_window.getSize().y;
            }

            void closeWindow() override
            {
                m_window.close();
            }

            bool isWindowOpen() override
            {
                return m_window.isOpen();
            }

            void clearWindow() override
            {
                m_window.clear();
            }

            void displayWindow() override
            {
                m_window.display();
            }

            void getEvents() override
            {
                sf::Event event;
                while (m_window.pollEvent(event))
                {
                    if (event.type == sf::Event::KeyPressed || event.type == sf::Event::MouseButtonPressed)
                        m_events.push_back(event);
                    if (event.type == sf::Event::Closed)
                    {
                        m_window.close();
                    }
                    if (event.type == sf::Event::Resized)
                        onResize();
                }
            }

            void onResize()
            {
                sf::Vector2u windowSize = m_window.getSize();
                sf::Vector2f viewSize(windowSize.x, windowSize.y);

                sf::View view(sf::FloatRect(0.f, 0.f, viewSize.x, viewSize.y));
                view.setViewport(sf::FloatRect(0.f, 0.f, 1.f, 1.f));
                view.setCenter(viewSize / 2.f);
                m_view = view;
                m_window.setView(m_view);
            }

            void updateRenderedImage(const std::unordered_map<int, std::vector<RayTracer::Color>> image, bool replace = false)
            {
                if (image.empty())
                    return;
                for (auto &line : image)
                {
                    for (int x = 0; x < line.second.size(); x++)
                    {
                        RayTracer::Color color = line.second[x];
                        sf::Color sfColor(color._r, color._g, color._b, 255);
                        m_renderedImage->setPixelColor(x, line.first, sfColor, replace);
                    }
                }
            }

            void renderAll() override
            {
                getEvents();

                clearWindow();

                for (auto &element : m_elements)
                {
                    element->update(m_window);
                    element->render(m_window);
                }

                for (auto &button : m_buttons)
                {
                    button->update(m_window, sf::Vector2f(sf::Mouse::getPosition(m_window)), m_events);
                    button->render(m_window);
                }

                if (m_renderedImage) {
                    m_renderedImage->render(m_window, sf::Vector2f(34, 50));

                    if (_workers->isRendering()) {
                        _workers->renderUpdate(*_core);

                        _workers->placeholderMutex.lock();
                        updateRenderedImage(_workers->placeholderImage, !_workers->isRendering());
                        _workers->placeholderMutex.unlock();
                    }
                }

                m_events.clear();
                displayWindow();
            }

        protected:
        private:
            sf::RenderWindow m_window;
            sf::View m_view;
            sf::Font m_font;
            double _aspect_ratio;

            std::vector<std::unique_ptr<Graphics::SFML::SFMLButton>> m_buttons;
            std::vector<std::unique_ptr<ResponsiveElement>> m_elements;

            std::unique_ptr<PixelImage> m_renderedImage;
            bool _finalDisplay = false;
            std::vector<sf::Event> m_events;

            // RayTracer::Core _core;
            // Workers _workers;
            std::shared_ptr<RayTracer::Core> _core;
            std::shared_ptr<Workers> _workers;
        };

    }
}

#endif /* !SFMLDisplay_HPP_ */
