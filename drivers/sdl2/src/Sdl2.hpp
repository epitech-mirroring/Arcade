/*
** EPITECH PROJECT, 2024
** Arcade
** File description:
** No file there , just an epitech header example .
** You can even have multiple lines if you want !
*/

#pragma once
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include "shared/IDriver.hpp"
#include "shared/displayable/primitives/IPrimitive.hpp"
#include "shared/displayable/primitives/IText.hpp"
#include "shared/displayable/primitives/ICircle.hpp"
#include "shared/displayable/primitives/ISquare.hpp"
#include "shared/displayable/entities/IEntity.hpp"
#include "shared/utils/ICanRotate.hpp"
#include "common/displayable/ADisplayable.hpp"
#include "common/events/Event.hpp"
#include "SDL2Exception.hpp"
#include <map>
#include <deque>
#include <cstddef>
#include <memory>
#include <iostream>

class SDL2: public IDriver {
public:
    SDL2();
    ~SDL2() override;
    void display(const IDisplayable &displayable) override;
    void flipFrame() override;
    void bindEvent(IEvent::EventType type, EventKey key, EventCallback callback) override;
    void setPreferredSize(std::size_t width, std::size_t height) override;
    void unbindAll() override;
    SDL_Color convertColor(const IColor &color);
private:
    void handleEvents();
    void handleKeyDownEvents(SDL_Event event);
    void handleKeyUpEvents(SDL_Event event);
    void handleKeyPressedEvents();
    void displayText(const IText &text);
    void displaySquare(const ISquare &square);
    void displayCircle(const ICircle &circle);
    void displayEntity(const IEntity &entity);
    void displayPrimitive(const IPrimitive &primitive);

    std::unique_ptr<SDL_Window, decltype(&SDL_DestroyWindow)> _window = std::unique_ptr<SDL_Window, decltype(&SDL_DestroyWindow)>(nullptr, SDL_DestroyWindow);
    std::unique_ptr<SDL_Renderer, decltype(&SDL_DestroyRenderer)> _renderer = std::unique_ptr<SDL_Renderer, decltype(&SDL_DestroyRenderer)>(nullptr, SDL_DestroyRenderer);
    SDL_Event _event;
    std::map<std::pair<IEvent::EventType, EventKey>, EventCallback> _events;
    std::map<SDL_Keycode, EventKey> _keyMap;
    std::deque<SDL_Keycode> _pressedKeys;
    std::map<std::string, SDL_Surface *> _images;
    std::map<std::pair<std::string, std::size_t>, TTF_Font *> _fonts;
    std::size_t _width;
    std::size_t _height;
};
