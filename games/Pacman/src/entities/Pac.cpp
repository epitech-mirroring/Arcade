/*
** EPITECH PROJECT, 2024
** Pacman
** File description:
** No file there , just an epitech header example .
** You can even have multiple lines if you want !
*/

#include "Pac.hpp"
#include "common/utils/Coord2D.hpp"
#include "common/utils/RGBAColor.hpp"
#include "../utils/Move.hpp"

Pac::Pac(): APacManEntity("assets/games/pacman/pacman/pacman.png", 208, 26) {
    Coord2D spawn(COORD_TO_SCREEN(13), COORD_TO_SCREEN(26));
    this->_sprite->setDrawRect({0, 0, 26, 26});
    this->setPosition(spawn);
    this->setSize(SCALE_PACKMAN);
    this->_direction = Direction::LEFT;
    this->_newDirection = Direction::LEFT;
    this->_eaten = false;
}

void Pac::handleEvent(const IEvent &event) {
    if (event.getType() == IEvent::EventType::_KEY_PRESS) {
        auto key = event.getKey();
        if (key == _KEY_UP || key == _KEY_Z) {
            this->_newDirection = Direction::UP;
        } else if (key == _KEY_DOWN || key == _KEY_S) {
            this->_newDirection = Direction::DOWN;
        } else if (key == _KEY_LEFT || key == _KEY_Q) {
            this->_newDirection = Direction::LEFT;
        } else if (key == _KEY_RIGHT || key == _KEY_D) {
            this->_newDirection = Direction::RIGHT;
        }
    }
}

bool isThereWall(const Wall (&map)[37][28], const Coord2D& pos) {
    return map[SCREEN_TO_COORD(pos.getY())][SCREEN_TO_COORD(pos.getX())].getType() != Wall::WallType::EMPTY;
}

void Pac::update(IArcade &arcade, const Wall (&map)[37][28]) {
    Move move(this->getPosition(), (APacManEntity &) *this, this->_newDirection);
    Coord2D fromGrid = Coord2D(SCREEN_TO_COORD(this->getPosition().getX()), SCREEN_TO_COORD(this->getPosition().getY()));
    Coord2D toGrid;

    move.computeLanding();
    toGrid = Coord2D(SCREEN_TO_COORD(move.getTo().getX()), SCREEN_TO_COORD(move.getTo().getY()));
    if(move.isLegal(map)){
        // Change square
        if (toGrid != fromGrid) {
            this->_animation ++;
            this->_animation %= 2;
        }
        this->_direction = this->_newDirection;
        this->setPosition(move.getTo());
    } else {
        move = Move(this->getPosition(), (APacManEntity &) *this, this->_direction);
        move.computeLanding();
        toGrid = Coord2D(SCREEN_TO_COORD(move.getTo().getX()), SCREEN_TO_COORD(move.getTo().getY()));
        if(move.isLegal(map)){
            // Change square
            if (toGrid != fromGrid) {
                this->_animation ++;
                this->_animation %= 2;
            }
            this->setPosition(move.getTo());
            this->_newDirection = this->_direction;
        }
    }

    this->_sprite->setDrawRect({26 * (this->_animation + this->_direction * 2), 0, 26, 26});
}

bool Pac::hasEaten() const {
    return this->_eaten;
}

void Pac::setEaten(bool eaten) {
    this->_eaten = eaten;
}
