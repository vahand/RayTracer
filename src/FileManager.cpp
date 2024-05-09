/*
** EPITECH PROJECT, 2024
** 7
** File description:
** FileManager
*/

#include "../includes/FileManager.hpp"

RayTracer::FileManager::FileManager(Core &core) : _core(core)
{
}

RayTracer::FileManager::~FileManager()
{
}

void RayTracer::FileManager::addFileConfigPath(const std::string &path)
{
    _fileConfigPath.push_back(path);
}

void RayTracer::FileManager::loadFileConfig()
{
    for (auto &path : _fileConfigPath)
        Parser parser(_core, path);
}

void RayTracer::FileManager::reload()
{
    _core._shapes.clear();
    _core._lights.clear();
    loadFileConfig();
}

void RayTracer::FileManager::rmFileConfigPath(const std::string &path)
{
    for (auto it = _fileConfigPath.begin(); it != _fileConfigPath.end(); it++) {
        if (*it == path) {
            _fileConfigPath.erase(it);
            return;
        }
    }
}
