/*
** EPITECH PROJECT, 2024
** Arcade
** File description:
** SnakeException
*/

#pragma once
#include "shared/errors/IGameError.hpp"

class SnakeException : public IGameError {
private:
    std::string _message;
public:
    SnakeException(std::string const &message);
    ~SnakeException() override = default;

    [[nodiscard]] const char *what() const noexcept override;
    [[nodiscard]] int getCode() const override;
};
