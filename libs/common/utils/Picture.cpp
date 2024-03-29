/*
** EPITECH PROJECT, 2024
** Arcade
** File description:
** No file there , just an epitech header example .
** You can even have multiple lines if you want !
*/

#include "common/utils/Picture.hpp"

Picture::Picture(const std::string &path)
{
    this->_path = path;
}

Picture::Picture(const IPicture &picture)
{
    this->_path = picture.getPath();
}

Picture::Picture()
{
    this->_path = "";
}

Picture::~Picture() = default;

const std::string &Picture::getPath() const
{
    return this->_path;
}

void Picture::setPath(const std::string &path)
{
    this->_path = path;
}

// Operators

bool Picture::operator==(const Picture &picture) const
{
    return this->_path == picture.getPath();
}

bool Picture::operator!=(const Picture &picture) const
{
    return !(*this == picture);
}

Picture &Picture::operator=(const Picture &picture)
{
    this->_path = picture.getPath();
    return *this;
}

std::ostream &operator<<(std::ostream &os, const Picture &picture)
{
    os << picture.getPath();
    return os;
}
