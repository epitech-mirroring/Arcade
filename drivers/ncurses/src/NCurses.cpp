/*
** EPITECH PROJECT, 2024
** Arcade
** File description:
** No file there , just an epitech header example .
** You can even have multiple lines if you want !
*/

#include "NCurses.hpp"
#include <memory>
#include <string>
#include <iostream>

extern "C" {
    __attribute__((constructor))
    void load_lib()
    {
        std::cout << "Loading NCurses driver" << std::endl;
    }

    __attribute__((destructor))
    void unload_lib()
    {
        std::cout << "Unloading NCurses driver" << std::endl;
    }

    std::unique_ptr<NCurses> create_driver(void)
    {
        return std::make_unique<NCurses>();
    }

    const std::string &get_name(void)
    {
        const static std::string name = "NCurses";
        return name;
    }
}

NCurses::NCurses() {
    this->_width = 500 / SCALE_WIDTH;
    this->_height = 500 / SCALE_HEIGHT;
    initscr();
    if (stdscr == nullptr)
        throw NCursesException("Failed to initialize ncurses");
    keypad(stdscr, TRUE);
    noecho();
    curs_set(0);
    nodelay(stdscr, TRUE);
    mousemask(BUTTON1_CLICKED | BUTTON2_CLICKED | BUTTON3_CLICKED, nullptr);
    start_color();
    init_pair(1, COLOR_BLACK, COLOR_BLACK);
    init_pair(2, COLOR_RED, COLOR_BLACK);
    init_pair(3, COLOR_GREEN, COLOR_BLACK);
    init_pair(4, COLOR_YELLOW, COLOR_BLACK);
    init_pair(5, COLOR_BLUE, COLOR_BLACK);
    init_pair(6, COLOR_MAGENTA, COLOR_BLACK);
    init_pair(7, COLOR_CYAN, COLOR_BLACK);
    init_pair(8, COLOR_WHITE, COLOR_BLACK);
    this->_keyMap = {
        {'a', _KEY_A},
        {'b', _KEY_B},
        {'c', _KEY_C},
        {'d', _KEY_D},
        {'e', _KEY_E},
        {'f', _KEY_F},
        {'g', _KEY_G},
        {'h', _KEY_H},
        {'i', _KEY_I},
        {'j', _KEY_J},
        {'k', _KEY_K},
        {'l', _KEY_L},
        {'m', _KEY_M},
        {'n', _KEY_N},
        {'o', _KEY_O},
        {'p', _KEY_P},
        {'q', _KEY_Q},
        {'r', _KEY_R},
        {'s', _KEY_S},
        {'t', _KEY_T},
        {'u', _KEY_U},
        {'v', _KEY_V},
        {'w', _KEY_W},
        {'x', _KEY_X},
        {'y', _KEY_Y},
        {'z', _KEY_Z},
        {'1', _KEY_DIGIT_1},
        {'&', _KEY_DIGIT_1},
        {'2', _KEY_DIGIT_2},
        {169, _KEY_DIGIT_2},
        {'3', _KEY_DIGIT_3},
        {'"', _KEY_DIGIT_3},
        {'4', _KEY_DIGIT_4},
        {'\'', _KEY_DIGIT_4},
        {'5', _KEY_DIGIT_5},
        {'(', _KEY_DIGIT_5},
        {'6', _KEY_DIGIT_6},
        {'-', _KEY_DIGIT_6},
        {'7', _KEY_DIGIT_7},
        {168, _KEY_DIGIT_7},
        {'8', _KEY_DIGIT_8},
        {'_', _KEY_DIGIT_8},
        {'9', _KEY_DIGIT_9},
        {167, _KEY_DIGIT_9},
        {'0', _KEY_DIGIT_0},
        {160, _KEY_DIGIT_0},
        {KEY_F(1), _KEY_F1},
        {KEY_F(2), _KEY_F2},
        {KEY_F(3), _KEY_F3},
        {KEY_F(4), _KEY_F4},
        {KEY_F(5), _KEY_F5},
        {KEY_F(6), _KEY_F6},
        {KEY_F(7), _KEY_F7},
        {KEY_F(8), _KEY_F8},
        {KEY_F(9), _KEY_F9},
        {KEY_F(10), _KEY_F10},
        {KEY_F(11), _KEY_F11},
        {KEY_F(12), _KEY_F12},
        {KEY_UP, _KEY_UP},
        {KEY_DOWN, _KEY_DOWN},
        {KEY_LEFT, _KEY_LEFT},
        {KEY_RIGHT, _KEY_RIGHT},
        {KEY_BACKSPACE, _KEY_BACKSPACE},
        {10, _KEY_ENTER},
        {' ', _KEY_SPACE},
        {27, _KEY_ESCAPE},
        {9, _KEY_TAB},
    };
}

NCurses::~NCurses() {
    endwin();
    this->_events.clear();
    this->_frameBuffer.clear();
}

static int getNcursesColor(const IColor &color) {
    std::size_t r = color.getR();
    std::size_t g = color.getG();
    std::size_t b = color.getB();

    if (r == 0 && g == 0 && b == 0)
        return 1;
    if (r == 255 && g == 255 && b == 255)
        return 8;
    if (r == 255 && g == 0 && b == 0)
        return 2;
    if (r == 0 && g == 255 && b == 0)
        return 3;
    if (r == 255 && g == 255 && b == 0)
        return 4;
    if (r == 0 && g == 0 && b == 255)
        return 5;
    if (r == 255 && g == 0 && b == 255)
        return 6;
    if (r == 0 && g == 255 && b == 255)
        return 7;
    return 8;
}

void NCurses::display(const IDisplayable &displayable) {
    if (IS_INSTANCE_OF(const IPrimitive, displayable)) {
        displayPrimitive(dynamic_cast<const IPrimitive &>(displayable));
    } else if (IS_INSTANCE_OF(const IEntity, displayable)) {
        displayEntity(dynamic_cast<const IEntity &>(displayable));
    }
}

void NCurses::displayPrimitive(const IPrimitive &primitive) {
    if (IS_INSTANCE_OF(const IText, primitive)) {
        displayText(dynamic_cast<const IText &>(primitive));
    } else if (IS_INSTANCE_OF(const ICircle, primitive)) {
        displayCircle(dynamic_cast<const ICircle &>(primitive));
    } else if (IS_INSTANCE_OF(const ISquare, primitive)) {
        displaySquare(dynamic_cast<const ISquare &>(primitive));
    } else if (IS_INSTANCE_OF(const ILine, primitive)) {
        displayLine(dynamic_cast<const ILine &>(primitive));
    }
}

void NCurses::displayText(const IText &text) {
    int color = getNcursesColor(text.getColor());
    std::size_t x = text.getPosition().getX() / SCALE_WIDTH;
    std::size_t y = text.getPosition().getY() / SCALE_HEIGHT;

    for (std::size_t i = 0; i < text.getText().size(); i++) {
        this->_frameBuffer[x + i][y] = BufferedChar{text.getText()[i], color};
    }
}

void NCurses::displayCircle(const ICircle &circle) {
    std::size_t radius = circle.getRadius() / SCALE_WIDTH;
    std::size_t centerX = circle.getPosition().getX() / SCALE_WIDTH + radius;
    std::size_t centerY = circle.getPosition().getY() / SCALE_HEIGHT + radius;
    std::size_t startX = circle.getPosition().getX() / SCALE_WIDTH;
    std::size_t startY = circle.getPosition().getY() / SCALE_HEIGHT;
    std::size_t endX = circle.getPosition().getX() / SCALE_WIDTH + radius * 2;
    std::size_t endY = circle.getPosition().getY() / SCALE_HEIGHT + radius * 2;
    int color = getNcursesColor(circle.getColor());

    for (std::size_t y = startY; y < endY; y++) {
        for (std::size_t x = startX; x < endX; x++) {
            auto d = (std::size_t) round(sqrt(pow(x - centerX, 2) + pow(y - centerY, 2)));
            if (d <= radius) {
                this->_frameBuffer[x][y] = BufferedChar{circle.getReplacingChar(), color};
            }
        }
    }
}

void NCurses::displaySquare(const ISquare &square) {
    int color = getNcursesColor(square.getColor());
    std::size_t startX = square.getPosition().getX() / SCALE_WIDTH;
    std::size_t startY = square.getPosition().getY() / SCALE_HEIGHT;
    std::size_t endX = square.getPosition().getX() / SCALE_WIDTH + square.getWidth() * square.getSize() / SCALE_WIDTH;
    std::size_t endY = square.getPosition().getY() / SCALE_HEIGHT + square.getHeight() * square.getSize() / SCALE_HEIGHT;

    for (std::size_t y = startY; y < endY; y++) {
        for (std::size_t x = startX; x < endX; x++) {
            if (x == startX || y == startY || y == endY - 1 || x == endX - 1 || square.isFilled()) {
                this->_frameBuffer[x][y] = BufferedChar{square.getReplacingChar(), color};
            }
        }
    }
}

static bool isPointInLine(const ILine &line, std::size_t x, std::size_t y) {
    std::size_t startX = line.getPosition().getX() / SCALE_WIDTH;
    std::size_t startY = line.getPosition().getY() / SCALE_HEIGHT;
    std::size_t endX = line.getEnd().getX() / SCALE_WIDTH;
    std::size_t endY = line.getEnd().getY() / SCALE_HEIGHT;
    double d = sqrt(pow(endX - startX, 2) + pow(endY - startY, 2));
    double flexibility = 0.05;
    double d_min = d - flexibility;
    double d_max = d + flexibility;
    double r = sqrt(pow(x - startX, 2) + pow(y - startY, 2)) + sqrt(pow(x - endX, 2) + pow(y - endY, 2));
    return r >= d_min && r <= d_max;
}

void NCurses::displayLine(const ILine &line) {
    int color = getNcursesColor(line.getColor());
    std::size_t startX = line.getPosition().getX() / SCALE_WIDTH;
    std::size_t startY = line.getPosition().getY() / SCALE_HEIGHT;
    std::size_t endX = line.getEnd().getX() / SCALE_WIDTH;
    std::size_t endY = line.getEnd().getY() / SCALE_HEIGHT;

    for (std::size_t y = startY; y <= endY; y++) {
        for (std::size_t x = startX; x <= endX; x++) {
            if (isPointInLine(line, x, y))
                this->_frameBuffer[x][y] = BufferedChar{line.getReplacingChar(), color};
        }
    }
}

void NCurses::displayEntity(const IEntity &entity) {
    if (entity.getReplacingChar() == ' ' || entity.getSize() == 0)
        return;
    int color = getNcursesColor(entity.getColor());
    std::size_t posX = entity.getPosition().getX() / SCALE_WIDTH;
    std::size_t posY = entity.getPosition().getY() / SCALE_HEIGHT;
    std::size_t width = (entity.getSprite().getDrawRect().width * entity.getSize()) / SCALE_WIDTH;
    std::size_t height = (entity.getSprite().getDrawRect().height  * entity.getSize()) / SCALE_HEIGHT;
    if (width == 0)
        width = 1;
    if (height == 0)
        height = 1;

    for (std::size_t y = 0; y < height; y++) {
        for (std::size_t x = 0; x < width; x++) {
            this->_frameBuffer[posX + x][posY + y] = BufferedChar{entity.getReplacingChar(), color};
        }
    }
}

void NCurses::flipFrame() {
    if (stdscr == nullptr)
        throw NCursesException("Window is null");
    std::size_t width = getmaxx(stdscr);
    std::size_t height = getmaxy(stdscr);

    for (std::size_t x = 0; x < width; x++) {
        for (std::size_t y = 0; y < height; y++) {
            mvaddch(y, x, ' ');
        }
    }
    if (width < this->_width || height < this->_height) {
        mvwprintw(stdscr, 0, 0, "Window is too small");
        wrefresh(stdscr);
        this->_frameBuffer.clear();
        this->handleEvents();
        return;
    }

    for (std::size_t x = 0; x < this->_width - 2; x++) {
        for (std::size_t y = 0; y < this->_height - 2; y++) {
            if (this->_frameBuffer.find(x) != this->_frameBuffer.end() &&
                this->_frameBuffer[x].find(y) != this->_frameBuffer[x].end()) {
                wattron(stdscr, COLOR_PAIR(this->_frameBuffer[x][y].color));
                mvwaddch(stdscr, y + 1, x + 1, this->_frameBuffer[x][y].c);
                wattroff(stdscr, COLOR_PAIR(this->_frameBuffer[x][y].color));
            } else {
                mvwaddch(stdscr, y + 1, x + 1, ' ');
            }
        }
    }
    mvhline(0, 0, 0, this->_width);
    mvhline(this->_height - 1, 0, 0, this->_width);
    mvvline(0, 0, 0, this->_height);
    mvvline(0, this->_width - 1, 0, this->_height);
    wrefresh(stdscr);
    this->_frameBuffer.clear();
    this->handleEvents();
}

void NCurses::bindEvent(IEvent::EventType type, EventKey key, EventCallback callback) {
    this->_events[std::make_pair(type, key)] = callback;
}

void NCurses::unbindAll() {
    this->_events.clear();
}

void NCurses::setPreferredSize(std::size_t width, std::size_t height) {
    this->_width = width / SCALE_WIDTH + 2;
    this->_height = height / SCALE_HEIGHT + 2;
}

void NCurses::handleEvents() {
    int event = wgetch(stdscr);

    if (event == ERR)
        return;
    handleInput(event);
}

void NCurses::handleInput(int event)
{
    if (event == KEY_MOUSE) {
        MEVENT mouseEvent;
        if (getmouse(&mouseEvent) == OK) {
            IEvent::EventType type;
            EventKey key;
            if (mouseEvent.bstate & BUTTON1_CLICKED) {
                type = IEvent::EventType::_MOUSE_DOWN;
                key = _MOUSE_LEFT_CLICK;
            } else if (mouseEvent.bstate & BUTTON2_CLICKED) {
                type = IEvent::EventType::_MOUSE_DOWN;
                key = _MOUSE_MIDDLE_CLICK;
            } else if (mouseEvent.bstate & BUTTON3_CLICKED) {
                type = IEvent::EventType::_MOUSE_DOWN;
                key = _MOUSE_RIGHT_CLICK;
            } else {
                return;
            }
            int x = mouseEvent.x * SCALE_WIDTH;
            int y = mouseEvent.y * SCALE_HEIGHT;
            EventCallback callback = this->_events[std::make_pair(type, key)];
            std::cout << "Mouse event: " << x << " " << y << std::endl;
            if (callback)
                callback(Event(type, key, x, y));
        }
        return;
    }
    if (this->_keyMap.find(event) == this->_keyMap.end())
        return;

    EventCallback callback = this->_events[std::make_pair(IEvent::EventType::_KEY_DOWN, this->_keyMap[event])];
    if (callback) {
        callback(Event(IEvent::EventType::_KEY_DOWN, this->_keyMap[event]));
    } else {
        callback = this->_events[std::make_pair(IEvent::EventType::_KEY_PRESS, this->_keyMap[event])];
        if (callback)
            callback(Event(IEvent::EventType::_KEY_PRESS, this->_keyMap[event]));
    }
}
