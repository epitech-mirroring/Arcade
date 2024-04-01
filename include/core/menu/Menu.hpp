/*
** EPITECH PROJECT, 2024
** Arcade
** File description:
** No file there , just an epitech header example .
** You can even have multiple lines if you want !
*/

#pragma once
#include "common/AGame.hpp"

class Menu : public AGame {
public:
    Menu();
    ~Menu() override = default;

    void typeUsername(const IEvent &event) const;

    void run() override;
    void start() override;
};
