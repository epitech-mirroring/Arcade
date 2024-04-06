/*
** EPITECH PROJECT, 2024
** Arcade
** File description:
** Snake
*/

#include "Snake.hpp"

Snake::Snake() : AEntity("./assets/games/Snake/empty.png", 40, 40, '#')
{
    this->_color = std::make_unique<RGBAColor>(0, 255, 0, 255);
    this->prev = nullptr;
    this->next = nullptr;
    this->gridPos = Coord2D(0, 0);
    this->_prevSnakeGridPos = Coord2D(0, 0);
    this->_size = 1;
    this->_snakeImages = {
        Picture("./assets/games/Snake/head_up.png", 40, 40),
        Picture("./assets/games/Snake/head_down.png", 40, 40),
        Picture("./assets/games/Snake/head_left.png", 40, 40),
        Picture("./assets/games/Snake/head_right.png", 40, 40),
        Picture("./assets/games/Snake/body_vertical.png", 40, 40),
        Picture("./assets/games/Snake/body_horizontal.png", 40, 40),
        Picture("./assets/games/Snake/body_topleft.png", 40, 40),
        Picture("./assets/games/Snake/body_bottomleft.png", 40, 40),
        Picture("./assets/games/Snake/body_topright.png", 40, 40),
        Picture("./assets/games/Snake/body_bottomright.png", 40, 40),
        Picture("./assets/games/Snake/tail_up.png", 40, 40),
        Picture("./assets/games/Snake/tail_down.png", 40, 40),
        Picture("./assets/games/Snake/tail_left.png", 40, 40),
        Picture("./assets/games/Snake/tail_right.png", 40, 40),
    };
}

Snake::~Snake()
{
    if (this->next)
        delete this->next;
}

void Snake::initSnake(int x, int y)
{
    Snake *tmp = this;

    this->gridPos = Coord2D(x, y);
    this->_prevSnakeGridPos = Coord2D(x, y + 1);
    while (this->_size < 4) {
        tmp->next = new Snake();
        if (!tmp->next)
            throw SnakeException("Error: Snake init failed");
        tmp->next->prev = tmp;
        tmp->next->gridPos = Coord2D(x, y + this->_size);
        this->_size++;
        tmp = tmp->next;
    }
}

const Coord2D &Snake::getGridPos() const
{
    return this->gridPos;
}

const Coord2D &Snake::getPrevSnakeGridPos() const
{
    return this->_prevSnakeGridPos;
}

void Snake::setGridPos(const Coord2D &gridPos)
{
    this->gridPos = gridPos;
}

std::deque<Coord2D> Snake::getSnakePos() const
{
    std::deque<Coord2D> snakePos;
    Snake *tmp = this->next;

    snakePos.push_back(this->gridPos);
    while (tmp) {
        snakePos.push_back(tmp->getGridPos());
        tmp = tmp->next;
    }
    return snakePos;
}

std::deque<Snake *> Snake::getSnake()
{
    std::deque<Snake *> snake;
    Snake *tmp = this->next;

    snake.push_back(this);
    while (tmp) {
        snake.push_back(tmp);
        tmp = tmp->next;
    }
    return snake;
}

void Snake::setSnakeImage()
{
    if (!this->prev || !this->next)
        return;
    int prevPosX = this->prev->gridPos.getX();
    int prevPosY = this->prev->gridPos.getY();
    int currentPosX = this->gridPos.getX();
    int currentPosY = this->gridPos.getY();
    int nextPosX = this->next->gridPos.getX();
    int nextPosY = this->next->gridPos.getY();

    if (prevPosX == currentPosX && currentPosX == nextPosX) {
        this->_sprite->setPicture(this->_snakeImages[BODY_VERTICAL]);
    } else if (prevPosY == currentPosY && currentPosY == nextPosY) {
        this->_sprite->setPicture(this->_snakeImages[BODY_HORIZONTAL]);
    } else if (currentPosX == prevPosX && currentPosY < prevPosY && currentPosY == nextPosY && currentPosX < nextPosX) {
        this->_sprite->setPicture(this->_snakeImages[BODY_BOTTOM_RIGHT]);
    } else if (currentPosX == prevPosX && currentPosY > prevPosY && currentPosY == nextPosY && currentPosX < nextPosX) {
        this->_sprite->setPicture(this->_snakeImages[BODY_TOP_RIGHT]);
    } else if (currentPosX == prevPosX && currentPosY < prevPosY && currentPosY == nextPosY && currentPosX > nextPosX) {
        this->_sprite->setPicture(this->_snakeImages[BODY_BOTTOM_LEFT]);
    } else if (currentPosX == prevPosX && currentPosY > prevPosY && currentPosY == nextPosY && currentPosX > nextPosX) {
        this->_sprite->setPicture(this->_snakeImages[BODY_TOP_LEFT]);
    } else if (currentPosY == prevPosY && currentPosX < prevPosX && currentPosX == nextPosX && currentPosY < nextPosY) {
        this->_sprite->setPicture(this->_snakeImages[BODY_BOTTOM_RIGHT]);
    } else if (currentPosY == prevPosY && currentPosX > prevPosX && currentPosX == nextPosX && currentPosY < nextPosY) {
        this->_sprite->setPicture(this->_snakeImages[BODY_BOTTOM_LEFT]);
    } else if (currentPosY == prevPosY && currentPosX < prevPosX && currentPosX == nextPosX && currentPosY > nextPosY) {
        this->_sprite->setPicture(this->_snakeImages[BODY_TOP_RIGHT]);
    } else if (currentPosY == prevPosY && currentPosX > prevPosX && currentPosX == nextPosX && currentPosY > nextPosY) {
        this->_sprite->setPicture(this->_snakeImages[BODY_TOP_LEFT]);
    }
}

void Snake::updateSnakeImage()
{
    Snake *tmp = this;
    int prevPosX = this->_prevSnakeGridPos.getX();
    int prevPosY = this->_prevSnakeGridPos.getY();
    int currentPosX = this->gridPos.getX();
    int currentPosY = this->gridPos.getY();

    if (currentPosX == prevPosX && currentPosY < prevPosY) {
        this->_sprite->setPicture(this->_snakeImages[HEAD_UP]);
    } else if (currentPosX == prevPosX && currentPosY > prevPosY) {
        this->_sprite->setPicture(this->_snakeImages[HEAD_DOWN]);
    } else if (currentPosY == prevPosY && currentPosX < prevPosX) {
        this->_sprite->setPicture(this->_snakeImages[HEAD_LEFT]);
    } else if (currentPosY == prevPosY && currentPosX > prevPosX) {
        this->_sprite->setPicture(this->_snakeImages[HEAD_RIGHT]);
    }
    while (tmp && tmp->next) {
        tmp->setSnakeImage();
        tmp = tmp->next;
    }
    if (!tmp)
        return;
    prevPosX = tmp->prev->gridPos.getX();
    prevPosY = tmp->prev->gridPos.getY();
    currentPosX = tmp->gridPos.getX();
    currentPosY = tmp->gridPos.getY();
    if (currentPosX == prevPosX && currentPosY <= prevPosY) {
        tmp->_sprite->setPicture(this->_snakeImages[TAIL_UP]);
    } else if (currentPosX == prevPosX && currentPosY >= prevPosY) {
        tmp->_sprite->setPicture(this->_snakeImages[TAIL_DOWN]);
    } else if (currentPosY == prevPosY && currentPosX <= prevPosX) {
        tmp->_sprite->setPicture(this->_snakeImages[TAIL_LEFT]);
    } else if (currentPosY == prevPosY && currentPosX >= prevPosX) {
        tmp->_sprite->setPicture(this->_snakeImages[TAIL_RIGHT]);
    }
}

void Snake::moveSnake(int x, int y)
{
    Snake *tmp = this;
    Coord2D tmpPos = this->gridPos;
    Coord2D tmpPos2;

    this->_prevSnakeGridPos = this->gridPos;
    this->gridPos.move(x, y);
    while (tmp->next) {
        tmpPos2 = tmp->next->gridPos;
        tmp->next->gridPos = tmpPos;
        tmpPos = tmpPos2;
        tmp = tmp->next;
    }
    this->updateSnakeImage();
}

void Snake::growSnake()
{
    Snake *tmp = this;

    while (tmp->next)
        tmp = tmp->next;
    tmp->next = new Snake();
    if (!tmp->next)
        return;
    tmp->next->prev = tmp;
    tmp->next->gridPos = tmp->gridPos;
    this->_size++;
}
