/*
** EPITECH PROJECT, 2024
** Arcade
** File description:
** No file there , just an epitech header example .
** You can even have multiple lines if you want !
*/

#pragma once
#include "common/AGame.hpp"

class CookieClicker: public AGame {
public:
    CookieClicker();
    ~CookieClicker() override = default;

    void start() override;
    void run() override;
};
