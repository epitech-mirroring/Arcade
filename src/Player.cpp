/*
** EPITECH PROJECT, 2024
** Arcade
** File description:
** No file there , just an epitech header example .
** You can even have multiple lines if you want !
*/

#include "core/Player.hpp"

Player::Player(const std::string &name, int score)
{
    this->_name = name;
    this->_score = score;
}

void Player::setScore(int score)
{
    this->_score = score;
}

int Player::getScore() const
{
    return this->_score;
}

void Player::setName(const std::string &name)
{
    this->_name = name;
}

const std::string &Player::getName() const
{
    return this->_name;
}
