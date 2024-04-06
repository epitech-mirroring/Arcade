/*
** EPITECH PROJECT, 2024
** Pacman
** File description:
** No file there , just an epitech header example .
** You can even have multiple lines if you want !
*/

#pragma once
#include "shared/events/IEvent.hpp"
#include "shared/ICanDrawGizmos.hpp"
#include "shared/IArcade.hpp"
#include "Wall.hpp"
#include "APacManEntity.hpp"
#include "PacDot.hpp"
#include "AGhost.hpp"
#include "Bonus.hpp"
#include "../PacManEnums.hpp"
#include <vector>

class Pac : public APacManEntity {
protected:
    bool _eaten;
    std::size_t _animation;
    std::vector<Bonus *> _bonuses;
    std::size_t _lastKill;
    std::size_t _killStreak;
public:
    Pac();
    ~Pac() override;
    Direction _newDirection;

    void handleEvent(const IEvent &event);
    void update(std::vector<PacDot *> &dots, const Wall (&map)[37][28], const std::vector<AGhost *> &ghosts);
    [[nodiscard]] bool hasEaten() const;
    void setEaten(bool eaten);
    void kill() override;
    [[nodiscard]] const std::vector<Bonus *> &getBonuses() const;
};
