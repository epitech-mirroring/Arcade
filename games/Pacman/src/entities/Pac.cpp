/*
** EPITECH PROJECT, 2024
** Pacman
** File description:
** No file there , just an epitech header example .
** You can even have multiple lines if you want !
*/

#include "Pac.hpp"
#include "../utils/Move.hpp"
#include "common/utils/RGBAColor.hpp"

Pac::Pac(): APacManEntity("assets/games/pacman/pacman/pacman.png", 208, 26) {
    GridCoordinate spawn = GridCoordinate(13, 26).toScreen();
    this->_sprite->setDrawRect({0, 0, 26, 26});
    this->setPosition(spawn);
    this->setSize(SCALE_PACKMAN);
    this->_direction = Direction::LEFT;
    this->_newDirection = Direction::LEFT;
    this->_eaten = false;
    this->_animation = 0;
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

bool isThereWall(const Wall (&map)[37][28], const GridCoordinate& pos) {
    GridCoordinate fromGrid = GridCoordinate(pos).toScreen();
    return map[pos.getY()][pos.getX()].getType() != Wall::WallType::EMPTY;
}

void Pac::update(std::vector<PacDot *> &dots, const Wall (&map)[37][28]) {
    GridCoordinate pos = GridCoordinate(this->getPosition(), GridCoordinate::SCREEN);
    Move move(pos, (APacManEntity &) *this, this->_newDirection);
    GridCoordinate fromGrid = GridCoordinate(pos).toGrid();

    move.computeLanding();
    GridCoordinate toGrid = GridCoordinate(move.getTo()).toGrid();
    if(move.isLegal(map)){
        // Change square
        if (toGrid != fromGrid) {
            this->_animation ++;
            this->_animation %= 2;
        }
        this->_direction = this->_newDirection;
        if (IS_GIZMOS(*arcade)) {
            GIZMOS(*arcade)->drawLine(this->getPosition(), move.getTo(), RGBAColor::RED);
        }
        this->setPosition(move.getTo());
    } else {
        move = Move(pos, (APacManEntity &) *this, this->_direction);
        move.computeLanding();
        toGrid = GridCoordinate(move.getTo()).toGrid();
        if(move.isLegal(map)){
            // Change square
            if (toGrid != fromGrid) {
                this->_animation ++;
                this->_animation %= 2;
            }
            if (IS_GIZMOS(*arcade)) {
                GIZMOS(*arcade)->drawLine(this->getPosition(), move.getTo(), RGBAColor::RED);
            }
            this->setPosition(move.getTo());
            this->_newDirection = this->_direction;
        }
    }

    for (std::size_t i = 0; i < dots.size(); i++) {
        PacDot *dot = dots[i];
        GridCoordinate dotGrid = GridCoordinate(dot->getPosition(), GridCoordinate::SCREEN).toGrid();
        GridCoordinate pacGrid = GridCoordinate(this->getPosition(), GridCoordinate::SCREEN).toGrid();
        if (dotGrid == pacGrid) {
            this->_eaten = true;
            if (dot->isEnergizer()) {
                isFrightened = true;
            }
            dots.erase(dots.begin() + i);
            delete dot;
            break;
        }
    }

    if (IS_GIZMOS(*arcade)) {
        GridCoordinate center = GridCoordinate(this->getPosition(), GridCoordinate::SCREEN);
        center.setX((int) ((float) center.getX() + 13.f * SCALE_PACKMAN));
        center.setY((int) ((float) center.getY() + 13.f * SCALE_PACKMAN));
        GridCoordinate gridCenter = GridCoordinate(this->getPosition(), GridCoordinate::SCREEN).round();
        gridCenter.setX((int) ((float) gridCenter.getX() + 4.f * SCALE));
        gridCenter.setY((int) ((float) gridCenter.getY() + 4.f * SCALE));
        GIZMOS(*arcade)->drawLine(center, gridCenter, RGBAColor::RED);
    }

    this->_sprite->setDrawRect({26 * (this->_animation + this->_direction * 2), 0, 26, 26});
}

bool Pac::hasEaten() const {
    return this->_eaten;
}

void Pac::setEaten(bool eaten) {
    this->_eaten = eaten;
}
