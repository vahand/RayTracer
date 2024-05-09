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
    if (_fileConfigPath.empty())
        return;
    Parser parser(_core, _fileConfigPath[0]);
    setCamera(parser.camera_settings);
    for (int i = 1; i < _fileConfigPath.size(); i++)
        Parser parser(_core, _fileConfigPath[i]);
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

void RayTracer::FileManager::setCamera(RayTracer::Parser::config_camere_s camera)
{
    _core._camera._position = camera.position;
    _core._camera._focusPoint = camera.focusPoint;
    _core._camera._fovInDegrees = camera.fov;
    _core._camera._samples = camera.samples;
    _core.sceneBackground = camera.sceneBackGround;
    _core._maxDepth = camera.maxDepth;
    _core._camera.initialize();
}
