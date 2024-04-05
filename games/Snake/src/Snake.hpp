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
#include "SnakeException.hpp"
#include <deque>
#include <vector>
#include <iostream>

#define GRID_WIDTH 40
#define GRID_HEIGHT 40
#define GRID_SIZE 20

class Snake : public AEntity {
protected:
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
    ~Snake() override;
    [[nodiscard]] const Coord2D &getGridPos() const;
    [[nodiscard]] const Coord2D &getPrevSnakeGridPos() const;
    void setGridPos(const Coord2D &pos);
    [[nodiscard]] const std::deque<Coord2D> &getSnakePos() const;
    [[nodiscard]] std::deque<Snake *> getSnake();
    void initSnake(int x, int y);
    void moveSnake(int x, int y);
    void growSnake();
    void updateSnakeImage();
    void setSnakeImage();
    void setRotationImage();

private:
    Snake *prev;
    Snake *next;
    Coord2D gridPos;
    Coord2D _prevSnakeGridPos;
    std::size_t _size;
    std::vector<Picture> _snakeImages;
};
