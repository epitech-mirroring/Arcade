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
    /**
     * @brief Construct a new Event object
     * @param type The type of the event
     * @param key The key of the event
     * @note The position is set to (0, 0)
     */
    Event(EventType type, EventKey key);
    /**
     * @brief Construct a new Event object (used for mouse events)
     * @param type The type of the event
     * @param key The key of the event
     * @param x The x position of the event
     * @param y The y position of the event
     */
    Event(EventType type, EventKey key, int x, int y);
    /**
     * @brief Construct a new Event object (used for mouse events)
     * @param type The type of the event
     * @param key The key of the event
     * @param position The position of the event
     */
    Event(EventType type, EventKey key, const Coord2D &position);
    /**
     * @brief Destroy the Event object
     */
    ~Event() override = default;
    /**
     * @brief Get the type of the event
     * @return The type of the event
     */
    [[nodiscard]] EventType getType() const override;
    /**
     * @brief Get the key of the event
     * @return The key of the event
     */
    [[nodiscard]] EventKey getKey() const override;
    /**
     * @brief Get the position of the event
     * @return The position of the event
     */
    [[nodiscard]] const ICoordinate &getPosition() const override;
};
