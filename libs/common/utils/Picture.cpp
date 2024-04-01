/*
** EPITECH PROJECT, 2024
** Arcade
** File description:
** No file there , just an epitech header example .
** You can even have multiple lines if you want !
*/

#include "common/utils/Picture.hpp"

Picture::Picture(const std::string &path, std::size_t width, std::size_t height)
{
    this->_path = path;
    this->_width = width;
    this->_height = height;
}

Picture::Picture(const IPicture &picture)
{
    this->_path = picture.getPath();
    this->_width = picture.getWidth();
    this->_height = picture.getHeight();
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

std::size_t Picture::getWidth() const
{
    return this->_width;
}

std::size_t Picture::getHeight() const
{
    return this->_height;
}
