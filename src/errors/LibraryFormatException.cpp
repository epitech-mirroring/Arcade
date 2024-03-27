/*
** EPITECH PROJECT, 2024
** Arcade
** File description:
** No file there , just an epitech header example .
** You can even have multiple lines if you want !
*/

#include "core/errors/LibraryFormatException.hpp"

LibraryFormatException::LibraryFormatException(std::string const &message)
{
    this->_message = message;
}

const char *LibraryFormatException::what() const noexcept
{
    return this->_message.c_str();
}

int LibraryFormatException::getCode() const
{
    return 500;
}
