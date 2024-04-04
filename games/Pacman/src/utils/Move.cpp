/*
** EPITECH PROJECT, 2024
** Pacman
** File description:
** No file there , just an epitech header example .
** You can even have multiple lines if you want !
*/

#include "Move.hpp"
#include "../entities/Pac.hpp"
#include "../entities/AGhost.hpp"

Move::Move(const Coord2D &from, APacManEntity &actor, Direction direction)
    : _from(from), _to(from), _direction(direction), _direction_(NONE), _actor(&actor) {}

Move::Move(const Coord2D &from, APacManEntity &actor, Direction direction, Direction _direction)
    : _from(from), _to(from), _direction(direction), _direction_(_direction), _actor(&actor) {}


void checkTeleport(Coord2D &grid) {
    Coord2D rightPortal = Coord2D(COORD_TO_SCREEN(27), COORD_TO_SCREEN(17));
    if (grid.getX() < 0) {
        grid.setX(rightPortal.getX());
    } else if (grid.getX() > COORD_TO_SCREEN(MAP_WIDTH)) {
        grid.setX(0);
    }
}

void Move::computeLanding() {
    float deltaTime = arcade->getDeltaTime(); // in s
    const int tilesPerSecond = 11;
    const int speed = (int) (tilesPerSecond * deltaTime * 8 * SCALE);
    Coord2D pacManSpeed = Coord2D(speed, speed);
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
            speedFactor = levels[currentLevel].ghostFrightenedSpeed;
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
            speedFactor = levels[currentLevel].ghostSpeed;
        }
    }

    Coord2D z = Coord2D(SCREEN_TO_COORD(_from.getX()), SCREEN_TO_COORD(_from.getY()));
    if (dynamic_cast<const AGhost *>(_actor) != nullptr && (z.getX() <= 5 || z.getX() >= 23) && z.getY() == 17) {
        speedFactor = levels[currentLevel].ghostTunnelSpeed;
    }
    if (dynamic_cast<const AGhost *>(_actor) != nullptr && dynamic_cast<const AGhost *>(_actor)->isDead()) {
        speedFactor = 1;
    }
    int deltaX = (int) round(pacManSpeed.getX() * speedFactor);
    int deltaY = (int) round(pacManSpeed.getY() * speedFactor);
    bool isGoingVertically = this->_direction == Direction::UP || this->_direction == Direction::DOWN;
    this->_to = Coord2D(this->_from);
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
    Coord2D grid = Coord2D(COORD_TO_SCREEN(SCREEN_TO_COORD(this->_to.getX())), COORD_TO_SCREEN(SCREEN_TO_COORD(this->_to.getY())));
    double dist = grid.distance(this->_to);
    if (dynamic_cast<const Pac *>(_actor) != nullptr) {
        if (dist > 0) {
            if(isGoingVertically){
                if(this->_to.getX() > grid.getX()){
                    this->_to.setX((int)(this->_to.getX() - deltaX/2.));
                } else if (this->_to.getX() < grid.getX()){
                    this->_to.setX((int)(this->_to.getX() + deltaX/2.));
                }
            } else {
                if(this->_to.getY() > grid.getY()){
                    this->_to.setY((int)(this->_to.getY() - deltaY/2.));
                } else if (this->_to.getY() < grid.getY()) {
                    this->_to.setY((int) (this->_to.getY() + deltaY / 2.));
                }
            }
        }
    } else {
        if (dist > 0) {
            if(isGoingVertically){
                if(this->_to.getX() > grid.getX()){
                    this->_to.setX((int)(this->_to.getX() - deltaX/3.));
                } else if (this->_to.getX() < grid.getX()){
                    this->_to.setX((int)(this->_to.getX() + deltaX/3.));
                }
            } else {
                if(this->_to.getY() > grid.getY()){
                    this->_to.setY((int)(this->_to.getY() - deltaY/3.));
                } else if (this->_to.getY() < grid.getY()) {
                    this->_to.setY((int) (this->_to.getY() + deltaY/3.));
                }
            }
        }
    }
    checkTeleport(this->_to);
}

bool Move::isLegal(const Wall (&map)[37][28]) const {
    Coord2D grid = Coord2D(SCREEN_TO_COORD(_to.getX()), SCREEN_TO_COORD(_to.getY()));
    Coord2D front = Coord2D(SCREEN_TO_COORD(_from.getX()), SCREEN_TO_COORD(_from.getY()));
    bool isPac = dynamic_cast<const Pac *>(_actor) != nullptr;
    bool isDead = false;

    std::vector<Wall::WallType> walkable = {Wall::WallType::EMPTY};
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
    front = Coord2D(COORD_TO_SCREEN(front.getX()), COORD_TO_SCREEN(front.getY()));
    checkTeleport(front);
    front = Coord2D(SCREEN_TO_COORD(front.getX()), SCREEN_TO_COORD(front.getY()));

    if (isChangingDirection) {
        grid = front;
    }

    Coord2D center = Coord2D(COORD_TO_SCREEN(SCREEN_TO_COORD(this->_from.getX())), SCREEN_TO_COORD(this->_from.getY()));
    double distToCenter = center.distance(this->_from);
    bool canReverse = dynamic_cast<const AGhost *>(this->_actor) == nullptr || dynamic_cast<const AGhost *>(this->_actor)->hasToReverse();

    bool isWalkable = std::find(walkable.begin(), walkable.end(), map[grid.getY()][grid.getX()].getType()) != walkable.end();
    bool isFrontWalkable = std::find(walkable.begin(), walkable.end(), map[front.getY()][front.getX()].getType()) != walkable.end();
    Coord2D tempA = Coord2D(COORD_TO_SCREEN(SCREEN_TO_COORD(this->_from.getX())), SCREEN_TO_COORD(this->_from.getY()));
    Coord2D tempB = Coord2D(COORD_TO_SCREEN(SCREEN_TO_COORD(this->_to.getX())), SCREEN_TO_COORD(this->_to.getY()));
    bool isGoingToFar = tempA.distance(this->_from) < tempB.distance(this->_to);
    bool isReversing = (this->_direction+2)%4 == (this->_direction_ != NONE ? this->_direction_ : this->_actor->getDirection());
    bool isForbiddenUp = (front.getX() == 15 || front.getX() == 12) && (front.getY() == 25 || front.getY() == 13) && this->_direction == Direction::UP; // && is Blinky
    bool isCloseEnough = isPac || (distToCenter <= 2) || !isChangingDirection;
    bool isLegal = isWalkable && !(isGoingToFar && !isFrontWalkable) && (!isReversing || canReverse) && (!isForbiddenUp || isDead || isPac) && isCloseEnough;

    return isLegal;
}

const Coord2D &Move::getTo() const {
    return _to;
}
