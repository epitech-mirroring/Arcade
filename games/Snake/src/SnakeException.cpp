/*
** EPITECH PROJECT, 2024
** Arcade
** File description:
** SnakeException
*/

#include "SnakeException.hpp"

SnakeException::SnakeException(std::string const &message)
{
    this->_message = message;
}

const char *SnakeException::what() const noexcept
{
    return this->_message.c_str();
}

int SnakeException::getCode() const
{
    return 666;
}
