/*
** EPITECH PROJECT, 2024
** Arcade
** File description:
** No file there , just an epitech header example .
** You can even have multiple lines if you want !
*/

#include "common/events/Event.hpp"

Event::Event(EventType type, EventKey key)
{
    this->_type = type;
    this->_key = key;
    this->_position = nullptr;
}

Event::Event(EventType type, EventKey key, int x, int y)
{
    this->_type = type;
    this->_key = key;
    this->_position = std::make_unique<Coord2D>(x, y);
}

Event::Event(EventType type, EventKey key, const Coord2D &position)
{
    this->_type = type;
    this->_key = key;
    this->_position = std::make_unique<Coord2D>(position);
}

Event::EventType Event::getType()
{
    return this->_type;
}

EventKey Event::getKey()
{
    return this->_key;
}

const ICoordinate &Event::getPosition()
{
    return *this->_position;
}
