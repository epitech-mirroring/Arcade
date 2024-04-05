/*
** EPITECH PROJECT, 2024
** Pacman
** File description:
** No file there , just an epitech header example .
** You can even have multiple lines if you want !
*/

#include "AGhost.hpp"
#include "common/utils/RGBAColor.hpp"
#include "common/utils/Picture.hpp"

AGhost::AGhost(const std::string &texturePath): APacManEntity(texturePath, 252, 28),
                                                _target(0, 0)
{
    _isDead = false;
    _hasToReverse = false;
    _dotLimit = 0;
    _isCaged = true;
    this->setSize(SCALE_GHOST);
    _animation = 0;
    _strategy = CHASE;
    this->_sprite->setDrawRect({0, 0, 28, 28});
    this->_baseSpritePath = texturePath;
}

bool AGhost::isDead() const
{
    return _isDead;
}

bool AGhost::hasToReverse() const
{
    return _hasToReverse;
}

void AGhost::update(const Pac &pac, const Wall (&map)[37][28], const std::vector<AGhost *> &ghosts)
{
    this->updateTarget(pac, ghosts);
    this->recalculateDotLimit();
    if (IS_GIZMOS(*arcade)) {
        GIZMOS(*arcade)->drawLine(this->getPosition(), _target, RGBAColor::GREEN);
    }

    GridCoordinate pos = GridCoordinate(this->getPosition(), GridCoordinate::SCREEN);
    Move move = this->getBestMove(pos, this->_direction, map);
    GridCoordinate fromGrid = GridCoordinate(pos).toGrid();
    GridCoordinate toGrid = GridCoordinate(move.getTo()).toGrid();

    if (isCaged()) {
        GridCoordinate grid = GridCoordinate(this->getPosition(), GridCoordinate::SCREEN).toGrid();
        if (pos.getY() >= 16 * SCALE*8) {
            move = Move(pos, *this, Direction::DOWN);
            move.computeLanding();
            toGrid = GridCoordinate(move.getTo()).toGrid();
        } else if (grid.getY() == 18) { // Go up
            move = Move(pos, *this, Direction::UP);
            move.computeLanding();
            toGrid = GridCoordinate(move.getTo()).toGrid();
        } else {
            move = Move(pos, *this, this->_direction);
            move.computeLanding();
            toGrid = GridCoordinate(move.getTo()).toGrid();
        }
        if (toGrid != fromGrid) {
            this->_animation ++;
            this->_animation %= 2;
        }
        this->_direction = move.getDirection();
        this->setPosition(move.getTo());
    } else if (move.isLegal(map)) {
        // Change square
        if (toGrid != fromGrid) {
            this->_animation ++;
            this->_animation %= 2;
        }
        this->_direction = move.getDirection();
        if (IS_GIZMOS(*arcade)) {
            GIZMOS(*arcade)->drawLine(this->getPosition(), move.getTo(), RGBAColor::RED);
        }
        this->setPosition(move.getTo());
    } else {
        move = Move(pos, *this, this->_direction);
        move.computeLanding();
        toGrid = GridCoordinate(move.getTo()).toGrid();
    }

    static Picture scared("assets/games/pacman/ghosts/scared.png", 124, 28);
    static Picture dead("assets/games/pacman/ghosts/dead.png", 252, 28);
    Picture base(this->_baseSpritePath, 252, 28);
    std::size_t finalAnimation = _animation;

    if (this->_isDead) {
        this->_sprite->setPicture(dead);
    } else if (isFrightened) {
        this->_sprite->setPicture(scared);
        std::size_t blinkTimeInMs = 500; // Time in ms (time between two blinks)
        static std::size_t lastBlink = 0;
        static bool isWhite = false;
        if (frightenedMsLeft < 2000) {
            blinkTimeInMs = 250;
        }
        if (arcade->getTime() - lastBlink > blinkTimeInMs) {
            isWhite = !isWhite;
            lastBlink = arcade->getTime();
        }
        if (this->_animation == 0 && isWhite) {
            finalAnimation = 2;
        } else if (this->_animation == 1 && isWhite) {
            finalAnimation = 3;
        }
    } else {
        this->_sprite->setPicture(base);
    }

    std::size_t offset = (finalAnimation+(_direction*2))*28 + (finalAnimation+(_direction*2))*4;
    if (isFrightened && !this->_isDead) {
        offset = (finalAnimation)*28 + (finalAnimation)*4;
    }
    this->_sprite->setDrawRect({offset, 0, 28, 28});
}

Move AGhost::getBestMove(const GridCoordinate& coord, Direction direction, const Wall (&map)[37][28])
{
    std::vector<Move> moves = this->getPossibleMoves(coord, direction, map);
    Move bestMove = moves[0];
    for (auto &move : moves) {
        if (move.getTo().distance(_target) < bestMove.getTo().distance(_target))
            bestMove = move;
    }
    return bestMove;
}

std::vector<Move> AGhost::getPossibleMoves(const GridCoordinate& coord, Direction direction, const Wall (&map)[37][28]) {
    std::vector<Move> moves;
    Move right(coord, *this, Direction::RIGHT, direction);
    right.computeLanding();
    Move left(coord, *this, Direction::LEFT, direction);
    left.computeLanding();
    Move up(coord, *this, Direction::UP, direction);
    up.computeLanding();
    Move down(coord, *this, Direction::DOWN, direction);
    down.computeLanding();

    if (right.isLegal(map))
        moves.push_back(right);
    if (left.isLegal(map))
        moves.push_back(left);
    if (up.isLegal(map))
        moves.push_back(up);
    if (down.isLegal(map))
        moves.push_back(down);
    return moves;
}

bool AGhost::isCaged() const
{
    return _isCaged;
}

GhostStrategy AGhost::getStrategy() const
{
    return _strategy;
}

void AGhost::setStrategy(GhostStrategy strategy)
{
    _strategy = strategy;
}
