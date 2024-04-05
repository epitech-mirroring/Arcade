/*
** EPITECH PROJECT, 2024
** Pacman
** File description:
** No file there , just an epitech header example .
** You can even have multiple lines if you want !
*/

#include "Pinky.hpp"

Pinky::Pinky(): AGhost("assets/games/pacman/ghosts/pinky.png") {
}

void Pinky::updateTarget(const Pac &pac, const std::vector<AGhost *> &ghost) {
    static const GridCoordinate home = GridCoordinate(2, 0).toScreen();
    static const GridCoordinate cage = GridCoordinate(13, 17).toScreen();
    (void) ghost;

    if(this->_isDead || this->_isCaged){
        this->_target = cage;
    } else if(_strategy == SCATTER){
        this->_target = home;
    }
    else if(_strategy == CHASE){
        GridCoordinate grid = GridCoordinate(pac.getPosition(), GridCoordinate::SCREEN).toGrid();
        switch (pac.getDirection()) {
            case Direction::RIGHT:
                grid.setX(grid.getX() + 4);
                break;
            case Direction::DOWN:
                grid.setY(grid.getY() + 4);
                break;
            case Direction::LEFT:
                grid.setX(grid.getX() - 4);
                break;
            case Direction::UP:
                grid.setY(grid.getY() - 4);
                grid.setX(grid.getX() - 4);
                break;
            case NONE:
                break;
        }
        this->_target = grid.toScreen();
    }
}

void Pinky::recalculateDotLimit() {
    this->_dotLimit = 0;
}
