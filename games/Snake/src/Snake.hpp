/*
** EPITECH PROJECT, 2024
** Arcade
** File description:
** Snake
*/

#pragma once
#include "common/displayable/entities/AEntity.hpp"
#include "common/utils/Coord2D.hpp"
#include "common/utils/Picture.hpp"
#include <deque>
#include <vector>
#include <iostream>

#define GRID_WIDTH 40
#define GRID_HEIGHT 40
#define GRID_SIZE 20

class Snake : public AEntity {
    enum ImageEnum {
        HEAD_UP,
        HEAD_DOWN,
        HEAD_LEFT,
        HEAD_RIGHT,
        BODY_VERTICAL,
        BODY_HORIZONTAL,
        BODY_TOP_LEFT,
        BODY_BOTTOM_LEFT,
        BODY_TOP_RIGHT,
        BODY_BOTTOM_RIGHT,
        TAIL_UP,
        TAIL_DOWN,
        TAIL_LEFT,
        TAIL_RIGHT,
    };

public:
    Snake();
    ~Snake();
    Coord2D getPos() const;
    Coord2D getPrevSnakePos() const;
    void setPos(const Coord2D &pos);
    std::deque<Coord2D> getSnakePos() const;
    std::deque<Snake *> getSnake();
    void initSnake(int x, int y);
    void moveSnake(int x, int y);
    void growSnake();
    void updateSnakeImage();
    void setSnakeImage();
    void setRotationImage();

private:
    Snake *prev;
    Snake *next;
    Coord2D pos;
    Coord2D _precSnakePos;
    std::size_t _size;
    std::vector<Picture> _snakeImages;
};
