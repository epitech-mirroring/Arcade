/*
** EPITECH PROJECT, 2024
** Arcade
** File description:
** No file there , just an epitech header example .
** You can even have multiple lines if you want !
*/

#pragma once
#include "shared/IDriver.hpp"
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include <SFML/Audio.hpp>

class SFML: public IDriver {
public:
    SFML();
    ~SFML() override;
    void display(std::shared_ptr<IDisplayable> displayable) override;
    void flipFrame() override;
    void bindEvent(IEvent::EventType type, EventKey key, EventCallback callback) override;

private:
    sf::RenderWindow _window;
    std::map<EventKey, EventCallback> _events;

};
