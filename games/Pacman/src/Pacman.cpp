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
#include "PacmanGlobals.hpp"
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
    for (std::size_t y = 0; y < MAP_HEIGHT; y++) {
        for (std::size_t x = 0; x < MAP_WIDTH; x++) {
            this->_map[y][x].setPosition(GridCoordinate(x, y).toScreen());
        }
    }
    this->_arcade->setPreferredSize(MAP_WIDTH * 8 * SCALE, MAP_HEIGHT * 8 * SCALE);

    currentLevel = 0;
    currentLives = 4;
    isFrightened = false;
    frightenedMsLeft = 0;
    this->_score = 0;
    this->replaceDots();
    *score = this->_score;
    this->pac.setPosition(GridCoordinate(13, 26).toScreen());

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
    int fps = (int) (1.f / this->_arcade->getDeltaTime());
    // Draw map
    for (auto & line : this->_map) {
        for (const auto & piece : line) {
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
    highScore.setText(std::to_string(this->_score)); // TODO Change to highscore
    highScore.setPosition(GridCoordinate((int) (17 - highScore.getChars().size()), 1).toScreen());
    for (auto &c : highScoreText.getChars()) {
        this->_arcade->display(*c);
    }
    const int oneUpBlinkTimeInMs = 500; // Time in ms (time between two blinks)
    static std::size_t lastBlinkOneUp = 0;
    static bool displayOneUp = true;
    if (this->_arcade->getTime() - lastBlinkOneUp > oneUpBlinkTimeInMs) {
        displayOneUp = !displayOneUp;
        lastBlinkOneUp = this->_arcade->getTime();
    }
    if (displayOneUp) {
        for (auto &c: oneUP.getChars()) {
            this->_arcade->display(*c);
        }
    }
    for (auto &c : scoreText.getChars()) {
        this->_arcade->display(*c);
    }
    for (auto &c : highScore.getChars()) {
        this->_arcade->display(*c);
    }
    static LevelCounter levelCounter;
    levelCounter.setLevel(currentLevel + 1);
    this->_arcade->display(levelCounter);
    static LiveCounter livesCounter;
    livesCounter.setLives(currentLives);
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
        if (!dot->isEnergizer() || displayEnergizer) {
            this->_arcade->display(*dot);
        }
    }
    // Update ghosts
    for (auto &ghost : this->ghosts) {
        ghost->update(this->pac, this->_map, this->ghosts);
    }
    // Update pacman
    this->pac.update(this->dots, this->_map, this->ghosts);
    if (frightenedMsLeft > 0) {
        if (frightenedMsLeft == levels[currentLevel].frightenedDuration * 1000) {
            for (auto &ghost : this->ghosts) {
                ghost->setFrightened(true);
                ghost->setStrategy(SCATTER);
            }
        }
        frightenedMsLeft -= (int) (this->_arcade->getDeltaTime() * 1000.f);
        if (frightenedMsLeft <= 0) {
            isFrightened = false;
            frightenedMsLeft = 0;
            for (auto &ghost : this->ghosts) {
                ghost->setStrategy(CHASE);
                ghost->setFrightened(false);
            }
        }
    }
    // Display pacman
    this->_arcade->display(this->pac);
    for (auto &bonus: this->pac.getBonuses()) {
        this->_arcade->display(*bonus);
    }
    // Display ghosts
    for (auto &ghost : this->ghosts) {
        this->_arcade->display(*ghost);
    }

    this->_arcade->flipFrame();
    frame++;
    frame = frame % fps;
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