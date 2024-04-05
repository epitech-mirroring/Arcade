/*
** EPITECH PROJECT, 2024
** Pacman
** File description:
** No file there , just an epitech header example .
** You can even have multiple lines if you want !
*/

#pragma once

#include "common/displayable/entities/AEntity.hpp"

#define LIVES_SCALE (SCALE * 8. / 16.)

class LiveCounter: public AEntity {
protected:
    std::size_t _lives;
public:
    LiveCounter();
    ~LiveCounter() override = default;

    void setLives(std::size_t lives);
};
