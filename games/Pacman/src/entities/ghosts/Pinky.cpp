/*
** EPITECH PROJECT, 2024
** Pacman
** File description:
** No file there , just an epitech header example .
** You can even have multiple lines if you want !
*/

#include "Pinky.hpp"
#include "common/utils/RGBAColor.hpp"
#include "../../PacmanGlobals.hpp"

Pinky::Pinky(): AGhost("assets/games/pacman/ghosts/pinky.png",
                       GridCoordinate(13, 17).toScreen()) {
    this->setPosition(GridCoordinate(13, 17).toScreen());
    this->setColor(RGBAColor::MAGENTA);
}

void Pinky::updateTarget(const APacManEntity &pac, const std::vector<AGhost *> &ghost) {
    static const GridCoordinate home = GridCoordinate(2, 0).toScreen();
    (void) ghost;

    if (IS_GIZMOS(*arcade)) {
        GIZMOS(*arcade)->drawRect(home, home + Coord2D(SCALE * 8, SCALE * 8), false, RGBAColor::MAGENTA);
    }

    if(this->_isDead || this->_isCaged){
        this->_target = _cage;
    } else if(_strategy == SCATTER){
        this->_target = home;
    } else if(_strategy == CHASE){
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
