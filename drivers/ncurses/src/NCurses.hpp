/*
** EPITECH PROJECT, 2024
** Arcade
** File description:
** No file there , just an epitech header example .
** You can even have multiple lines if you want !
*/

#pragma once
#include "shared/IDriver.hpp"
#include <unordered_map>
#include <ncurses.h>
#include <string>
#include "shared/displayable/primitives/IPrimitive.hpp"
#include "shared/displayable/primitives/IText.hpp"
#include "shared/displayable/primitives/ICircle.hpp"
#include "shared/displayable/primitives/ISquare.hpp"
#include "shared/displayable/entities/IEntity.hpp"

#define INSTANCE_OF(type, obj) (dynamic_cast<type *>(&obj) != nullptr)

struct BufferedChar {
    char c;
    int color;
};

class NCurses: public IDriver {
protected:
    std::size_t _preferredWidth;
    std::size_t _preferredHeight;
    std::unordered_map<EventKey, EventCallback> _events;
    std::unique_ptr<WINDOW, decltype(&delwin)> _window = std::unique_ptr<WINDOW, decltype(&delwin)>(nullptr, &delwin);
    std::unordered_map<std::size_t, std::unordered_map<std::size_t, BufferedChar>> _frameBuffer;
public:
    NCurses();
    ~NCurses() override = default;

    void display(const IDisplayable &displayable) override;
    void flipFrame() override;
    void bindEvent(IEvent::EventType type, EventKey key, EventCallback callback) override;
    void setPreferredSize(std::size_t width, std::size_t height) override;

    void displayText(const IText &text);
    void displaySquare(const ISquare &square);
    void displayCircle(const ICircle &circle);
    void displayEntity(const IEntity &entity);
    void displayPrimitive(const IPrimitive &primitive);
};
