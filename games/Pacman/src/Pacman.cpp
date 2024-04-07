/*
** EPITECH PROJECT, 2024
** Arcade
** File description:
** No file there , just an epitech header example .
** You can even have multiple lines if you want !
*/

#include "Pacman.hpp"
#include "utils/GridCoordinate.hpp"
#include "entities/PacManText.hpp"
#include "entities/LevelCounter.hpp"
#include "entities/LiveCounter.hpp"
#include "entities/ghosts/Pinky.hpp"
#include "entities/ghosts/Blinky.hpp"
#include "entities/ghosts/Clyde.hpp"
#include "entities/ghosts/Inky.hpp"
#include "common/displayable/entities/SimpleEntity.hpp"
#include "PacmanGlobals.hpp"
#include "common/displayable/entities/SimpleSprite.hpp"
#include <string>
#include <iostream>

extern "C" {
    __attribute__((constructor))
    void load_lib()
    {
        std::cout << "Loading Pacman game" << std::endl;
    }

    __attribute__((destructor))
    void unload_lib()
    {
        std::cout << "Unloading Pacman game" << std::endl;
    }

    std::unique_ptr<Pacman> create_game(void) {
        return std::make_unique<Pacman>();
    }

    const std::string &get_name(void) {
        const static std::string name = "Pacman";
        return name;
    }
}

Pacman::Pacman() = default;
bool isFrightened = false;
int currentLevel = 0;
int currentLives = 4;
std::shared_ptr<IArcade> arcade;
int *score = nullptr;
int frightenedMsLeft;
Pacman *game;
bool isGlobalDotCounter;
std::size_t globalDotCounter;
bool isInAnimation;
Animation animation;
std::size_t animationStart;
bool shouldDisplayActors;
bool shouldDisplayAnything;
Fruit *fruit1 = nullptr;
Fruit *fruit2 = nullptr;

Pacman::~Pacman() {
    for (auto &ghost : this->ghosts) {
        delete ghost;
    }
    for (auto &dot : this->dots) {
        delete dot;
    }
    delete fruit1;
    fruit1 = nullptr;
    delete fruit2;
    fruit2 = nullptr;
}

void Pacman::init(std::shared_ptr<IArcade> _arcade) {
    this->_arcade = _arcade;
    game = this;
    arcade = this->_arcade;
    this->_score = 0;
    score = &this->_score;

    this->_arcade->bindEvent(IEvent::EventType::_KEY_PRESS, _KEY_Z, [this](const IEvent &event) {
        this->pac.handleEvent(event);
    });
    this->_arcade->bindEvent(IEvent::EventType::_KEY_PRESS, _KEY_Q, [this](const IEvent &event) {
        this->pac.handleEvent(event);
    });
    this->_arcade->bindEvent(IEvent::EventType::_KEY_PRESS, _KEY_S, [this](const IEvent &event) {
        this->pac.handleEvent(event);
    });
    this->_arcade->bindEvent(IEvent::EventType::_KEY_PRESS, _KEY_D, [this](const IEvent &event) {
        this->pac.handleEvent(event);
    });
    this->_arcade->bindEvent(IEvent::EventType::_KEY_PRESS, _KEY_UP, [this](const IEvent &event) {
        this->pac.handleEvent(event);
    });
    this->_arcade->bindEvent(IEvent::EventType::_KEY_PRESS, _KEY_DOWN, [this](const IEvent &event) {
        this->pac.handleEvent(event);
    });
    this->_arcade->bindEvent(IEvent::EventType::_KEY_PRESS, _KEY_RIGHT, [this](const IEvent &event) {
        this->pac.handleEvent(event);
    });
    this->_arcade->bindEvent(IEvent::EventType::_KEY_PRESS, _KEY_LEFT, [this](const IEvent &event) {
        this->pac.handleEvent(event);
    });
}

void Pacman::start() {
    game = this;
    arcade = this->_arcade;
    for (std::size_t y = 0; y < MAP_HEIGHT; y++) {
        for (std::size_t x = 0; x < MAP_WIDTH; x++) {
            this->_map[y][x].setPosition(GridCoordinate(x, y).toScreen());
        }
    }
    this->_arcade->setPreferredSize(MAP_WIDTH * 8 * SCALE, MAP_HEIGHT * 8 * SCALE);

    currentLevel = -1;
    currentLives = 4;
    shouldDisplayActors = true;
    shouldDisplayAnything = true;
    this->_score = 0;
    *score = this->_score;
    isInAnimation = false;
    animation = None;
    animationStart = 0;
    for (auto &ghost : this->ghosts) {
        delete ghost;
    }
    this->ghosts.clear();

    auto *blinky = new Blinky();
    this->ghosts.push_back(blinky);

    auto *pinky = new Pinky();
    this->ghosts.push_back(pinky);

    auto *inky = new Inky();
    this->ghosts.push_back(inky);

    auto *clyde = new Clyde();
    this->ghosts.push_back(clyde);

    this->reset(true);
}

void Pacman::replaceDots() {
    for (auto &dot : this->dots) {
        delete dot;
    }
    this->dots.clear();

    for (auto & line : this->_map) {
        for (auto & cell : line) {
            if (cell.getType() == Wall::WallType::DOT || cell.getType() == Wall::WallType::ENERGIZER) {
                auto *dot = new PacDot(cell.getType() == Wall::WallType::ENERGIZER);
                dot->setPosition(cell.getPosition());
                this->dots.push_back(dot);
            }
        }
    }
}

void Pacman::run() {
    static int frame = 0;
    int fps = (int) (1.f / (this->_arcade->getDeltaTime() + 0.0001f));
    // Draw map
    for (auto & line : this->_map) {
        for (const auto & piece : line) {
            if (shouldDisplayAnything)
                this->_arcade->display(piece);
        }
    }
    // Draw ui
    static PacManText highScoreText("HIGH SCORE", PacManTextColor::WHITE);
    highScoreText.setPosition(GridCoordinate(9, 0).toScreen());
    static PacManText oneUP("1UP", PacManTextColor::WHITE);
    oneUP.setPosition(GridCoordinate(3, 0).toScreen());
    static PacManText scoreText(std::to_string(this->_score), PacManTextColor::WHITE);
    scoreText.setText(std::to_string(this->_score));
    scoreText.setPosition(GridCoordinate((int) (7 - scoreText.getChars().size()), 1).toScreen());
    static PacManText highScore(std::to_string(this->_score), PacManTextColor::WHITE);
    highScore.setText(std::to_string(this->_arcade->getCurrentGameHighScore()));
    highScore.setPosition(GridCoordinate((int) (17 - highScore.getChars().size()), 1).toScreen());
    for (auto &c : highScoreText.getChars()) {
        if (shouldDisplayAnything)
            this->_arcade->display(*c);
    }
    const int oneUpBlinkTimeInMs = 500; // Time in ms (time between two blinks)
    static std::size_t lastBlinkOneUp = 0;
    static bool displayOneUp = true;
    if (this->_arcade->getTime() - lastBlinkOneUp > oneUpBlinkTimeInMs) {
        displayOneUp = !displayOneUp;
        lastBlinkOneUp = this->_arcade->getTime();
    }
    if (displayOneUp || isInAnimation) {
        for (auto &c: oneUP.getChars()) {
            if (shouldDisplayAnything)
                this->_arcade->display(*c);
        }
    }
    for (auto &c : scoreText.getChars()) {
        if (shouldDisplayAnything)
            this->_arcade->display(*c);
    }
    for (auto &c : highScore.getChars()) {
        if (shouldDisplayAnything)
            this->_arcade->display(*c);
    }
    static LevelCounter levelCounter;
    levelCounter.setLevel(currentLevel + 1);
    if (shouldDisplayAnything)
        this->_arcade->display(levelCounter);
    static LiveCounter livesCounter;
    livesCounter.setLives(currentLives);
    if (shouldDisplayAnything)
        this->_arcade->display(livesCounter);

    // Draw dots
    const int energizerBlinkTimeInMs = 250; // Time in ms (time between two blinks)
    static std::size_t lastBlink = 0;
    static bool displayEnergizer = true;
    if (this->_arcade->getTime() - lastBlink > energizerBlinkTimeInMs) {
        displayEnergizer = !displayEnergizer;
        lastBlink = this->_arcade->getTime();
    }
    for (auto & dot : this->dots) {
        if ((!dot->isEnergizer() || displayEnergizer || isInAnimation) && shouldDisplayAnything) {
            this->_arcade->display(*dot);
        }
    }
    if (!isInAnimation) {
        // Update ghosts
        for (auto &ghost: this->ghosts) {
            ghost->update(this->pac, this->_map, this->ghosts);
        }
        // Update pacman
        this->pac.update(this->dots, this->_map, this->ghosts);
        if (frightenedMsLeft > 0) {
            if (frightenedMsLeft == levels[currentLevel].frightenedDuration * 1000) {
                for (auto &ghost : this->ghosts) {
                    ghost->setFrightened(true);
                }
            }
            frightenedMsLeft -= (int) (this->_arcade->getDeltaTime() * 1000.f);
            if (frightenedMsLeft <= 0) {
                isFrightened = false;
                frightenedMsLeft = 0;
                for (auto &ghost : this->ghosts) {
                    ghost->setFrightened(false);
                }
            }
        }
    }
    if (shouldDisplayActors && shouldDisplayAnything) {
        // Display pacman
        this->_arcade->display(this->pac);
        // Display score bonus
        for (auto &bonus: this->pac.getBonuses()) {
            this->_arcade->display(*bonus);
        }
        // Display ghosts
        for (auto &ghost : this->ghosts) {
            this->_arcade->display(*ghost);
        }
        if (fruit1->shouldBeDisplayed()) {
            this->_arcade->display(*fruit1);
        }
        if (fruit2->shouldBeDisplayed()) {
            this->_arcade->display(*fruit2);
        }
    }
    this->handleAnimation();
    if (this->dots.empty()) {
        if (!isInAnimation) {
            animation = BoardBlink;
            isInAnimation = true;
            animationStart = this->_arcade->getTime();
            shouldDisplayActors = false;
        }
    } else {
        std::size_t count = this->dots.size();
        if (count == 240-70 && !fruit1->hasSpawned() && !fruit1->hasBeenEaten()) {
            fruit1->setApparitionTime(this->_arcade->getTime());
            fruit1->setSpawned(true);
            fruit1->setEaten(false);
        }
        if (count == 240-170 && !fruit2->hasSpawned() && !fruit2->hasBeenEaten()) {
            fruit2->setApparitionTime(this->_arcade->getTime());
            fruit2->setSpawned(true);
            fruit2->setEaten(false);
        }
    }

    this->_arcade->flipFrame();
    frame++;
    frame = frame % (std::max(fps, 1));
}

Direction operator!(Direction direction) {
    switch (direction) {
        case UP:
            return DOWN;
        case DOWN:
            return UP;
        case LEFT:
            return RIGHT;
        case RIGHT:
            return LEFT;
        case NONE:
            return NONE;
    }
    return NONE;
}

AGhost *Pacman::getFirstCagedGhost() {
    for (auto &ghost : this->ghosts) {
        if (ghost->isCaged()) {
            return ghost;
        }
    }
    return nullptr;
}

void Pacman::reset(bool isNewLevel) {
    if(isNewLevel) {
        currentLevel++;
        this->replaceDots();
        isGlobalDotCounter = false;

        if (fruit1 != nullptr) {
            delete fruit1;
            fruit1 = nullptr;
        }
        if (fruit2 != nullptr) {
            delete fruit2;
            fruit2 = nullptr;
        }
        fruit1 = new Fruit(levels[currentLevel].bonus);
        fruit1->setPosition(GridCoordinate(13, 20).toScreen());
        fruit2 = new Fruit(levels[currentLevel].bonus);
        fruit2->setPosition(GridCoordinate(13, 20).toScreen());
    } else {
        isGlobalDotCounter = true;
    }
    globalDotCounter = 0;

    for(auto &ghost : ghosts) {
        ghost->setPosition(GridCoordinate(ghost->getSpawnPosition()));
        if(dynamic_cast<Blinky *>(ghost) != nullptr) {
            ghost->setCaged(false);
        }
        else {
            ghost->setCaged(true);
        }
        if(isNewLevel) ghost->setPersonalDotCount(0);
        ghost->setDead(false);
        ghost->setFrightened(false);
        ghost->setStrategy(CHASE);
        ghost->recalculateDotLimit();
        if (dynamic_cast<Pinky *>(ghost) != nullptr) {
            ghost->setDirection(Direction::UP);
        } else {
            ghost->setDirection(Direction::DOWN);
        }
    }

    this->pac.setPosition(GridCoordinate(Pac::getSpawnPosition()));
    this->pac.setDirection(Direction::RIGHT);
    this->pac.setEaten(false);

    frightenedMsLeft = 0;
    isFrightened = false;

    if (fruit1->hasSpawned() && !fruit1->hasBeenEaten()) {
        fruit1->setEaten(true);
    }
    if (fruit2->hasSpawned() && !fruit2->hasBeenEaten()) {
        fruit2->setEaten(true);
    }

    animation = Ready;
    isInAnimation = true;
    animationStart = this->_arcade->getTime();
}

void Pacman::handleAnimation() {
    if (isInAnimation) {
        if (animation == Ready) {
            if (this->_arcade->getTime() - animationStart > 2000) {
                isInAnimation = false;
                animation = None;
            } else {
                static auto ready = SimpleEntity("assets/games/pacman/ready.png", 92, 14);
                ready.setPosition(GridCoordinate(11, 20).toScreen());
                ready.setSize(SCALE * 8. / 14.);
                this->_arcade->display(ready);
            }
        } else if (animation == BoardBlink) {
            if (this->_arcade->getTime() - animationStart > 3000) {
                isInAnimation = false;
                animation = None;
                shouldDisplayActors = true;
                reset(true);
            } else {
                static const std::size_t blinkTime = 250; // Time in ms (time between two blinks)
                static std::size_t lastBlink = 0;
                static bool boardIsWhite = false;
                if (this->_arcade->getTime() - lastBlink > blinkTime) {
                    boardIsWhite = !boardIsWhite;
                    lastBlink = this->_arcade->getTime();
                }
                for (auto & line : this->_map) {
                    for (auto & cell : line) {
                        cell.setWhite(boardIsWhite);
                    }
                }
            }
        } else if (animation == Death) {
            static int animationStep = 0;
            static const std::size_t frameLasting = 200; // in ms
            static const std::size_t frameCount = 11;
            if (this->_arcade->getTime() - animationStart > frameLasting * frameCount) {
                isInAnimation = false;
                animation = None;
                shouldDisplayActors = true;
                animationStep = 0;
                currentLives--;
                if (currentLives > 0) {
                    reset(false);
                } else {
                    isInAnimation = true;
                    animation = GameOver;
                    animationStart = this->_arcade->getTime();
                    shouldDisplayActors = false;
                    shouldDisplayAnything = false;
                }
            } else {
                static auto death = SimpleEntity("assets/games/pacman/pacman/pac_death.png", 344, 22);
                static std::size_t lastAnimationChange = 0;
                if (this->_arcade->getTime() - lastAnimationChange > frameLasting) {
                    lastAnimationChange = this->_arcade->getTime();
                    animationStep++;
                }
                death.setPosition(this->pac.getPosition());
                death.setSize(SCALE * 8. / 22.);
                SimpleSprite sprite = SimpleSprite(death.getSprite());
                sprite.setDrawRect({(std::size_t) animationStep*32 - 2, 0, 30, 21});
                death.setSprite(sprite);
                this->_arcade->display(death);
            }
        } else if (animation == GameOver) {
            static PacManText gameover("GAME OVER", PacManTextColor::RED);
            gameover.setPosition(GridCoordinate(MAP_WIDTH / 2 - 5, MAP_HEIGHT / 2).toScreen());
            for (auto &c : gameover.getChars()) {
                this->_arcade->display(*c);
            }
            if (this->_arcade->getTime() - animationStart > 3000) {
                isInAnimation = false;
                animation = None;
                shouldDisplayAnything = true;
                shouldDisplayActors = true;
                start();
            }
        }
    }
}

GhostStrategy Pacman::getGlobalStrategy() {
    static std::size_t lastStrategyChange = 0;
    static int changeCount = -1;
    static std::size_t index = currentLevel == 1 ? 0 : (currentLevel >= 5 ? 2 : 1);

    if (changeCount == -1) {
        changeCount = 0;
        lastStrategyChange = this->_arcade->getTime();
    }

    static const GhostStrategyTime currentStrategy = strategyTimes[index][changeCount];

    if (currentStrategy.lasting == 0) {
        return currentStrategy.strategy;
    }

    if (this->_arcade->getTime() - lastStrategyChange > currentStrategy.lasting) {
        lastStrategyChange = this->_arcade->getTime();
        changeCount++;
    }
    return strategyTimes[index][changeCount].strategy;
}
