/*
** EPITECH PROJECT, 2024
** Arcade
** File description:
** No file there , just an epitech header example .
** You can even have multiple lines if you want !
*/

#pragma once
#include "../../shared/events/IEvent.hpp"
#include "../utils/Coord2D.hpp"

class Event : public IEvent {
protected:
    EventType _type;
    EventKey _key;
    std::unique_ptr<ICoordinate> _position;
public:
    Event(EventType type, EventKey key);
    Event(EventType type, EventKey key, int x, int y);
    Event(EventType type, EventKey key, Coord2D position);
    ~Event() override = default;
    EventType getType() override;
    EventKey getKey() override;
    std::unique_ptr<ICoordinate> &getPosition() override;
};
