/*
** EPITECH PROJECT, 2024
** Pacman
** File description:
** No file there , just an epitech header example .
** You can even have multiple lines if you want !
*/

#include "Blinky.hpp"

Blinky::Blinky(): AGhost("assets/games/pacman/ghosts/blinky.png") {

}

void Blinky::updateTarget(const Pac &pac, const std::vector<AGhost *> &ghost) {
    static const GridCoordinate home = GridCoordinate(MAP_WIDTH-3, 0).toScreen();
    static const GridCoordinate cage = GridCoordinate(13, 17).toScreen();
    (void) ghost;

    if(this->_isDead || this->_isCaged){
        this->_target = cage;
    } else if(_strategy == SCATTER){
        this->_target = home;
    }
    else if(_strategy == CHASE){
        GridCoordinate grid = GridCoordinate(pac.getPosition(), GridCoordinate::SCREEN).toGrid();
        this->_target = grid.toScreen();
    }
}

void Blinky::recalculateDotLimit() {
    this->_dotLimit = 0;
}
