/*
** EPITECH PROJECT, 2024
** RAYTRACER
** File description:
** SFMLDisplay
*/

#include "../includes/SFMLDisplay.hpp"

void Graphics::SFML::SFMLDisplay::createWindow(int width, int height, const std::string &title, std::shared_ptr<RayTracer::FileManager> manager)
{
    _manager = manager;

    std::cerr << "[SFMLDisplay] Creating window with width: " << width << " and height: " << height << " and title: " << title << std::endl;
    if (!m_window.isOpen()) {
        sf::VideoMode videoMode(width, height);
        m_window.create(videoMode, title);
        displayWindow();
    } else {
        m_window.close();
        createWindow(width, height, title, std::move(_manager));
    }

    m_window.setFramerateLimit(60);

    m_view = sf::View(sf::FloatRect(0.f, 0.f, static_cast<float>(width), static_cast<float>(height)));
    m_window.setView(m_view);
    _aspectRatio = static_cast<double>(width) / static_cast<double>(height);

    initRayTracerWindow();
}

void Graphics::SFML::SFMLDisplay::initRayTracerWindow()
{
    std::cerr << "[SFMLDisplay] Initing the RayTracer window" << std::endl;

    if (!m_font.loadFromFile("assets/code.ttf")) {
        std::cerr << "Error: Could not load font" << std::endl;
    }

    double ratioX = 33;
    double leftX = 2 * ratioX;
    double rightX = ratioX;
    double globalY = 100;
    double borderWidth = 1;

    leftX -= borderWidth;
    globalY -= borderWidth * 2;

    //? PANELS CREATION
    m_elements.push_back(std::make_unique<Panel>(sf::Vector2f(0, 0), sf::Vector2f(100, 100)));
    m_elements[0]->setBackgroundColor(sf::Color(0, 50, 70, 255));
    m_elements.push_back(std::make_unique<Panel>(sf::Vector2f(borderWidth, borderWidth), sf::Vector2f(leftX, globalY)));
    m_elements[1]->setBackgroundColor(sf::Color(20, 20, 20, 255));
    m_elements.push_back(std::make_unique<Panel>(sf::Vector2f(leftX + borderWidth, borderWidth), sf::Vector2f(rightX, globalY)));
    m_elements[2]->setBackgroundColor(sf::Color(186, 186, 186, 255));

    //? FOV SLIDER
    m_elements.push_back(std::make_unique<SFMLSlider>(
        sf::Vector2i(30, 150),
        _core->_camera._fovInDegrees,
        sf::Color(0, 156, 227),
        sf::Color(0, 110, 162),
        sf::Vector2f(66 + 33/2 - 16/2, 5),
        sf::Vector2f(16, 2),
        "FOV",
        [this]() {
            if (_workers->isRendering())
                return;
            _core->_camera._fovInDegrees = m_elements[3]->getValue();
            _core->_camera.initialize();
            _fastRendering = true;
            _workers->beginRender();
            _workers->setRendering(true);
        }
    ));

    //? SAMPLES SLIDER
    m_elements.push_back(std::make_unique<SFMLSlider>(
        sf::Vector2i(10, 5000),
        _core->_camera._samples,
        sf::Color(0, 156, 227),
        sf::Color(0, 110, 162),
        sf::Vector2f(66 + 33/2 - 16/2, 10),
        sf::Vector2f(16, 2),
        "SAMPLES",
        [this]() {
            if (_workers->isRendering())
                return;
            _core->_camera._samples = m_elements[4]->getValue();
            _core->_camera.initialize();
        },
        true
    ));

    //? CAMERA ROTATION SLIDER (Y axis)
    m_elements.push_back(std::make_unique<SFMLSlider>(
        sf::Vector2i(0, 360),
        0,
        sf::Color(0, 156, 227),
        sf::Color(0, 110, 162),
        sf::Vector2f(66 + 33/2 - 16/2, 15),
        sf::Vector2f(16, 2),
        "CAMERA",
        [this]() {
            if (_workers->isRendering())
                return;
            double angle = m_elements[5]->getValue();
            std::cerr << "Angle: " << angle << std::endl;
            if (angle < 0)
                angle = 360 + angle;
            _core->_camera.setRotationAroundFocus(angle);
            _core->_camera.initialize();
            _fastRendering = true;
            _workers->beginRender();
            _workers->setRendering(true);
        }
    ));

    //? SCENE LOADER SELECTOR
    m_elements.push_back(std::make_unique<SFMLSelector>(
        sf::Vector2f(66 + 33/2 - 14/2 - 3, 20),
        sf::Vector2f(14, 3),
        sf::Color(0, 156, 227),
        sf::Color(0, 110, 162),
        sf::Color::White,
        // _manager->getScenes()
    ));

    //* LOAD BUTTON
    std::unique_ptr<SFMLButton> loadButton = std::make_unique<SFMLButton>(
        sf::Vector2f(66 + 33/2 + 14/2 + 3, 20),
        sf::Vector2f(4, 3),
        "LOAD",
        sf::Color(0, 156, 227),
        sf::Color(0, 110, 162),
        sf::Color::White
    );
    loadButton->setTriggerFunction([this](sf::RenderWindow &window) {
        if (_workers->isRendering())
            return;
        // std::string scenePath = m_elements[6]->getValue();
        // _core->loadScene(scenePath);
        // _fastRendering = true;
        // _workers->beginRender();
        // _workers->setRendering(true);
    });
    m_buttons.push_back(std::move(loadButton));

    //? Render Button
    std::unique_ptr<SFMLButton> renderButton = std::make_unique<SFMLButton>(sf::Vector2f(66 + 33 / 2 - 14 / 2, 90), sf::Vector2f(14, 6), "RENDER", sf::Color(0, 156, 227), sf::Color(0, 110, 162), sf::Color::White);
    renderButton->setTriggerFunction([this](sf::RenderWindow &window) {
        std::cerr << "Render button clicked" << std::endl;
        if (_workers->isRendering() && !_locked)
            return;
        _locked = true;
        _fastRendering = false;
        _workers->beginRender();
        _workers->setRendering(true);
    });
    m_buttons.push_back(std::move(renderButton));

    //? Fast Render Button
    std::unique_ptr<SFMLButton> fastRenderButton = std::make_unique<SFMLButton>(sf::Vector2f(66 + 33 / 2 - 14 / 2, 85), sf::Vector2f(14, 4), "FAST-RENDER", sf::Color(0, 170, 100), sf::Color(0, 100, 60), sf::Color::White);
    fastRenderButton->setTriggerFunction([this](sf::RenderWindow &window) {
        std::cerr << "FastRender button clicked" << std::endl;
        if (_workers->isRendering() && !_locked)
            return;
        _locked = true;
        _fastRendering = true;
        _workers->beginRender();
        _workers->setRendering(true);
    });
    m_buttons.push_back(std::move(fastRenderButton));

    //? SAVE Button
    std::unique_ptr<SFMLButton> saveButton = std::make_unique<SFMLButton>(sf::Vector2f(66+33/2+14/2+1, 85), sf::Vector2f(6, 11), "SAVE", sf::Color(0, 155, 87), sf::Color(0, 110, 62), sf::Color::White);
    saveButton->setTriggerFunction([this](sf::RenderWindow &window) {
        if (_workers->isRendering())
            return;
        time_t now = time(0);
        tm *ltm = localtime(&now);
        std::string filename = "saved_" + std::to_string(ltm->tm_hour) + "_" + std::to_string(ltm->tm_min) + "_" + std::to_string(ltm->tm_sec) + ".ppm";
        _workers->writeImageToFile(filename);
    });
    m_buttons.push_back(std::move(saveButton));

    //? STOP Button
    std::unique_ptr<SFMLButton> stopButton = std::make_unique<SFMLButton>(sf::Vector2f(66 + 33/2 - 14, 85), sf::Vector2f(6, 11), "STOP", sf::Color(255, 0, 0), sf::Color(156, 0, 0), sf::Color::White, true);
    stopButton->setTriggerFunction([this](sf::RenderWindow &window) {
        if (_workers->isRendering()) {
            _workers->setRendering(false);
            _workers->waitForWorkersEnd();
        }
    });
    m_buttons.push_back(std::move(stopButton));

    //? Placeholder Image initialization
    m_renderedImage = std::make_unique<PixelImage>(_core->_screenWidth, _core->_screenHeight, sf::Vector2f(0, 0));
    for (int y = 0; y < _core->_screenHeight; y++)
    {
        for (int x = 0; x < _core->_screenWidth; x++)
        {
            RayTracer::Color randomColor(rand() % 256, rand() % 256, rand() % 256);
            m_renderedImage->setPixelColor(x, y, randomColor);
        }
    }
}

void Graphics::SFML::SFMLDisplay::updateRenderedImage(const std::unordered_map<int, std::unique_ptr<std::vector<RayTracer::Color>>> &image)
{
    if (image.empty())
        return;
    for (auto &line : image)
    {
        for (int x = 0; x < line.second->size(); x++)
        {
            RayTracer::Color color = line.second->at(x);
            m_renderedImage->setPixelColor(x, line.first, color);
        }
    }
}

void Graphics::SFML::SFMLDisplay::renderAll()
{
    if (!_workers->isRendering()) {
        if (_manager->checkForSceneEdition()) {
            _fastRendering = true;
            _workers->beginRender();
            _workers->setRendering(true);
        }
    }

    getEvents();
    clearWindow();

    for (auto &element : m_elements) {
        element->update(m_window);
        element->render(m_window);
    }

    for (auto &button : m_buttons) {
        button->update(m_window, sf::Vector2f(sf::Mouse::getPosition(m_window)), m_events, _workers->isRendering() || _locked);
    }

    if (m_renderedImage) {
        m_renderedImage->render(m_window, sf::Vector2f(34, 50));

        if (_workers->isRendering()) {
            _workers->renderUpdate(*_core, _fastRendering);

            _workers->placeholderMutex.lock();
            updateRenderedImage(_workers->placeholderImage);
            _workers->placeholderMutex.unlock();
            _startLockTime = std::chrono::high_resolution_clock::now();
        } else {
            if (_locked) {
                auto now = std::chrono::high_resolution_clock::now();
                auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(now - _startLockTime).count();
                if (duration > 1000) {
                    _locked = false;
                    _workers->placeholderMutex.lock();
                    updateRenderedImage(_workers->placeholderImage);
                    _workers->placeholderMutex.unlock();
                }
            }
        }
    }

    m_events.clear();
    displayWindow();
}
