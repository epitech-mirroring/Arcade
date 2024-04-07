/*
** EPITECH PROJECT, 2024
** Pacman
** File description:
** No file there , just an epitech header example .
** You can even have multiple lines if you want !
*/

#include "AGhost.hpp"
#include "common/utils/Picture.hpp"
#include "../PacmanGlobals.hpp"
#define SCALE_GHOST (SCALE * 8. / 28.)

AGhost::AGhost(const std::string &texturePath,
               const GridCoordinate &spawn) : APacManEntity(texturePath, 252, 28),
                                            _target(0, 0),
                                            _lastDirectionChangeCell(0, 0),
                                            _spawn(spawn) {
    _isDead = false;
    _hasToReverse = false;
    _isInAnimation = false;
    _dotLimit = 0;
    _isCaged = true;
    this->setSize(SCALE_GHOST);
    _animation = 0;
    _strategy = CHASE;
    this->_sprite->setDrawRect({0, 0, 28, 28});
    this->_baseSpritePath = texturePath;
    _isFrightened = false;
    _personalDotCount = 0;
    _animationStart = 0;
    this->_replacingChar = 'G';
}

const GridCoordinate AGhost::_cage = GridCoordinate(13, 17).toScreen();

const GridCoordinate &AGhost::getCagePosition() {
    return _cage;
}

bool AGhost::isDead() const
{
    return _isDead;
}

bool AGhost::hasToReverse() const
{
    return _hasToReverse;
}

void AGhost::updateStrategy()
{
    GhostStrategy old = _strategy;

    if (_isFrightened) {
        _strategy = SCATTER;
    } else {
        _strategy = game->getGlobalStrategy();
    }

    if (old != _strategy) {
        this->_hasToReverse = true;
    }
}

void AGhost::update(const APacManEntity &pac, const Wall (&map)[37][28], const std::vector<AGhost *> &ghosts)
{
    Picture base(this->_baseSpritePath, 252, 28);
    if (this->_isInAnimation) {
        this->_sprite->setPicture(base);
        this->_sprite->setDrawRect({252-28, 0, 28, 28});
        static GridCoordinate target = GridCoordinate(13, 15).toScreen();
        static GridCoordinate from = GridCoordinate(13, 17).toScreen();
        static const std::size_t animationLength = 1000;
        double progress = (double) (arcade->getTime() - _animationStart) / (double)animationLength;
        GridCoordinate pos = GridCoordinate(target.getX(), (int) (from.getY() + (target.getY() - from.getY()) * progress), GridCoordinate::SCREEN);
        this->setPosition(pos);

        if (arcade->getTime() - _animationStart > animationLength) {
            this->_isInAnimation = false;
        } else {
            return;
        }
    }
    this->updateStrategy();
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
        if (pos.getY() <= 16 * SCALE*8) {
            move = Move(pos, *this, Direction::DOWN);
            move.computeLanding();
            toGrid = GridCoordinate(move.getTo()).toGrid();
        } else if (grid.getY() >= 18) { // Go up
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
        if (fromGrid == _lastDirectionChangeCell && move.getDirection() != this->getDirection() && !_hasToReverse) {
            // Can't change direction twice in a row (or at least not in the same cell)
            Move tempMove = Move(pos, *this, this->_direction);
            tempMove.computeLanding();
            if (tempMove.isLegal(map)) {
                move = tempMove;
                toGrid = GridCoordinate(move.getTo()).toGrid();
            }
        }
        // Change square
        if (toGrid != fromGrid) {
            this->_animation ++;
            this->_animation %= 2;
        }
        if (move.getDirection() != this->getDirection()) {
            _lastDirectionChangeCell = toGrid;
            if (_hasToReverse && move.getDirection() == !this->getDirection())
                _hasToReverse = false;
        }
        this->_direction = move.getDirection();
        if (IS_GIZMOS(*arcade)) {
            GIZMOS(*arcade)->drawLine(this->getPosition(), move.getTo(), RGBAColor::RED);
        }
        this->setPosition(move.getTo());
    } else {
        move = Move(pos, *this, this->_direction);
        move.computeLanding();
    }

    static Picture scared("assets/games/pacman/ghosts/scared.png", 124, 28);
    static Picture dead("assets/games/pacman/ghosts/dead.png", 252, 28);
    std::size_t finalAnimation = _animation;

    if (this->_isDead) {
        static GridCoordinate cage = GridCoordinate(13, 17).toScreen();
        this->_sprite->setPicture(dead);
        // Check distance to cage if in cage then call spawn
        if (move.getTo().distance(cage) <= 8 * SCALE) {
            this->spawn(false);
        }
    } else if (_isFrightened) {
        this->_sprite->setPicture(scared);
        std::size_t blinkTimeInMs = 500; // Time in ms (time between two blinks)
        static std::size_t lastBlink = 0;
        static bool isWhite = false;
        if (frightenedMsLeft < 2000) {
            blinkTimeInMs = 200;
        }
        if (arcade->getTime() - lastBlink > blinkTimeInMs) {
            isWhite = !isWhite;
            lastBlink = arcade->getTime();
        }
        if (frightenedMsLeft >= 2000) {
            isWhite = false;
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
    if (_isFrightened && !this->_isDead) {
        offset = (finalAnimation)*28 + (finalAnimation)*4;
    }
    if (this->_isDead) {
        offset = (_direction)*20 + (_direction)*42;
    }
    this->_sprite->setDrawRect({offset, 0, 28, 28});
}

Move AGhost::getBestMove(const GridCoordinate& coord, Direction direction, const Wall (&map)[37][28])
{
    std::vector<Move> moves = this->getPossibleMoves(coord, direction, map);
    if (moves.empty())
        return {coord, *this, direction, direction};
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

void AGhost::spawn(bool skipAnimation)
{
    this->_isDead = false;
    this->_isCaged = false;
    this->_hasToReverse = false;
    this->_animation = 0;
    this->_sprite->setDrawRect({0, 0, 28, 28});
    this->_direction = Direction::LEFT;
    if (!skipAnimation) {
        this->_isCaged = false;
        this->_isInAnimation = true;
        this->_animationStart = arcade->getTime();
    } else {
        this->_isInAnimation = false;
        this->setPosition(GridCoordinate(13, 14).toScreen());
    }
}

bool AGhost::isFrightened() const
{
    return _isFrightened;
}

void AGhost::setFrightened(bool isFrightened)
{
    _isFrightened = isFrightened;
}

void AGhost::kill()
{
    this->_isDead = true;
    this->_isFrightened = false;
    this->_hasToReverse = false;
}

void AGhost::setCaged(bool isCaged)
{
    _isCaged = isCaged;
}

void AGhost::setPersonalDotCount(std::size_t count)
{
    _personalDotCount = count;
}

std::size_t AGhost::getPersonalDotCount() const
{
    return _personalDotCount;
}

void AGhost::setDead(bool isDead)
{
    _isDead = isDead;
}

const GridCoordinate &AGhost::getSpawnPosition() {
    return _spawn;
}

int AGhost::getDotLimit() const
{
    return _dotLimit;
}
