/*
** EPITECH PROJECT, 2024
** raytracer
** File description:
** FileManager
*/

#ifndef FILEMANAGER_HPP_
#define FILEMANAGER_HPP_

#include "Parser.hpp"
#include <time.h>
#include <sys/stat.h>

namespace RayTracer {
    class FileManager {
        public:
            class File {
                public:
                    File(const std::string &path);
                    ~File() {};

                    time_t getLastModif();
                    bool checkLastModif();

                    std::string _path;
                    time_t _lastModif;
            };
            FileManager(Core &core);
            ~FileManager();

            void addFileConfigPath(const std::string &path);
            void loadFileConfig();
            void reload();
            void rmFileConfigPath(const std::string &path);
            bool checkLastModifFile();
            // void saveFileConfig(const std::string &path);
            void setCamera(RayTracer::Parser::config_camere_s camera);
            bool checkForSceneEdition();

        protected:
        private:
            Core &_core;
            std::vector<File> _files;

    };
}

#endif /* !FILEMANAGER_HPP_ */
