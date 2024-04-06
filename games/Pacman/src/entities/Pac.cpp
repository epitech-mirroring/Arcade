/*
** EPITECH PROJECT, 2024
** Pacman
** File description:
** No file there , just an epitech header example .
** You can even have multiple lines if you want !
*/

#include "Pac.hpp"
#include "../PacmanGlobals.hpp"
#define SCALE_PACKMAN (SCALE * 8. / 28.)

const GridCoordinate Pac::_spawn = GridCoordinate(13, 26).toScreen();

Pac::Pac(): APacManEntity("assets/games/pacman/pacman/pacman.png", 208, 26) {
    this->_sprite->setDrawRect({0, 0, 26, 26});
    this->setPosition(Pac::_spawn);
    this->setSize(SCALE_PACKMAN);
    this->_direction = Direction::LEFT;
    this->_newDirection = Direction::LEFT;
    this->_eaten = false;
    this->_animation = 0;
    this->_lastKill = 0;
    this->_killStreak = 0;
}

Pac::~Pac() {
    for (auto &bonus: _bonuses) {
        delete bonus;
    }
    _bonuses.clear();
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

void Pac::update(std::vector<PacDot *> &dots, const Wall (&map)[37][28], const std::vector<AGhost *> &ghosts) {
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

    static std::size_t lastEat = 0;
    for (std::size_t i = 0; i < dots.size(); i++) {
        PacDot *dot = dots[i];
        GridCoordinate dotGrid = GridCoordinate(dot->getPosition(), GridCoordinate::SCREEN).toGrid();
        GridCoordinate pacGrid = GridCoordinate(this->getPosition(), GridCoordinate::SCREEN).toGrid();
        if (dotGrid == pacGrid) {
            this->_eaten = true;
            if (dot->isEnergizer()) {
                if (score != nullptr)
                    *score += 40;
                isFrightened = true;
                frightenedMsLeft = levels[currentLevel].frightenedDuration * 1000;
            } else if (score != nullptr) {
                *score += 10;
            }
            dots.erase(dots.begin() + i);
            delete dot;

            AGhost *g = game->getFirstCagedGhost();
            if(g != nullptr){
                if(isGlobalDotCounter){
                    globalDotCounter++;
                    if(globalDotCounter == 7 || globalDotCounter == 17 || globalDotCounter == 32){
                        g->spawn(false);
                    }
                } else {
                    g->setPersonalDotCount(g->getPersonalDotCount() + 1);
                    if((int) g->getPersonalDotCount() >= g->getDotLimit()) g->spawn(false);
                }
            }
            lastEat = arcade->getTime();
            break;
        }
    }
    if (arcade->getTime() - lastEat > 6000) {
        lastEat = arcade->getTime();
        AGhost *g = game->getFirstCagedGhost();
        if(g != nullptr){
            g->spawn(false);
        }
    }

    for (AGhost *ghost : ghosts) {
        GridCoordinate ghostGrid = GridCoordinate(ghost->getPosition(), GridCoordinate::SCREEN).toGrid();
        GridCoordinate pacGrid = GridCoordinate(this->getPosition(), GridCoordinate::SCREEN).toGrid();
        if (ghostGrid == pacGrid) {
            if (ghost->isFrightened()) {
                ghost->kill();
                if (arcade->getTime() - _lastKill < levels[currentLevel].frightenedDuration * 1000ull) {
                    _killStreak++;
                    if (score != nullptr)
                        *score += (int) (200 * _killStreak);
                    BonusPoint point;
                    switch (_killStreak) {
                        case 1:
                        default:
                            point = _200;
                            break;
                        case 2:
                            point = _400;
                            break;
                        case 3:
                            point = _800;
                            break;
                        case 4:
                            point = _1600;
                            break;
                    }
                    this->_bonuses.push_back(new Bonus(ghost->getPosition(), point));
                } else {
                    _killStreak = 1;
                    if (score != nullptr)
                        *score += 200;
                    this->_bonuses.push_back(new Bonus(ghost->getPosition(),
                                                       _200));
                }
                _lastKill = arcade->getTime();
            } else if (!ghost->isDead()) {
                this->kill();
            }
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

    this->_bonuses = std::vector<Bonus *>(this->_bonuses.begin(), std::remove_if(this->_bonuses.begin(), this->_bonuses.end(), [](Bonus *bonus) {
        if (bonus->canBeDeleted()) {
            delete bonus;
            return true;
        }
        return false;
    }));
}

bool Pac::hasEaten() const {
    return this->_eaten;
}

void Pac::setEaten(bool eaten) {
    this->_eaten = eaten;
}

void Pac::kill() {
    isInAnimation = true;
    animation = Death;
    animationStart = arcade->getTime();
    shouldDisplayActors = false;
}

const std::vector<Bonus *> &Pac::getBonuses() const {
    return this->_bonuses;
}

const GridCoordinate &Pac::getSpawnPosition() {
    return _spawn;
}