/*
** EPITECH PROJECT, 2024
** RAYTRACER
** File description:
** SFMLDisplay
*/

#ifndef SFMLDisplay_HPP_
    #define SFMLDisplay_HPP_

#include "AGraphicals.hpp"
#include "SFMLSelector.hpp"
#include "SFMLButton.hpp"
#include "SFMLSlider.hpp"
#include "SFMLPixelImage.hpp"
#include "SFMLPanel.hpp"
#include "SFMLResponsive.hpp"

namespace Graphics
{
    namespace SFML
    {
        /**
         * @brief Class of the SFML Display
         *
         * @details This class is used to create a window with SFML
         */
        class SFMLDisplay : public AGraphicals
        {
        public:
            SFMLDisplay() = default;
            ~SFMLDisplay() {
                m_window.close();
            }

            void setup(std::shared_ptr<RayTracer::Core> core, std::shared_ptr<Workers> workers)
            {
                _core = core;
                _workers = workers;
            }

            void createWindow(int width, int height, const std::string &title, std::shared_ptr<RayTracer::FileManager> manager) override;
            void initRayTracerWindow();

            int getWindowWidth() const { return m_window.getSize().x; }
            int getWindowHeight() const { return m_window.getSize().y; }
            void closeWindow() override { m_window.close(); }
            bool isWindowOpen() override { return m_window.isOpen(); }
            void clearWindow() override { m_window.clear(); }
            void displayWindow() override { m_window.display(); }

            void getEvents() override
            {
                sf::Event event;
                while (m_window.pollEvent(event))
                {
                    if (event.type == sf::Event::KeyPressed || event.type == sf::Event::MouseButtonPressed)
                        m_events.push_back(event);
                    if (event.type == sf::Event::Closed || (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape)) {
                        if (_workers->isRendering()) {
                            _workers->setRendering(false);
                            _workers->waitForWorkersEnd();
                        }
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

            void updateRenderedImage(const std::unordered_map<int, std::unique_ptr<std::vector<RayTracer::Color>>> &image);
            void renderAll() override;

        protected:
        private:
            sf::RenderWindow m_window;
            sf::View m_view;
            sf::Font m_font;
            double _aspectRatio;

            std::vector<std::unique_ptr<Graphics::SFML::SFMLButton>> m_buttons;
            std::vector<std::unique_ptr<ResponsiveElement>> m_elements;

            bool _fastRendering = false;
            std::unique_ptr<PixelImage> m_renderedImage;
            bool _finalDisplay = false;
            std::vector<sf::Event> m_events;
            bool _locked = false;
            std::chrono::time_point<std::chrono::high_resolution_clock> _startLockTime;

            std::shared_ptr<RayTracer::Core> _core;
            std::shared_ptr<Workers> _workers;
            std::shared_ptr<RayTracer::FileManager> _manager;
        };

    }
}

#endif /* !SFMLDisplay_HPP_ */
