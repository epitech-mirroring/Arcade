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
#include "APacManEntity.hpp"
#include "../utils/GridCoordinate.hpp"
#include "../utils/Move.hpp"

class AGhost: public APacManEntity {
private:
    std::string _baseSpritePath;
protected:
    bool _isDead;
    bool _hasToReverse;
    explicit AGhost(const std::string &texturePath,
                    const GridCoordinate &spawn);
    GridCoordinate _target;
    int _dotLimit;
    bool _isCaged;
    std::size_t _animation;
    GhostStrategy _strategy;
    bool _isFrightened;
    GridCoordinate _lastDirectionChangeCell;
    static const GridCoordinate _cage;
    const GridCoordinate _spawn;
    std::size_t _personalDotCount;
public:
    ~AGhost() override = default;

    [[nodiscard]] bool isDead() const;
    [[nodiscard]] bool hasToReverse() const;
    virtual void updateTarget(const APacManEntity &pac, const std::vector<AGhost *> &ghost) = 0;
    virtual void recalculateDotLimit() = 0;
    void updateStrategy();
    void update(const APacManEntity &pac, const Wall (&map)[37][28], const std::vector<AGhost *> &ghosts);
    [[nodiscard]] bool isCaged() const;
    [[nodiscard]] GhostStrategy getStrategy() const;
    void setStrategy(GhostStrategy strategy);
    void spawn(bool skipAnimation);
    [[nodiscard]] bool isFrightened() const;
    void setFrightened(bool isFrightened);
    void kill() override;
    [[nodiscard]] static const GridCoordinate &getCagePosition() ;
    [[nodiscard]] const GridCoordinate &getSpawnPosition() ;
    void setCaged(bool isCaged);
    void setPersonalDotCount(std::size_t count);
    [[nodiscard]] std::size_t getPersonalDotCount() const;
    void setDead(bool isDead);

    [[nodiscard]] Move getBestMove(const GridCoordinate& coord, Direction direction, const Wall (&map)[37][28]);
    [[nodiscard]] std::vector<Move> getPossibleMoves(const GridCoordinate& coord, Direction direction, const Wall (&map)[37][28]);
};
