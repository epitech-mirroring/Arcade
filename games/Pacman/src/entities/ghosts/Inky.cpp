/*
** EPITECH PROJECT, 2024
** Pacman
** File description:
** No file there , just an epitech header example .
** You can even have multiple lines if you want !
*/

#include "Inky.hpp"
#include "Blinky.hpp"
#include "common/utils/RGBAColor.hpp"
#include "../../PacmanGlobals.hpp"

Inky::Inky(): AGhost("assets/games/pacman/ghosts/inky.png",
                     GridCoordinate(11, 17).toScreen()) {
    this->setPosition(GridCoordinate(11, 17).toScreen());
    this->setColor(RGBAColor::CYAN);
}

void Inky::updateTarget(const APacManEntity &pac, const std::vector<AGhost *> &ghost) {
    static const GridCoordinate home = GridCoordinate(MAP_WIDTH-1, MAP_HEIGHT-3).toScreen();

    if (IS_GIZMOS(*arcade)) {
        GIZMOS(*arcade)->drawRect(home, home + Coord2D(SCALE * 8, SCALE * 8), false, RGBAColor::CYAN);
    }

    Blinky *blinky = nullptr;
    for (auto &g : ghost) {
        if (dynamic_cast<Blinky *>(g) != nullptr) {
            blinky = dynamic_cast<Blinky *>(g);
        }
    }
    if (blinky == nullptr) {
        return;
    }

    if(this->_isDead || this->_isCaged){
        this->_target = _cage;
    } else if(_strategy == SCATTER){
        this->_target = home;
    }
    else if(_strategy == CHASE){
        GridCoordinate grid = GridCoordinate(pac.getPosition(), GridCoordinate::SCREEN).toGrid();
        switch (pac.getDirection()) {
            case Direction::RIGHT:
                grid.setX(grid.getX() + 2);
                break;
            case Direction::DOWN:
                grid.setY(grid.getY() + 2);
                break;
            case Direction::LEFT:
                grid.setX(grid.getX() - 2);
                break;
            case Direction::UP:
                grid.setY(grid.getY() - 2);
                break;
            case NONE:
                break;
        }
        grid.toScreen();
        int vX = (int) grid.getX() - (int) blinky->getPosition().getX();
        int vY = (int) grid.getY() - (int) blinky->getPosition().getY();
        grid.setX(grid.getX() + vX);
        grid.setY(grid.getY() + vY);
        this->_target = grid;
    }
}

void Inky::recalculateDotLimit() {
    this->_dotLimit = currentLevel == 0 ? 30:0;
}