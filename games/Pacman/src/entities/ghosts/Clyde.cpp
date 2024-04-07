/*
** EPITECH PROJECT, 2024
** Pacman
** File description:
** No file there , just an epitech header example .
** You can even have multiple lines if you want !
*/

#include "Clyde.hpp"
#include "common/utils/RGBAColor.hpp"
#include "../../PacmanGlobals.hpp"

Clyde::Clyde(): AGhost("assets/games/pacman/ghosts/clyde.png",
                       GridCoordinate(15, 17).toScreen()) {
    this->setPosition(GridCoordinate(15, 17).toScreen());
    this->setColor(RGBAColor::YELLOW);
}

void Clyde::updateTarget(const APacManEntity &pac, const std::vector<AGhost *> &ghost) {
    static const GridCoordinate home = GridCoordinate(0, MAP_HEIGHT-3).toScreen();
    (void) ghost;

    if (IS_GIZMOS(*arcade)) {
        GIZMOS(*arcade)->drawRect(home, home + Coord2D(SCALE * 8, SCALE * 8), false, RGBAColor::YELLOW);
    }

    if(this->_isDead || this->_isCaged){
        this->_target = _cage;
    } else if(_strategy == SCATTER){
        this->_target = home;
    }
    else if(_strategy == CHASE){
        GridCoordinate grid = GridCoordinate(pac.getPosition(), GridCoordinate::SCREEN).toGrid();
        GridCoordinate clyde = GridCoordinate(this->getPosition(), GridCoordinate::SCREEN).toGrid();
        if (clyde.distance(grid) > 8) {
            this->_target = grid.toScreen();
        } else {
            this->_target = home;
        }
    }
}

void Clyde::recalculateDotLimit() {
    this->_dotLimit = currentLevel==0?60:currentLevel==1?50:0;
}
