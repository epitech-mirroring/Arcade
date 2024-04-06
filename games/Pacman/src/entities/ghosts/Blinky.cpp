/*
** EPITECH PROJECT, 2024
** Pacman
** File description:
** No file there , just an epitech header example .
** You can even have multiple lines if you want !
*/

#include "Blinky.hpp"
#include "../../PacmanGlobals.hpp"

Blinky::Blinky(): AGhost("assets/games/pacman/ghosts/blinky.png",
                         GridCoordinate(13, 14).toScreen()) {
    this->setPosition(GridCoordinate(13, 17).toScreen());
    spawn(true);
}

void Blinky::updateTarget(const APacManEntity &pac, const std::vector<AGhost *> &ghost) {
    static const GridCoordinate home = GridCoordinate(MAP_WIDTH-3, 0).toScreen();
    (void) ghost;

    if (IS_GIZMOS(*arcade)) {
        GIZMOS(*arcade)->drawRect(home, home + Coord2D(SCALE * 8, SCALE * 8), false, RGBAColor::RED);
    }

    if(this->_isDead || this->_isCaged){
        this->_target = _cage;
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
