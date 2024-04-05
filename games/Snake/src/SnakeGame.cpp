/*
** EPITECH PROJECT, 2024
** Arcade
** File description:
** No file there , just an epitech header example .
** You can even have multiple lines if you want !
*/

#include "SnakeGame.hpp"
#include <iostream>

extern "C" {
    __attribute__((constructor))
    void load_lib() {
        std::cout << "Loading Snake" << std::endl;
    }

    __attribute__((destructor))
    void unload_lib() {
        std::cout << "Unloading Snake" << std::endl;
    }

    std::unique_ptr<IGame> create_game() {
        std::unique_ptr<IGame> game = std::make_unique<SnakeGame>();
        return game;
    }

    const std::string &get_name() {
        static const std::string game_name = "Snake";
        return game_name;
    }
}

SnakeGame::SnakeGame()
{
    srand(time(NULL));
    this->_snake = nullptr;
    this->_food = nullptr;
    this->_time = 0;
    this->_score = 0;
    this->_direction = UP;
    this->_gameOver = false;
    this->_scoreText = std::make_shared<Text>(RGBAColor(255, 255, 255, 255), "Score: 0", "assets/PressStart2P.ttf");
    this->_scoreText->setPosition(Coord2D(GRID_WIDTH * GRID_SIZE / 2 + 100, 0));
    this->_scoreText->setSize(20);
    this->_highScoreText = std::make_shared<Text>(RGBAColor(255, 255, 255, 255), "High Score: 0", "assets/PressStart2P.ttf");
    this->_highScoreText->setPosition(Coord2D(150, 0));
    this->_highScoreText->setSize(20);
    this->_gameOverText = std::make_shared<Text>(RGBAColor(255, 0, 0, 255), "Game Over", "assets/PressStart2P.ttf");
    this->_gameOverText->setPosition(Coord2D(200, GRID_HEIGHT * GRID_SIZE / 2));
    this->_gameOverText->setSize(50);
    this->_background_even = std::make_shared<Square>(RGBAColor(162, 209, 73, 255), GRID_WIDTH, GRID_HEIGHT, '#');
    this->_background_odd = std::make_shared<Square>(RGBAColor(170, 215, 81, 255), GRID_WIDTH, GRID_HEIGHT, '#');
}

SnakeGame::~SnakeGame()
{
    this->_snake.reset();
}

void SnakeGame::start()
{
    if (this->_snake != nullptr)
        this->_snake.reset();
    if (this->_food != nullptr)
        this->_food.reset();
    this->_snake = std::make_shared<Snake>();
    this->_food = nullptr;
    this->_time = 0;
    this->_score = 0;
    this->_direction = UP;
    this->_gameOver = false;
    this->_arcade->setPreferredSize(GRID_WIDTH * GRID_SIZE, GRID_HEIGHT * GRID_SIZE);
    this->_snake->initSnake(GRID_SIZE / 2, GRID_SIZE / 2);
    this->bindEvents();
    this->_arcade->flipFrame();
}

void SnakeGame::run()
{
    if (this->isGameOver()) {
        this->_arcade->display(*this->_gameOverText);
        this->_arcade->flipFrame();
        return;
    }
    this->drawBackground();
    this->_time += this->_arcade->getDeltaTime();
    if (this->_time > 0.15) {
        this->moveSnake();
        this->_time -= 0.15;
    }
    if (this->_food == nullptr)
        this->makeAnAppleSpawn();
    eatingApple();
    std::deque<Snake *> snakes = this->_snake->getSnake();

    for (auto &elem : snakes) {
        Coord2D pos = elem->getPos();
        pos *= GRID_WIDTH;
        elem->setPosition(pos);
        this->_arcade->display(*elem);
    }
    Coord2D foodPos = this->_food->getPos();
    foodPos *= GRID_WIDTH;
    this->_food->setPosition(foodPos);
    this->_arcade->display(*(this->_food));
    this->updateScore();
    this->_arcade->display(*(this->_scoreText));
    this->_arcade->display(*(this->_highScoreText));
    this->_arcade->flipFrame();
}

void SnakeGame::bindEvents()
{
    this->_arcade->bindEvent(IEvent::_KEY_DOWN, _KEY_Z, [this](const IEvent &event) {(void) event; this->inputMoveSnake(Direction::UP);});
    this->_arcade->bindEvent(IEvent::_KEY_DOWN, _KEY_UP, [this](const IEvent &event) {(void) event; this->inputMoveSnake(Direction::UP);});
    this->_arcade->bindEvent(IEvent::_KEY_DOWN, _KEY_S, [this](const IEvent &event) {(void) event; this->inputMoveSnake(Direction::DOWN);});
    this->_arcade->bindEvent(IEvent::_KEY_DOWN, _KEY_DOWN, [this](const IEvent &event) {(void) event; this->inputMoveSnake(Direction::DOWN);});
    this->_arcade->bindEvent(IEvent::_KEY_DOWN, _KEY_Q, [this](const IEvent &event) {(void) event; this->inputMoveSnake(Direction::LEFT);});
    this->_arcade->bindEvent(IEvent::_KEY_DOWN, _KEY_LEFT, [this](const IEvent &event) {(void) event; this->inputMoveSnake(Direction::LEFT);});
    this->_arcade->bindEvent(IEvent::_KEY_DOWN, _KEY_D, [this](const IEvent &event) {(void) event; this->inputMoveSnake(Direction::RIGHT);});
    this->_arcade->bindEvent(IEvent::_KEY_DOWN, _KEY_RIGHT, [this](const IEvent &event) {(void) event; this->inputMoveSnake(Direction::RIGHT);});
}

void SnakeGame::moveSnake()
{
    Coord2D pos = this->_snake->getPos();
    int x = 0;
    int y = 0;

    switch (this->_direction) {
        case UP:
            y -= 1;
            break;
        case DOWN:
            y += 1;
            break;
        case LEFT:
            x -= 1;
            break;
        case RIGHT:
            x += 1;
            break;
    }
    this->_snake->moveSnake(x, y);
}

void SnakeGame::inputMoveSnake(Direction direction)
{
    Coord2D pos = this->_snake->getPos();
    Coord2D precPos = this->_snake->getPrevSnakePos();
    int x = pos.getX() - precPos.getX();
    int y = pos.getY() - precPos.getY();

    if (x == 0 && y == 1) {
        if (direction != UP)
            this->_direction = direction;
    } else if (x == 0 && y == -1) {
        if (direction != DOWN)
            this->_direction = direction;
    } else if (x == 1 && y == 0) {
        if (direction != LEFT)
            this->_direction = direction;
    } else if (x == -1 && y == 0) {
        if (direction != RIGHT)
            this->_direction = direction;
    }
}

void SnakeGame::makeAnAppleSpawn()
{
    int x = rand() % GRID_SIZE;
    int y = rand() % GRID_SIZE;
    Coord2D applePos = Coord2D(x, y);
    std::deque<Coord2D> snakePos = this->_snake->getSnakePos();
    while (std::find(snakePos.begin(), snakePos.end(), applePos) != snakePos.end()) {
        x = rand() % GRID_SIZE;
        y = rand() % GRID_SIZE;
        applePos = Coord2D(x, y);
    }
    this->_food = std::make_shared<Apple>(x, y);
}

void SnakeGame::eatingApple()
{
    Coord2D snakePos = this->_snake->getPos();
    Coord2D foodPos = this->_food->getPos();

    if (snakePos == foodPos) {
        this->_score += 100;
        this->_food.reset();
        this->makeAnAppleSpawn();
        this->_snake->growSnake();
    }
}

bool SnakeGame::isGameOver()
{
    std::deque<Coord2D> snakePos = this->_snake->getSnakePos();
    Coord2D pos = this->_snake->getPos();

    if (pos.getX() < 0 || pos.getX() >= GRID_SIZE || pos.getY() < 0 || pos.getY() >= GRID_SIZE)
        return true;
    snakePos.pop_front();
    if (std::find(snakePos.begin(), snakePos.end(), pos) != snakePos.end())
        return true;
    return false;
}

void SnakeGame::updateScore()
{
    this->_scoreText->setText("Score: " + std::to_string(this->_score));
}

void SnakeGame::drawBackground()
{
    for (int i = 0; i < GRID_HEIGHT; i++) {
        for (int j = 0; j < GRID_WIDTH; j++) {
            if ((i + j) % 2 == 0) {
                this->_background_even->setPosition(Coord2D(j * GRID_WIDTH, i * GRID_HEIGHT));
                this->_arcade->display(*this->_background_even);
            } else {
                this->_background_odd->setPosition(Coord2D(j * GRID_WIDTH, i * GRID_HEIGHT));
                this->_arcade->display(*this->_background_odd);
            }
        }
    }
}
