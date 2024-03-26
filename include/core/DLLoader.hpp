/*
** EPITECH PROJECT, 2024
** Arcade
** File description:
** DLLoader
*/

#pragma once

#include <dlfcn.h>
#include <iostream>

template <typename T>
class DLLoader {
public:
    DLLoader(std::string const &libPath) {
        this->_handle = dlopen(libPath.c_str(), RTLD_LAZY);
        if (!this->_handle) {
            std::cerr << "Cannot open library: " << dlerror() << '\n';
            exit(84); // Replace with exception
        }
        this->_entryPoint = reinterpret_cast<T *(*)()>(dlsym(this->_handle, "entryPoint"));
        if (!this->_entryPoint) {
            std::cerr << "Cannot load symbol entryPoint: " << dlerror() << '\n';
            exit(84); // Replace with exception
        }
    }

    ~DLLoader() {
        dlclose(this->_handle);
    }

    T *getInstance() {
        return this->_entryPoint();
    }

private:
    void *_handle;
    T *(*_entryPoint)();
};
