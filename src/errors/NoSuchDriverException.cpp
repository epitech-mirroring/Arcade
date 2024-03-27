/*
** EPITECH PROJECT, 2024
** Arcade
** File description:
** No file there , just an epitech header example .
** You can even have multiple lines if you want !
*/

#include "core/errors/NoSuchDriverException.hpp"

NoSuchDriverException::NoSuchDriverException(std::string const &driverName)
{
    this->_message = "Driver not found: " + driverName;
}

const char *NoSuchDriverException::what() const noexcept
{
    return this->_message.c_str();
}

int NoSuchDriverException::getCode() const
{
    return 404;
}
