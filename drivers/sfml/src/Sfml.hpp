/*
** EPITECH PROJECT, 2024
** Arcade
** File description:
** No file there , just an epitech header example .
** You can even have multiple lines if you want !
*/

#pragma once
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
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include <SFML/Audio.hpp>
#include <unordered_map>
#include <map>
#include <deque>
#include <cstddef>
#ifdef _KEY_T
#undef _KEY_T
#endif

class SFML: public IDriver {
public:
    SFML();
    ~SFML() override;
    void display(const IDisplayable &displayable) override;
    void flipFrame() override;
    void bindEvent(IEvent::EventType type, EventKey key, EventCallback callback) override;
    void setPreferredSize(std::size_t width, std::size_t height) override;
    void unbindAll() override;
private:
    void handleEvents();
    void handleKeyDownEvents(sf::Event event);
    void handleKeyUpEvents(sf::Event event);
    void handleKeyPressedEvents();
    void displayText(const IText &text);
    void displaySquare(const ISquare &square);
    void displayLine(const ILine &line);
    void displayCircle(const ICircle &circle);
    void displayEntity(const IEntity &entity);
    void displayPrimitive(const IPrimitive &primitive);

    sf::RenderWindow _window;
    sf::Event _event;
    std::map<std::pair<IEvent::EventType, EventKey>, EventCallback> _events;
    std::unordered_map<sf::Keyboard::Key, EventKey> _keyMap;
    std::deque<sf::Keyboard::Key> _pressedKeys;
    std::unordered_map<std::string, sf::Texture *> _loadedTextures;
    std::unordered_map<std::string, sf::Font *> _loadedFonts;
    std::size_t _width;
    std::size_t _height;
};
