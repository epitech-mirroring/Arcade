/*
** EPITECH PROJECT, 2024
** Arcade
** File description:
** No file there , just an epitech header example .
** You can even have multiple lines if you want !
*/

#include "Sfml.hpp"
#include <iostream>

extern "C" {
    __attribute__((constructor))
    void load_lib()
    {
        std::cout << "Loading SFML driver" << std::endl;
    }

    __attribute__((destructor))
    void unload_lib()
    {
        std::cout << "Unloading SFML driver" << std::endl;
    }

    std::unique_ptr<IDriver> create_driver()
    {
        std::unique_ptr<IDriver> driver = std::make_unique<SFML>();
        return driver;
    }

    const std::string &get_name()
    {
        static const std::string driver_name = "SFML";
        return driver_name;
    }
}

SFML::SFML()
{
    this->_window.create(sf::VideoMode(800, 600), "Arcade");
    this->_window.setFramerateLimit(60);
    this->_window.clear();
}

SFML::~SFML()
{
    this->_window.close();
}

void SFML::display(std::shared_ptr<IDisplayable> displayable)
{
    sf::RectangleShape shape(sf::Vector2f(displayable->getSize(), displayable->getSize()));

    shape.setPosition(displayable->getPosition()->getX(), displayable->getPosition()->getY());
    shape.setFillColor(sf::Color::Red);
    this->_window.draw(shape);
}

void SFML::flipFrame()
{
    this->_window.display();
    this->_window.clear();
}

void SFML::bindEvent(IEvent::EventType type, EventKey key, EventCallback callback)
{
    (void) type;
    this->_events[key] = callback;
}
