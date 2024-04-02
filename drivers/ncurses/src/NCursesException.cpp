/*
** EPITECH PROJECT, 2024
** Arcade
** File description:
** NCursesException
*/

#include "NCursesException.hpp"

NCursesException::NCursesException(std::string const &message)
{
    this->_message = message;
}

const char *NCursesException::what() const noexcept
{
    return this->_message.c_str();
}

int NCursesException::getCode() const
{
    return 905;
}
