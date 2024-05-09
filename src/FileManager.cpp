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
    File file(path);
    _files.push_back(file);
}

void RayTracer::FileManager::loadFileConfig()
{
    if (_files.empty())
        return;
    Parser parser(_core, _files[0]._path);
    setCamera(parser.camera_settings);
    for (int i = 1; i < _files.size(); i++)
        Parser parser(_core, _files[i]._path);
}

void RayTracer::FileManager::reload()
{
    _core._shapes.clear();
    _core._lights.clear();
    loadFileConfig();
}

void RayTracer::FileManager::rmFileConfigPath(const std::string &path)
{
    for (int i = 0; i < _files.size(); i++)
        if (_files[i]._path == path) {
            _files.erase(_files.begin() + i);
            return;
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

bool RayTracer::FileManager::checkForSceneEdition()
{
    if (checkLastModifFile()) {
        reload();
        return true;
    }
    return false;
}

bool RayTracer::FileManager::checkLastModifFile()
{
    bool reload = false;

    for (int i = 0; i < _files.size(); i++)
        if (_files[i].checkLastModif())
            reload = true;
    return reload;
}

RayTracer::FileManager::File::File(const std::string &path) : _path(path)
{
    _lastModif = getLastModif();
}

time_t RayTracer::FileManager::File::getLastModif()
{
    struct stat attrib;
    stat(_path.c_str(), &attrib);
    _lastModif = attrib.st_mtime;
}

bool RayTracer::FileManager::File::checkLastModif()
{
    time_t lastModif = getLastModif();
    if (lastModif != _lastModif) {
        _lastModif = lastModif;
        return true;
    }
    return false;
}