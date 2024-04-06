/*
** EPITECH PROJECT, 2024
** Arcade
** File description:
** No file there , just an epitech header example .
** You can even have multiple lines if you want !
*/

#pragma once
#include "common/AGame.hpp"
#include "common/utils/Coord2D.hpp"
#include "common/utils/RGBAColor.hpp"
#include "common/displayable/primitives/Square.hpp"
#include "common/displayable/primitives/Text.hpp"
#include "Snake.hpp"
#include "Apple.hpp"
#include <deque>

class SnakeGame: public AGame {
public:
    enum Direction {
        UP,
        DOWN,
        LEFT,
        RIGHT
    };
    SnakeGame();
    ~SnakeGame() override;

    void start() override;
    void run() override;
    void bindEvents();

    void makeAnAppleSpawn();
    void eatingApple();

    void moveSnake();
    void inputMoveSnake(Direction direction);
    bool isGameOver();
    void updateScore();
    void drawBackground();
private:
    std::shared_ptr<Snake> _snake;
    std::shared_ptr<Apple> _food;
    std::shared_ptr<Square> _background_odd;
    std::shared_ptr<Square> _background_even;
    std::shared_ptr<Text> _scoreText;
    std::shared_ptr<Text> _highScoreText;
    std::shared_ptr<Text> _gameOverText;
    Direction _direction;
    float _time;
    bool _gameOver;
};
