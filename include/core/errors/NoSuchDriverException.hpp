/*
** EPITECH PROJECT, 2024
** Arcade
** File description:
** No file there , just an epitech header example .
** You can even have multiple lines if you want !
*/

#pragma once
#include "shared/errors/IError.hpp"

class NoSuchDriverException : public IError {
private:
    std::string _message;
public:
    NoSuchDriverException(std::string const &driverName);
    ~NoSuchDriverException() override = default;

    const char *what() const noexcept override;
    int getCode() const override;
};
