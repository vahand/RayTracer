/*
** EPITECH PROJECT, 2024
** RAYTRACER
** File description:
** IGraphicals
*/

#ifndef IGRAPHICALS_HPP_
    #define IGRAPHICALS_HPP_

    #include <string>
    #include "Workers.hpp"
    #include "Core.hpp"

class IGraphicals {
    public:
        IGraphicals() = default;
        ~IGraphicals() = default;

        virtual void setup(std::shared_ptr<RayTracer::Core> core, std::shared_ptr<Workers> workers) = 0;
        virtual void createWindow(int width, int height, const std::string& title) = 0;
        virtual void closeWindow() = 0;
        virtual bool isWindowOpen() = 0;
        virtual void clearWindow() = 0;
        virtual void displayWindow() = 0;
        virtual void getEvents() = 0;
        virtual void renderAll() = 0;

        virtual void updateRenderedImage(std::unordered_map<int, std::unique_ptr<std::vector<RayTracer::Color>>> image) = 0;

    protected:
    private:
};

#endif /* !IGRAPHICALS_HPP_ */
