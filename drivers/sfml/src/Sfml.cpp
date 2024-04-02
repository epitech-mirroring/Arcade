/*
** EPITECH PROJECT, 2024
** Arcade
** File description:
** No file there , just an epitech header example .
** You can even have multiple lines if you want !
*/

#include "Sfml.hpp"
#include <memory>
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
    this->_width = 800;
    this->_height = 600;
    this->_window.create(sf::VideoMode(800, 600), "Arcade", sf::Style::Close | sf::Style::Titlebar);
    this->_window.setFramerateLimit(60);
    this->_window.clear();
    this->_window.setView(sf::View(sf::FloatRect(0, 0, 800, 600)));
    this->_keyMap = {
        {sf::Keyboard::Key::A, _KEY_A},
        {sf::Keyboard::Key::B, _KEY_B},
        {sf::Keyboard::Key::C, _KEY_C},
        {sf::Keyboard::Key::D, _KEY_D},
        {sf::Keyboard::Key::E, _KEY_E},
        {sf::Keyboard::Key::F, _KEY_F},
        {sf::Keyboard::Key::G, _KEY_G},
        {sf::Keyboard::Key::H, _KEY_H},
        {sf::Keyboard::Key::I, _KEY_I},
        {sf::Keyboard::Key::J, _KEY_J},
        {sf::Keyboard::Key::K, _KEY_K},
        {sf::Keyboard::Key::L, _KEY_L},
        {sf::Keyboard::Key::M, _KEY_M},
        {sf::Keyboard::Key::N, _KEY_N},
        {sf::Keyboard::Key::O, _KEY_O},
        {sf::Keyboard::Key::P, _KEY_P},
        {sf::Keyboard::Key::Q, _KEY_Q},
        {sf::Keyboard::Key::R, _KEY_R},
        {sf::Keyboard::Key::S, _KEY_S},
        {sf::Keyboard::Key::T, _KEY_T},
        {sf::Keyboard::Key::U, _KEY_U},
        {sf::Keyboard::Key::V, _KEY_V},
        {sf::Keyboard::Key::W, _KEY_W},
        {sf::Keyboard::Key::X, _KEY_X},
        {sf::Keyboard::Key::Y, _KEY_Y},
        {sf::Keyboard::Key::Z, _KEY_Z},
        {sf::Keyboard::Key::Num0, _KEY_DIGIT_0},
        {sf::Keyboard::Key::Numpad0, _KEY_DIGIT_0},
        {sf::Keyboard::Key::Num1, _KEY_DIGIT_1},
        {sf::Keyboard::Key::Numpad1, _KEY_DIGIT_1},
        {sf::Keyboard::Key::Num2, _KEY_DIGIT_2},
        {sf::Keyboard::Key::Numpad2, _KEY_DIGIT_2},
        {sf::Keyboard::Key::Num3, _KEY_DIGIT_3},
        {sf::Keyboard::Key::Numpad3, _KEY_DIGIT_3},
        {sf::Keyboard::Key::Num4, _KEY_DIGIT_4},
        {sf::Keyboard::Key::Numpad4, _KEY_DIGIT_4},
        {sf::Keyboard::Key::Num5, _KEY_DIGIT_5},
        {sf::Keyboard::Key::Numpad5, _KEY_DIGIT_5},
        {sf::Keyboard::Key::Num6, _KEY_DIGIT_6},
        {sf::Keyboard::Key::Numpad6, _KEY_DIGIT_6},
        {sf::Keyboard::Key::Num7, _KEY_DIGIT_7},
        {sf::Keyboard::Key::Numpad7, _KEY_DIGIT_7},
        {sf::Keyboard::Key::Num8, _KEY_DIGIT_8},
        {sf::Keyboard::Key::Numpad8, _KEY_DIGIT_8},
        {sf::Keyboard::Key::Num9, _KEY_DIGIT_9},
        {sf::Keyboard::Key::Numpad9, _KEY_DIGIT_9},
        {sf::Keyboard::Key::Escape, _KEY_ESCAPE},
        {sf::Keyboard::Key::LControl, _KEY_CTRL},
        {sf::Keyboard::Key::RControl, _KEY_CTRL},
        {sf::Keyboard::Key::LShift, _KEY_SHIFT},
        {sf::Keyboard::Key::RShift, _KEY_SHIFT},
        {sf::Keyboard::Key::Tab, _KEY_TAB},
        {sf::Keyboard::Key::Space, _KEY_SPACE},
        {sf::Keyboard::Key::Return, _KEY_ENTER},
        {sf::Keyboard::Key::BackSpace, _KEY_BACKSPACE},
        {sf::Keyboard::Key::Up, _KEY_UP},
        {sf::Keyboard::Key::Down, _KEY_DOWN},
        {sf::Keyboard::Key::Left, _KEY_LEFT},
        {sf::Keyboard::Key::Right, _KEY_RIGHT},
        {sf::Keyboard::Key::F1, _KEY_F1},
        {sf::Keyboard::Key::F2, _KEY_F2},
        {sf::Keyboard::Key::F3, _KEY_F3},
        {sf::Keyboard::Key::F4, _KEY_F4},
        {sf::Keyboard::Key::F5, _KEY_F5},
        {sf::Keyboard::Key::F6, _KEY_F6},
        {sf::Keyboard::Key::F7, _KEY_F7},
        {sf::Keyboard::Key::F8, _KEY_F8},
        {sf::Keyboard::Key::F9, _KEY_F9},
        {sf::Keyboard::Key::F10, _KEY_F10},
        {sf::Keyboard::Key::F11, _KEY_F11},
        {sf::Keyboard::Key::F12, _KEY_F12}
    };
}

SFML::~SFML()
{
    this->_window.close();
}

void SFML::flipFrame()
{
    this->_window.display();
    this->_window.clear();
    if (this->_window.pollEvent(this->_event)) {
        this->handleEvents();
    }
}

void SFML::setPreferredSize(std::size_t width, std::size_t height)
{
    this->_width = width;
    this->_height = height;
    this->_window.setSize(sf::Vector2u(width, height));
    this->_window.setView(sf::View(sf::FloatRect(0, 0, width, height)));
}

void SFML::bindEvent(IEvent::EventType type, EventKey key, EventCallback callback)
{
    this->_events[std::make_pair(type, key)] = callback;
}

void SFML::handleEvents()
{
    if (this->_event.type == sf::Event::Closed) {
        EventCallback callback = this->_events[std::make_pair(IEvent::EventType::_KEY_DOWN, _KEY_ESCAPE)];
        if (callback) {
            callback(Event(IEvent::EventType::_KEY_DOWN, _KEY_ESCAPE));
        }
    }
    if (this->_event.type == sf::Event::KeyPressed) {
        this->handleKeyDownEvents(this->_event);
    }
    this->handleKeyPressedEvents();
    if (this->_event.type == sf::Event::KeyReleased) {
        this->handleKeyUpEvents(this->_event);
    }
}

void SFML::handleKeyDownEvents(sf::Event event)
{
    EventCallback callback = this->_events[std::make_pair(IEvent::EventType::_KEY_DOWN, this->_keyMap[event.key.code])];
    if (callback) {
        callback(Event(IEvent::EventType::_KEY_DOWN, this->_keyMap[event.key.code]));
    }
    this->_pressedKeys.push_back(event.key.code);
}

void SFML::handleKeyUpEvents(sf::Event event)
{
    EventCallback callback = this->_events[std::make_pair(IEvent::EventType::_KEY_UP, this->_keyMap[event.key.code])];
    if (callback) {
        callback(Event(IEvent::EventType::_KEY_UP, this->_keyMap[event.key.code]));
    }
    this->_pressedKeys.erase(std::remove(this->_pressedKeys.begin(), this->_pressedKeys.end(), event.key.code), this->_pressedKeys.end());
}

void SFML::handleKeyPressedEvents()
{
    for (sf::Keyboard::Key key : this->_pressedKeys) {
        EventCallback callback = this->_events[std::make_pair(IEvent::EventType::_KEY_PRESS, this->_keyMap[key])];
        if (callback) {
            callback(Event(IEvent::EventType::_KEY_PRESS, this->_keyMap[key]));
        }
    }
}

void SFML::display(const IDisplayable &displayable)
{
    if (IS_INSTANCE_OF(const IPrimitive, displayable)) {
        displayPrimitive(dynamic_cast<const IPrimitive &>(displayable));
    } else if (IS_INSTANCE_OF(const IEntity, displayable)) {
        displayEntity(dynamic_cast<const IEntity &>(displayable));
    }
}

void SFML::displayPrimitive(const IPrimitive &primitive)
{
    if (IS_INSTANCE_OF(const IText, primitive)) {
        displayText(dynamic_cast<const IText &>(primitive));
    } else if (IS_INSTANCE_OF(const ISquare, primitive)) {
        displaySquare(dynamic_cast<const ISquare &>(primitive));
    } else if (IS_INSTANCE_OF(const ICircle, primitive)) {
        displayCircle(dynamic_cast<const ICircle &>(primitive));
    }
}

void SFML::displayText(const IText &text)
{
    static sf::Font font;
    sf::Text sfText;
    sf::Color color = sf::Color(text.getColor().getR(), text.getColor().getG(), text.getColor().getB(), text.getColor().getA());

    if (this->_loadedFonts.find(text.getFontPath()) == this->_loadedFonts.end()) {
        font.loadFromFile(text.getFontPath());
        this->_loadedFonts[text.getFontPath()] = font;
    } else {
        font = this->_loadedFonts[text.getFontPath()];
    }
    sfText.setFont(font);
    sfText.setString(text.getText());
    sfText.setFillColor(color);
    sfText.setOutlineColor(color);
    sfText.setCharacterSize(text.getSize());
    sfText.setPosition(text.getPosition().getX(), text.getPosition().getY());
    if (IS_INSTANCE_OF(const ICanRotate, text)) {
        sfText.setRotation(TRANSFORM_TO(const ICanRotate, text)->getRotation());
    }
    this->_window.draw(sfText);
}

void SFML::displaySquare(const ISquare &square)
{
    sf::RectangleShape sfSquare;
    sf::Color color = sf::Color(square.getColor().getR(), square.getColor().getG(), square.getColor().getB(), square.getColor().getA());

    sfSquare.setSize(sf::Vector2f(square.getWidth() * square.getSize(), square.getHeight() * square.getSize()));
    sfSquare.setFillColor(color);
    sfSquare.setPosition(square.getPosition().getX(), square.getPosition().getY());
    if (IS_INSTANCE_OF(const ICanRotate, square)) {
        sfSquare.setRotation(TRANSFORM_TO(const ICanRotate, square)->getRotation());
    }
    this->_window.draw(sfSquare);
}

void SFML::displayCircle(const ICircle &circle)
{
    sf::CircleShape sfCircle;
    sf::Color color = sf::Color(circle.getColor().getR(), circle.getColor().getG(), circle.getColor().getB(), circle.getColor().getA());

    sfCircle.setRadius(circle.getRadius() * circle.getSize());
    sfCircle.setFillColor(color);
    sfCircle.setPosition(circle.getPosition().getX(), circle.getPosition().getY());
    if (IS_INSTANCE_OF(const ICanRotate, circle)) {
        sfCircle.setRotation(TRANSFORM_TO(const ICanRotate, circle)->getRotation());
    }
    this->_window.draw(sfCircle);
}

void SFML::displayEntity(const IEntity &entity)
{
    sf::Sprite sprite;
    sf::Texture texture;
    DrawRect drawRect = entity.getSprite().getDrawRect();
    std::string path = entity.getSprite().getPicture().getPath();

    if (this->_loadedTextures.find(path) == this->_loadedTextures.end()) {
        texture.loadFromFile(path);
        this->_loadedTextures[path] = texture;
    } else {
        texture = this->_loadedTextures[path];
    }
    sprite.setTexture(texture, true);
    sprite.setTextureRect(sf::IntRect(drawRect.x, drawRect.y, drawRect.width, drawRect.height));
    sprite.setPosition(entity.getPosition().getX(), entity.getPosition().getY());
    sprite.setScale(entity.getSize(), entity.getSize());
    if (IS_INSTANCE_OF(const ICanRotate, entity)) {
        sprite.setRotation(TRANSFORM_TO(const ICanRotate, entity)->getRotation());
    }
    this->_window.draw(sprite);
}

void SFML::unbindAll()
{
    this->_events.clear();
}
