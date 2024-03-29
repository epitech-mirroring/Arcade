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

extern "C" {
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
    this->_preferredHeight = 500;
    this->_preferredWidth = 500;
    this->_window = std::unique_ptr<WINDOW, decltype(&delwin)>(initscr(), &delwin);
    if (this->_window == nullptr)
        throw std::runtime_error("Failed to initialize ncurses window");
    keypad(this->_window.get(), TRUE);
    noecho();
    curs_set(0);
    nodelay(this->_window.get(), TRUE);
    start_color();
    init_pair(1, COLOR_BLACK, COLOR_WHITE);
    init_pair(2, COLOR_RED, COLOR_BLACK);
    init_pair(3, COLOR_GREEN, COLOR_BLACK);
    init_pair(4, COLOR_YELLOW, COLOR_BLACK);
    init_pair(5, COLOR_BLUE, COLOR_BLACK);
    init_pair(6, COLOR_MAGENTA, COLOR_BLACK);
    init_pair(7, COLOR_CYAN, COLOR_BLACK);
    init_pair(8, COLOR_WHITE, COLOR_BLACK);
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

void NCurses::displayText(const IText &text) {
    int color = getNcursesColor(text.getColor());
    std::size_t x = text.getPosition().getX();
    std::size_t y = text.getPosition().getY();

    for (std::size_t i = 0; i < text.getText().size(); i++) {
        this->_frameBuffer[x + i][y] = BufferedChar{text.getText()[i], color};
    }
}

void NCurses::displayCircle(const ICircle &circle) {
    std::size_t radius = circle.getRadius();
    std::size_t centerX = circle.getPosition().getX() + radius;
    std::size_t centerY = circle.getPosition().getY() + radius;
    std::size_t startX = circle.getPosition().getX();
    std::size_t startY = circle.getPosition().getY();
    std::size_t endX = circle.getPosition().getX() + radius * 2;
    std::size_t endY = circle.getPosition().getY() + radius * 2;
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

    for (std::size_t y = square.getPosition().getY(); y < square.getHeight(); y++) {
        for (std::size_t x = square.getPosition().getX(); x < square.getWidth(); x++) {
            // Draw hollow square
            if (x == 0 || y == 0 || y == square.getHeight() - 1 || x == square.getWidth() - 1) {
                this->_frameBuffer[x][y] = BufferedChar{square.getReplacingChar(), color};
            }
        }
    }
}

void NCurses::displayPrimitive(const IPrimitive &primitive) {
    if (INSTANCE_OF(const IText, primitive)) {
        displayText(dynamic_cast<const IText &>(primitive));
    } else if (INSTANCE_OF(const ICircle, primitive)) {
        displayCircle(dynamic_cast<const ICircle &>(primitive));
    } else if (INSTANCE_OF(const ISquare, primitive)) {
        displaySquare(dynamic_cast<const ISquare &>(primitive));
    }
}

void NCurses::displayEntity(const IEntity &entity) {
    // display entity
}

void NCurses::display(const IDisplayable &displayable) {
    if (INSTANCE_OF(const IPrimitive, displayable)) {
        displayPrimitive(dynamic_cast<const IPrimitive &>(displayable));
    } else if (INSTANCE_OF(const IEntity, displayable)) {
        displayEntity(dynamic_cast<const IEntity &>(displayable));
    }
}

void NCurses::flipFrame() {
    if (this->_window == nullptr)
        throw std::runtime_error("Window is null");
    std::size_t width = getmaxx(this->_window.get());
    std::size_t height = getmaxy(this->_window.get());

    if (width < this->_preferredWidth || height < this->_preferredHeight) {
        mvwprintw(this->_window.get(), 0, 0, "Window is too small");
        wrefresh(this->_window.get());
        return;
    }

    for (std::size_t x = 0; x < this->_preferredWidth; x++) {
        for (std::size_t y = 0; y < this->_preferredHeight; y++) {
            if (this->_frameBuffer.find(x) != this->_frameBuffer.end() &&
                this->_frameBuffer[x].find(y) != this->_frameBuffer[x].end()) {
                wattron(this->_window.get(), COLOR_PAIR(this->_frameBuffer[x][y].color));
                mvwaddch(this->_window.get(), y, x, this->_frameBuffer[x][y].c);
                wattroff(this->_window.get(), COLOR_PAIR(this->_frameBuffer[x][y].color));
            } else {
                mvwaddch(this->_window.get(), y, x, ' ');
            }
        }
    }
    wrefresh(this->_window.get());
    this->_frameBuffer.clear();
}

void NCurses::bindEvent(IEvent::EventType type, EventKey key, EventCallback callback) {
    if (type == IEvent::MOUSE_DOWN || type == IEvent::MOUSE_UP || type == IEvent::MOUSE_MOVE)
        return;
    this->_events[key] = callback;
}

void NCurses::setPreferredSize(std::size_t width, std::size_t height) {
    this->_preferredWidth = width;
    this->_preferredHeight = height;
}
