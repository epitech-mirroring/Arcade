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
#include "../PacmanGlobals.hpp"
#include "APacManEntity.hpp"
#include "../utils/GridCoordinate.hpp"
#include "Pac.hpp"
#include "../utils/Move.hpp"

#define SCALE_GHOST (SCALE * 8. / 28.)

class AGhost: public APacManEntity {
private:
    std::string _baseSpritePath;
protected:
    bool _isDead;
    bool _hasToReverse;
    explicit AGhost(const std::string &texturePath);
    GridCoordinate _target;
    int _dotLimit;
    bool _isCaged;
    std::size_t _animation;
    GhostStrategy _strategy;
public:
    ~AGhost() override = default;

    [[nodiscard]] bool isDead() const;
    [[nodiscard]] bool hasToReverse() const;
    virtual void updateTarget(const Pac &pac, const std::vector<AGhost *> &ghost) = 0;
    virtual void recalculateDotLimit() = 0;
    void update(const Pac &pac, const Wall (&map)[37][28], const std::vector<AGhost *> &ghosts);
    [[nodiscard]] bool isCaged() const;
    [[nodiscard]] GhostStrategy getStrategy() const;
    void setStrategy(GhostStrategy strategy);

    [[nodiscard]] Move getBestMove(const GridCoordinate& coord, Direction direction, const Wall (&map)[37][28]);
    [[nodiscard]] std::vector<Move> getPossibleMoves(const GridCoordinate& coord, Direction direction, const Wall (&map)[37][28]);
};
