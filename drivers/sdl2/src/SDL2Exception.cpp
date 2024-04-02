/*
** EPITECH PROJECT, 2024
** Arcade
** File description:
** SDL2Exception
*/

#include "SDL2Exception.hpp"

SDL2Exception::SDL2Exception(std::string const &message, IDriver &driver)
{
    this->_message = message;
    this->_driver = std::shared_ptr<IDriver>(&driver);
}

const char *SDL2Exception::what() const noexcept
{
    return this->_message.c_str();
}

int SDL2Exception::getCode() const
{
    return 906;
}

const IDriver &SDL2Exception::getDriver() const
{
    return *this->_driver;
}
