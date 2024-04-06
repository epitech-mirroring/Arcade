/*
** EPITECH PROJECT, 2024
** Pacman
** File description:
** No file there , just an epitech header example .
** You can even have multiple lines if you want !
*/

#pragma once
#include "common/displayable/entities/AEntity.hpp"
#include "../PacManEnums.hpp"

class Fruit: public AEntity {
protected:
    BonusType _type;
    bool _hasBeenEaten;
    std::size_t _apparitionTime;
    bool _hasSpawned;
public:
    explicit Fruit(BonusType type);

    [[nodiscard]] BonusType getType() const;
    [[nodiscard]] bool hasBeenEaten() const;
    void setEaten(bool eaten);
    [[nodiscard]] std::size_t getApparitionTime() const;
    void setApparitionTime(std::size_t apparitionTime);
    [[nodiscard]] bool shouldBeDisplayed() const;
    void setSpawned(bool spawned);
    [[nodiscard]] bool hasSpawned() const;
};
