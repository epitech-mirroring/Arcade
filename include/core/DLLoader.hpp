/*
** EPITECH PROJECT, 2024
** Arcade
** File description:
** DLLoader
*/

#pragma once
#include <dlfcn.h>
#include <iostream>
#include <memory>
#include "errors/LibraryFormatException.hpp"
#include <string>

template <typename T>
class DLLoader {
public:
    const std::string &(*getLibName)();

    DLLoader(std::string const &libPath, std::string const &entryPointName): getLibName(nullptr), _handle(nullptr), _entryPoint(nullptr) {
        this->_handle = dlopen(libPath.c_str(), RTLD_LAZY);
        if (!this->_handle) {
            throw LibraryFormatException("Cannot open library: " + libPath);
        }
        this->_entryPoint = reinterpret_cast<std::unique_ptr<T> (*)()>(dlsym(this->_handle, entryPointName.c_str()));
        if (!this->_entryPoint) {
            throw LibraryFormatException("Cannot find entry point: " + entryPointName);
        }
        this->getLibName = reinterpret_cast<const std::string &(*)()>(dlsym(this->_handle, "get_name"));
    }

    ~DLLoader() {
        dlclose(this->_handle);
    }

    std::unique_ptr<T> getInstance() {
        return this->_entryPoint();
    }

private:
    void *_handle;
    std::unique_ptr<T> (*_entryPoint)();
};
