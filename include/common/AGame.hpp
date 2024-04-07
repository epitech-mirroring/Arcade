/*
** EPITECH PROJECT, 2024
** Arcade
** File description:
** No file there , just an epitech header example .
** You can even have multiple lines if you want !
*/

#pragma once
#include "../shared/IGame.hpp"

class AGame: public IGame {
protected:
    std::shared_ptr<IArcade> _arcade;
    int _score;

public:
    AGame();
    ~AGame() override = default;

    /**
     * @brief Initialize the game (linking the game with the arcade)
     * @param arcade The arcade instance that will be used to interact with the game
     */
    virtual void init(std::shared_ptr<IArcade> arcade) override;
    /**
     * @brief Start the game
     * This method should be called after the init method or anytime you want to (re)start the game
     */
    virtual void start() override = 0;
    /**
     * @brief Run the game
     * This method is called every frame
     */
    virtual void run() override = 0;
    /**
     * @brief Get the score of the game
     * @return The score of the game
     */
    virtual int getScore() override;
};
