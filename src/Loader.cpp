/*
** EPITECH PROJECT, 2024
** arcade
** File description:
** Loader
*/

#include "../includes/Loader.hpp"

Loader::Loader()
{
}

Loader::Loader(std::string filename) : _handle(dlopen(filename.c_str(), RTLD_LAZY), [](void *handle) {
    if (handle != nullptr)
        dlclose(handle);
})
{
    if (this->_handle == nullptr) {
        std::cerr << "Failed to load library: " << dlerror() << std::endl;
    }
    std::cerr << "Loader for librairy " << filename << " created successfully" << std::endl;
}
