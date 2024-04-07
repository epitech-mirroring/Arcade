/*
** EPITECH PROJECT, 2024
** Arcade
** File description:
** No file there , just an epitech header example .
** You can even have multiple lines if you want !
*/

#pragma once
#include "common/AGame.hpp"
#include <string>

class Menu : public AGame {
protected:
    std::string _tempUsername;
public:
    Menu();
    ~Menu() override = default;

    void typeUsername(const IEvent &event);
    void handleClicked(const IEvent &event);

    void run() override;
    void init(std::shared_ptr<IArcade> arcade) override;
    void start() override;
};
