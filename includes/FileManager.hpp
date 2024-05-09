/*
** EPITECH PROJECT, 2024
** raytracer
** File description:
** FileManager
*/

#ifndef FILEMANAGER_HPP_
#define FILEMANAGER_HPP_

#include "Parser.hpp"

namespace RayTracer {
    class FileManager {
        public:
            FileManager(Core &core);
            ~FileManager();

            void addFileConfigPath(const std::string &path);
            void loadFileConfig();
            void reload();
            void rmFileConfigPath(const std::string &path);
            // void saveFileConfig(const std::string &path);

        protected:
        private:
            Core &_core;
            std::vector<std::string> _fileConfigPath;

    };
}

#endif /* !FILEMANAGER_HPP_ */
