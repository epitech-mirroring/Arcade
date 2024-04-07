/*
** EPITECH PROJECT, 2024
** Arcade
** File description:
** No file there , just an epitech header example .
** You can even have multiple lines if you want !
*/

#include "core/menu/Menu.hpp"
#include "common/displayable/entities/SimpleEntity.hpp"
#include "common/displayable/primitives/Text.hpp"
#include "common/utils/Coord2D.hpp"
#include "common/utils/RGBAColor.hpp"
#include "core/Arcade.hpp"
#include <unordered_map>
#ifdef _KEY_T
#undef _KEY_T
#endif

Menu::Menu() = default;

void Menu::init(std::shared_ptr<IArcade> arcade) {
    this->_arcade = arcade;
    this->_tempUsername = TRANSFORM_TO(Arcade, *this->_arcade)->getCurrentPlayer().getName();
}

void Menu::run() {
    static SimpleEntity background = SimpleEntity("assets/menu_bg.png", 979, 551);
    static std::size_t frame = 0;

    static Text title = Text((IColor &) RGBAColor::WHITE, "Arcade", "assets/PressStart2P.ttf");
    static Coord2D titlePos = Coord2D(979 / 2 - 100, 20);
    title.setSize(30);
    title.setPosition(titlePos);
    this->_arcade->display(title);
    this->_arcade->display(background);

    static SimpleEntity betterTitle = SimpleEntity("assets/menu_title.png", 1024, 338);
    static Coord2D betterTitlePos = Coord2D((979/2) - (1024/4), 10);
    betterTitle.setPosition(betterTitlePos);
    betterTitle.setSize(0.5);
    this->_arcade->display(betterTitle);

    // Show games
    Coord2D gameTextPos = Coord2D(50, 150);
    Text gameTitle = Text((IColor &) RGBAColor::WHITE, "Games", "assets/PressStart2P.ttf");
    gameTitle.setSize(30);
    gameTitle.setPosition(gameTextPos);
    this->_arcade->display(gameTitle);
    gameTextPos.move(0, 50);
    for (auto &game : TRANSFORM_TO(Arcade, *this->_arcade)->getGames()) {
        Text gameText = Text((IColor &) RGBAColor::WHITE, game.name, "assets/PressStart2P.ttf");
        gameText.setSize(15);
        gameText.setPosition(gameTextPos);
        this->_arcade->display(gameText);
        gameTextPos.move(0, 20);
    }

    // Show drivers
    Coord2D driverTextPos = Coord2D(250, 150);
    Text driverTitle = Text((IColor &) RGBAColor::WHITE, "Drivers", "assets/PressStart2P.ttf");
    driverTitle.setSize(30);
    driverTitle.setPosition(driverTextPos);
    this->_arcade->display(driverTitle);
    driverTextPos.move(0, 50);
    for (auto &driver : TRANSFORM_TO(Arcade, *this->_arcade)->getDrivers()) {
        Text driverText = Text((IColor &) RGBAColor::WHITE, driver.name, "assets/PressStart2P.ttf");
        driverText.setSize(15);
        driverText.setPosition(driverTextPos);
        this->_arcade->display(driverText);
        driverTextPos.move(0, 20);
    }

    // Show scores
    Coord2D scoreTextPos = Coord2D(700, 150);
    Text scoreTitle = Text((IColor &) RGBAColor::WHITE, "Scores", "assets/PressStart2P.ttf");
    scoreTitle.setSize(30);
    scoreTitle.setPosition(scoreTextPos);
    this->_arcade->display(scoreTitle);
    scoreTextPos.move(0, 50);
    for (auto players : TRANSFORM_TO(Arcade, *this->_arcade)->getPlayers()) {
        Text scoreText = Text((IColor &) RGBAColor::WHITE, players->getName() + ": " + std::to_string(players->getTotalScore()), "assets/PressStart2P.ttf");
        scoreText.setSize(15);
        scoreText.setPosition(scoreTextPos);
        this->_arcade->display(scoreText);
        scoreTextPos.move(0, 20);
    }

    // Show username input
    std::string username = _tempUsername;
    Coord2D usernameTextPos = Coord2D(50, 400);
    Text usernameTitle = Text((IColor &) RGBAColor::WHITE, "YOUR NAME", "assets/PressStart2P.ttf");
    usernameTitle.setSize(15);
    usernameTitle.setPosition(usernameTextPos);
    this->_arcade->display(usernameTitle);
    usernameTextPos.move(0, 30);
    Text usernameText = Text((IColor &) RGBAColor::WHITE, username, "assets/PressStart2P.ttf");
    usernameText.setSize(30);
    usernameText.setPosition(usernameTextPos);
    this->_arcade->display(usernameText);

    Coord2D pressPlayPos = Coord2D(50 - (int) frame * 5, 520);
    Text pressPlay = Text((IColor &) RGBAColor::WHITE, "Press F4 to play", "assets/PressStart2P.ttf");
    pressPlay.setSize(15);
    for (std::size_t i = 0; i < 5; i++) {
        pressPlay.setPosition(pressPlayPos);
        if (frame < 55/3)
            continue;
        this->_arcade->display(pressPlay);
        pressPlayPos.move(270, 0);
    }

    this->_arcade->flipFrame();
    frame++;
    if (frame >= 55)
        frame = 0;
}

void Menu::typeUsername(const IEvent &event) {
    static const std::unordered_map<EventKey, char> keyMap = {
        {_KEY_A, 'a'}, {_KEY_B, 'b'}, {_KEY_C, 'c'}, {_KEY_D, 'd'}, {_KEY_E, 'e'}, {_KEY_F, 'f'}, {_KEY_G, 'g'}, {_KEY_H, 'h'},
        {_KEY_I, 'i'}, {_KEY_J, 'j'}, {_KEY_K, 'k'}, {_KEY_L, 'l'}, {_KEY_M, 'm'}, {_KEY_N, 'n'}, {_KEY_O, 'o'}, {_KEY_P, 'p'},
        {_KEY_Q, 'q'}, {_KEY_R, 'r'}, {_KEY_S, 's'}, {_KEY_T, 't'}, {_KEY_U, 'u'}, {_KEY_V, 'v'}, {_KEY_W, 'w'}, {_KEY_X, 'x'},
        {_KEY_Y, 'y'}, {_KEY_Z, 'z'}, {_KEY_DIGIT_0, '0'}, {_KEY_DIGIT_1, '1'}, {_KEY_DIGIT_2, '2'}, {_KEY_DIGIT_3, '3'},
        {_KEY_DIGIT_4, '4'}, {_KEY_DIGIT_5, '5'}, {_KEY_DIGIT_6, '6'}, {_KEY_DIGIT_7, '7'}, {_KEY_DIGIT_8, '8'}, {_KEY_DIGIT_9, '9'}
    };

    if (event.getKey() == _KEY_BACKSPACE) {
        if (!_tempUsername.empty())
            _tempUsername.pop_back();
    } else if (event.getKey() == _KEY_ENTER) {
        TRANSFORM_TO(Arcade, *this->_arcade)->updateCurrentPlayerName(_tempUsername);
    } else {
        if (_tempUsername.size() < 10)
            _tempUsername += keyMap.at(event.getKey());
    }
}

void Menu::handleClicked(const IEvent &event) {
    Coord2D mousePos = event.getPosition();

    Coord2D gameTextPos = Coord2D(50, 150);
    gameTextPos.move(0, 50);
    for (auto &game : TRANSFORM_TO(Arcade, *this->_arcade)->getGames()) {
        std::size_t width = game.name.size() * 15;
        std::size_t height = 15;

        if (mousePos.getX() >= gameTextPos.getX() && (std::size_t) mousePos.getX() <= (std::size_t) gameTextPos.getX() + width &&
            mousePos.getY() >= gameTextPos.getY() && (std::size_t) mousePos.getY() <= (std::size_t) gameTextPos.getY() + height) {
            TRANSFORM_TO(Arcade, *this->_arcade)->loadGame(game.name);
        }
        gameTextPos.move(0, 20);
    }

    Coord2D driverTextPos = Coord2D(250, 150);
    driverTextPos.move(0, 50);
    for (auto &driver : TRANSFORM_TO(Arcade, *this->_arcade)->getDrivers()) {
        std::size_t width = driver.name.size() * 15;
        std::size_t height = 15;

        if (mousePos.getX() >= driverTextPos.getX() && (std::size_t) mousePos.getX() <= (std::size_t) driverTextPos.getX() + width &&
            mousePos.getY() >= driverTextPos.getY() && (std::size_t) mousePos.getY() <= (std::size_t) driverTextPos.getY() + height) {
            TRANSFORM_TO(Arcade, *this->_arcade)->loadDriver(driver.name);
        }
        driverTextPos.move(0, 20);
    }
}

void Menu::start() {
    this->_arcade->setPreferredSize(979, 551);
    for (EventKey key = _KEY_A; key <= _KEY_DIGIT_0; key++) {
        this->_arcade->bindEvent(IEvent::_KEY_DOWN, key, [this](const IEvent &event) { this->typeUsername(event); });
    }
    this->_arcade->bindEvent(IEvent::_KEY_DOWN, _KEY_BACKSPACE, [this](const IEvent &event) { this->typeUsername(event); });
    this->_arcade->bindEvent(IEvent::_KEY_DOWN, _KEY_ENTER, [this](const IEvent &event) { this->typeUsername(event); });
    this->_arcade->bindEvent(IEvent::_MOUSE_DOWN, _MOUSE_LEFT_CLICK, [this](const IEvent &event) { this->handleClicked(event); });
}
