/*
** EPITECH PROJECT, 2024
** Pacman
** File description:
** No file there , just an epitech header example .
** You can even have multiple lines if you want !
*/

#include "Move.hpp"
#include "../entities/Pac.hpp"
#include "common/utils/RGBAColor.hpp"
#include "../PacmanGlobals.hpp"

Move::Move(const GridCoordinate &from, APacManEntity &actor, Direction direction)
    : _from(from), _to(from), _direction(direction), _direction_(NONE), _actor(&actor) {}

Move::Move(const GridCoordinate &from, APacManEntity &actor, Direction direction, Direction _direction)
    : _from(from), _to(from), _direction(direction), _direction_(_direction), _actor(&actor) {}


void checkTeleport(GridCoordinate &grid) {
    GridCoordinate rightPortal = GridCoordinate(27, 17).toScreen();
    if (grid.getX() < 0) {
        grid.setX(rightPortal.getX());
    } else if ((float) grid.getX() >= MAP_WIDTH * 8.f * SCALE) {
        grid.setX(0);
    }
}

void Move::computeLanding() {
    float deltaTime = arcade->getDeltaTime(); // in s
    const int tilesPerSecond = 11;
    const int speed = (int) (tilesPerSecond * deltaTime * 8 * SCALE);
    GridCoordinate pacManSpeed = GridCoordinate(speed, speed, GridCoordinate::SCREEN);
    double speedFactor;

    if (isFrightened) {
        if (dynamic_cast<const Pac *>(_actor) != nullptr) {
            if (dynamic_cast<const Pac *>(_actor)->hasEaten()) {
                speedFactor = 0;
                dynamic_cast<Pac *>(_actor)->setEaten(false);
            } else {
                speedFactor = levels[currentLevel].pacmanFrightenedSpeed;
            }
        } else {
            if (dynamic_cast<const AGhost *>(_actor)->isFrightened()) {
                speedFactor = levels[currentLevel].ghostFrightenedSpeed;
            } else {
                speedFactor = levels[currentLevel].ghostSpeed;
            }
        }
    } else {
        if (dynamic_cast<const Pac *>(_actor) != nullptr) {
            if (dynamic_cast<const Pac *>(_actor)->hasEaten()) {
                speedFactor = 0;
                dynamic_cast<Pac *>(_actor)->setEaten(false);
            } else {
                speedFactor = levels[currentLevel].pacmanSpeed;
            }
        } else {
            if (dynamic_cast<const AGhost *>(_actor)->isCaged()) {
                speedFactor = 0.5;
            } else {
                speedFactor = levels[currentLevel].ghostSpeed;
            }
        }
    }

    GridCoordinate z = GridCoordinate(_from).toGrid();
    if (dynamic_cast<const AGhost *>(_actor) != nullptr && (z.getX() <= 5 || z.getX() >= 23) && z.getY() == 17) {
        speedFactor = levels[currentLevel].ghostTunnelSpeed;
    }
    if (dynamic_cast<const AGhost *>(_actor) != nullptr && dynamic_cast<const AGhost *>(_actor)->isDead()) {
        speedFactor = 1;
    }
    int deltaX = (int) round(pacManSpeed.getX() * speedFactor);
    int deltaY = (int) round(pacManSpeed.getY() * speedFactor);
    bool isGoingVertically = this->_direction == Direction::UP || this->_direction == Direction::DOWN;
    this->_to = GridCoordinate(this->_from);
    switch (this->_direction) {
        case UP:
            this->_to.setY(this->_to.getY() - deltaY);
            break;
        case DOWN:
            this->_to.setY(this->_to.getY() + deltaY);
            break;
        case LEFT:
            this->_to.setX(this->_to.getX() - deltaX);
            break;
        case RIGHT:
            this->_to.setX(this->_to.getX() + deltaX);
            break;
        case NONE:
            break;
    }
    GridCoordinate grid = GridCoordinate(this->_to).round();
    double dist = grid.distance(this->_to);
    if (dist > 0) {
        if(isGoingVertically){
            if(this->_to.getX() > grid.getX()){
                this->_to.setX((int)(this->_to.getX() - deltaX/4.));
            } else if (this->_to.getX() < grid.getX()){
                this->_to.setX((int)(this->_to.getX() + deltaX/4.));
            }
        } else {
            if(this->_to.getY() > grid.getY()){
                this->_to.setY((int)(this->_to.getY() - deltaY/4.));
            } else if (this->_to.getY() < grid.getY()) {
                this->_to.setY((int) (this->_to.getY() + deltaY/4.));
            }
        }
    }
    checkTeleport(this->_to);
}

bool Move::isLegal(const Wall (&map)[37][28]) const {
    GridCoordinate grid = GridCoordinate(_to).toGrid();
    GridCoordinate front = GridCoordinate(_from).toGrid();
    bool isPac = dynamic_cast<const Pac *>(_actor) != nullptr;
    bool isDead = false;

    std::vector<Wall::WallType> walkable = {Wall::WallType::EMPTY, Wall::WallType::DOT, Wall::WallType::ENERGIZER};
    if (!isPac) {
        if (this->_actor != nullptr && dynamic_cast<const AGhost *>(this->_actor)->isDead()) {
            isDead = true;
            walkable.push_back(Wall::WallType::GATE);
        }
    }
    if (this->_actor == nullptr) {
        return false;
    }

    bool isChangingDirection = this->_direction != this->_actor->getDirection();
    switch (this->_direction) {
        case UP:
            front.setY(front.getY() - 1);
            break;
        case DOWN:
            front.setY(front.getY() + 1);
            break;
        case LEFT:
            front.setX(front.getX() - 1);
            break;
        case RIGHT:
            front.setX(front.getX() + 1);
            break;
        case NONE:
            break;
    }
    front = GridCoordinate(front).toScreen();
    checkTeleport(front);
    front = GridCoordinate(front).toGrid();

    if (isChangingDirection) {
        grid = front;
    }

    GridCoordinate center = GridCoordinate(_from).round();
    double distToCenter = center.distance(this->_from);
    bool canReverse = dynamic_cast<const AGhost *>(this->_actor) == nullptr || dynamic_cast<const AGhost *>(this->_actor)->hasToReverse();

    bool isWalkable = std::find(walkable.begin(), walkable.end(), map[grid.getY()][grid.getX()].getType()) != walkable.end();
    bool isFrontWalkable = std::find(walkable.begin(), walkable.end(), map[front.getY()][front.getX()].getType()) != walkable.end();
    GridCoordinate tempA = GridCoordinate(_from).round();
    GridCoordinate tempB = GridCoordinate(_to).round();
    bool isGoingToFar = tempA.distance(this->_from) < tempB.distance(this->_to);
    bool isReversing = (!this->_direction) == (this->_direction_ != NONE ? this->_direction_ : this->_actor->getDirection());
    bool isForbiddenUp = (front.getX() == 15 || front.getX() == 12) && (front.getY() == 25 || front.getY() == 13) && this->_direction == Direction::UP && (dynamic_cast<const AGhost *>(this->_actor) != nullptr && !dynamic_cast<const AGhost *>(this->_actor)->isDead() && !dynamic_cast<const AGhost *>(this->_actor)->isFrightened());
    bool isCloseEnough = isPac || (distToCenter <= 1) || !isChangingDirection || isDead;
    bool isLegal = isWalkable && !(isGoingToFar && !isFrontWalkable) && (!isReversing || canReverse) && !isForbiddenUp && isCloseEnough;

    if (IS_GIZMOS(*arcade)) {
        GridCoordinate gridScreen = GridCoordinate(this->_to).round();
        GIZMOS(*arcade)->drawRect(gridScreen, gridScreen + Coord2D(8 * SCALE, 8 * SCALE), false, isLegal ? RGBAColor::GREEN : RGBAColor::RED);
    }

    return isLegal;
}

Direction Move::getDirection() const {
    return _direction;
}

const GridCoordinate &Move::getTo() const {
    return _to;
}
