/*
** EPITECH PROJECT, 2024
** Arcade
** File description:
** SDL2Exception
*/

#pragma once
#include "shared/errors/IDriverError.hpp"
#include <memory>

class SDL2Exception : public IDriverError {
private:
    std::string _message;
    std::shared_ptr<IDriver> _driver;
public:
    SDL2Exception(std::string const &message, IDriver &driver);
    ~SDL2Exception() override = default;

    [[nodiscard]] const char *what() const noexcept override;
    [[nodiscard]] int getCode() const override;
    [[nodiscard]] const IDriver &getDriver() const override;
};
