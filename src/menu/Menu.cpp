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

Menu::Menu() = default;

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
    Coord2D scoreTextPos = Coord2D(770, 150);
    Text scoreTitle = Text((IColor &) RGBAColor::WHITE, "Scores", "assets/PressStart2P.ttf");
    scoreTitle.setSize(30);
    scoreTitle.setPosition(scoreTextPos);
    this->_arcade->display(scoreTitle);
    scoreTextPos.move(0, 50);
    for (auto &players : TRANSFORM_TO(Arcade, *this->_arcade)->getPlayers()) {
        Text scoreText = Text((IColor &) RGBAColor::WHITE, players.getName() + ": " + std::to_string(players.getScore()), "assets/PressStart2P.ttf");
        scoreText.setSize(15);
        scoreText.setPosition(scoreTextPos);
        this->_arcade->display(scoreText);
        scoreTextPos.move(0, 20);
    }

    // Show username input
    std::string username = TRANSFORM_TO(Arcade, *this->_arcade)->getCurrentPlayer().getName();
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

#include <unordered_map>

void Menu::typeUsername(const IEvent &event) const {
    static const std::unordered_map<EventKey, char> keyMap = {
        {KEY_A, 'a'}, {KEY_B, 'b'}, {KEY_C, 'c'}, {KEY_D, 'd'}, {KEY_E, 'e'}, {KEY_F, 'f'}, {KEY_G, 'g'}, {KEY_H, 'h'},
        {KEY_I, 'i'}, {KEY_J, 'j'}, {KEY_K, 'k'}, {KEY_L, 'l'}, {KEY_M, 'm'}, {KEY_N, 'n'}, {KEY_O, 'o'}, {KEY_P, 'p'},
        {KEY_Q, 'q'}, {KEY_R, 'r'}, {KEY_S, 's'}, {KEY_T, 't'}, {KEY_U, 'u'}, {KEY_V, 'v'}, {KEY_W, 'w'}, {KEY_X, 'x'},
        {KEY_Y, 'y'}, {KEY_Z, 'z'}, {KEY_DIGIT_0, '0'}, {KEY_DIGIT_1, '1'}, {KEY_DIGIT_2, '2'}, {KEY_DIGIT_3, '3'},
        {KEY_DIGIT_4, '4'}, {KEY_DIGIT_5, '5'}, {KEY_DIGIT_6, '6'}, {KEY_DIGIT_7, '7'}, {KEY_DIGIT_8, '8'}, {KEY_DIGIT_9, '9'}
    };

    if (event.getKey() == KEY_BACKSPACE) {
        std::string user = TRANSFORM_TO(Arcade, *this->_arcade)->getCurrentPlayer().getName();
        if (!user.empty())
            user.pop_back();
        TRANSFORM_TO(Arcade, *this->_arcade)->getCurrentPlayer().setName(user);
    } else {
        std::string user = TRANSFORM_TO(Arcade, *this->_arcade)->getCurrentPlayer().getName();
        if (user.size() < 10)
            user += keyMap.at(event.getKey());
        TRANSFORM_TO(Arcade, *this->_arcade)->getCurrentPlayer().setName(user);
    }
}

void Menu::start() {
    this->_arcade->setPreferredSize(979, 551);
    for (EventKey key = KEY_A; key <= KEY_DIGIT_0; key++) {
        this->_arcade->bindEvent(IEvent::KEY_DOWN, key, [this](const IEvent &event) { this->typeUsername(event); });
    }
    this->_arcade->bindEvent(IEvent::KEY_DOWN, KEY_BACKSPACE, [this](const IEvent &event) { this->typeUsername(event); });
}
