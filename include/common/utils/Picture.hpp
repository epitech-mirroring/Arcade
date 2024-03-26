/*
** EPITECH PROJECT, 2024
** Arcade
** File description:
** No file there , just an epitech header example .
** You can even have multiple lines if you want !
*/

#pragma once
#include "../../shared/utils/IPicture.hpp"
#include <ostream>

class Picture: public IPicture {
protected:
    std::string _path;
public:
    Picture(const std::string &path);
    Picture(const Picture &picture);
    Picture();
    ~Picture();
    const std::string &getPath() const override;
    void setPath(const std::string &path) override;
    bool operator==(const Picture &picture) const;
    bool operator!=(const Picture &picture) const;
    Picture &operator=(const Picture &picture);
    friend std::ostream &operator<<(std::ostream &os, const Picture &picture);
};
