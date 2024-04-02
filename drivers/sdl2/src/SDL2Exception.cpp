/*
** EPITECH PROJECT, 2024
** Arcade
** File description:
** SDL2Exception
*/

#include "SDL2Exception.hpp"

SDL2Exception::SDL2Exception(std::string const &message)
{
    this->_message = message;
}

const char *SDL2Exception::what() const noexcept
{
    return this->_message.c_str();
}

int SDL2Exception::getCode() const
{
    return 906;
}
