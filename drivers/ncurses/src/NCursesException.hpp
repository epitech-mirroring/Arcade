/*
** EPITECH PROJECT, 2024
** Arcade
** File description:
** NCursesException
*/

#pragma once
#include "shared/errors/IDriverError.hpp"
#include <memory>

class NCursesException : public IDriverError {
private:
    std::string _message;
public:
    NCursesException(std::string const &message);
    ~NCursesException() override = default;

    [[nodiscard]] const char *what() const noexcept override;
    [[nodiscard]] int getCode() const override;
};
