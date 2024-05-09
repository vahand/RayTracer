/*
** EPITECH PROJECT, 2024
** RAYTRACER
** File description:
** AGraphicals
*/

#ifndef AGRAPHICALS_HPP_
    #define AGRAPHICALS_HPP_

    #include "IGraphicals.hpp"

namespace Graphics {
    class AGraphicals : public IGraphicals {
        public:
            AGraphicals() = default;
            ~AGraphicals() = default;

            virtual void setup(std::shared_ptr<RayTracer::Core> core, std::shared_ptr<Workers> workers) = 0;
            virtual void createWindow(int width, int height, const std::string& title) {};
            virtual void closeWindow() {};
            virtual void clearWindow() {};
            virtual void displayWindow() {};
            virtual void getEvents() {};
            virtual void renderAll() {};
            virtual void updateRenderedImage(std::unordered_map<int, std::unique_ptr<std::vector<RayTracer::Color>>> image) {};

            virtual bool isWindowOpen() { return false; };

        protected:
        private:
    };
}


#endif /* !AGRAPHICALS_HPP_ */
