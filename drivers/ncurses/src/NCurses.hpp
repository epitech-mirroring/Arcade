/*
** EPITECH PROJECT, 2024
** Arcade
** File description:
** No file there , just an epitech header example .
** You can even have multiple lines if you want !
*/

#pragma once
#include <ncurses.h>
#include "shared/IDriver.hpp"
#include "shared/IDriver.hpp"
#include "shared/displayable/primitives/IPrimitive.hpp"
#include "shared/displayable/primitives/IText.hpp"
#include "shared/displayable/primitives/ICircle.hpp"
#include "shared/displayable/primitives/ISquare.hpp"
#include "shared/displayable/primitives/ILine.hpp"
#include "shared/displayable/entities/IEntity.hpp"
#include "shared/utils/ICanRotate.hpp"
#include "common/displayable/ADisplayable.hpp"
#include "common/events/Event.hpp"
#include "common/utils/RGBAColor.hpp"
#include "NCursesException.hpp"
#include <map>
#include <deque>
#include <cstddef>
#include <memory>
#include <iostream>
#ifdef _KEY_T
#undef _KEY_T
#endif

#define SCALE_WIDTH 8
#define SCALE_HEIGHT 18

struct BufferedChar {
    char c;
    int color;
};
class NCurses: public IDriver {
public:
    NCurses();
    ~NCurses() override;
    void display(const IDisplayable &displayable) override;
    void flipFrame() override;
    void bindEvent(IEvent::EventType type, EventKey key, EventCallback callback) override;
    void setPreferredSize(std::size_t width, std::size_t height) override;
    void unbindAll() override;

private:
    void handleEvents();
    void handleInput(int event);
    void displayText(const IText &text);
    void displaySquare(const ISquare &square);
    void displayLine(const ILine &line);
    void displayCircle(const ICircle &circle);
    void displayEntity(const IEntity &entity);
    void displayPrimitive(const IPrimitive &primitive);

    std::map<std::pair<IEvent::EventType, EventKey>, EventCallback> _events;
    std::map<int, EventKey> _keyMap;
    std::size_t _width;
    std::size_t _height;
    std::unordered_map<std::size_t, std::unordered_map<std::size_t, BufferedChar>> _frameBuffer;
};
