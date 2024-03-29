/*
** EPITECH PROJECT, 2024
** Arcade
** File description:
** No file there , just an epitech header example .
** You can even have multiple lines if you want !
*/

#pragma once
#include "shared/errors/IError.hpp"

class LibraryFormatException : public IError {
private:
    std::string _message;
public:
    explicit LibraryFormatException(std::string const &message);
    ~LibraryFormatException() override = default;

    [[nodiscard]] const char *what() const noexcept override;
    [[nodiscard]] int getCode() const override;
};
