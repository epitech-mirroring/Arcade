/*
** EPITECH PROJECT, 2024
** Arcade
** File description:
** No file there , just an epitech header example .
** You can even have multiple lines if you want !
*/

#include "core/menu/Menu.hpp"
#include "common/displayable/primitives/Square.hpp"
#include "common/displayable/primitives/Circle.hpp"
#include "common/displayable/primitives/Text.hpp"
#include "common/utils/RGBAColor.hpp"
#include "core/Arcade.hpp"

Menu::Menu() = default;

void Menu::run() {
    static Square background = Square((IColor &) RGBAColor::BLACK, 800, 600);
    this->_arcade->display(background);

    static Text title = Text((IColor &) RGBAColor::WHITE, "Arcade");
    static Coord2D titlePos = Coord2D(400, 300);
    title.setSize(30);
    title.setPosition(titlePos);
    this->_arcade->display(title);

    // Show games
    Coord2D gameTextPos = Coord2D(200, 100);
    for (auto &game : TRANSFORM_TO(Arcade, *this->_arcade)->getGames()) {
        Text gameText = Text((IColor &) RGBAColor::WHITE, game.name);
        gameText.setSize(30);
        gameText.setPosition(gameTextPos);
        this->_arcade->display(gameText);
        gameTextPos.move(0, 50);
    }

    // Show drivers
    Coord2D driverTextPos = Coord2D(600, 100);
    for (auto &lib : TRANSFORM_TO(Arcade, *this->_arcade)->getDrivers()) {
        Text driverText = Text((IColor &) RGBAColor::WHITE, lib.name);
        driverText.setSize(30);
        driverText.setPosition(driverTextPos);
        this->_arcade->display(driverText);
        driverTextPos.move(0, 50);
    }

    std::string user = TRANSFORM_TO(Arcade, *this->_arcade)->getCurrentPlayer().getName();
    Text username = Text((IColor &) RGBAColor::WHITE, "Username: " + user);
    username.setSize(30);
    username.setPosition(Coord2D(400, 500));
    this->_arcade->display(username);

    this->_arcade->flipFrame();
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
    this->_arcade->setPreferredSize(800, 600);
    for (EventKey key = KEY_A; key <= KEY_DIGIT_0; key++) {
        this->_arcade->bindEvent(IEvent::KEY_DOWN, key, [this](const IEvent &event) { this->typeUsername(event); });
    }
    this->_arcade->bindEvent(IEvent::KEY_DOWN, KEY_BACKSPACE, [this](const IEvent &event) { this->typeUsername(event); });
}
