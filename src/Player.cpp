/*
** EPITECH PROJECT, 2024
** Arcade
** File description:
** No file there , just an epitech header example .
** You can even have multiple lines if you want !
*/

#include "core/Player.hpp"

Player::Player(const std::string &name)
{
    this->_name = name;
}

void Player::setScore(const std::string &gameName, int score)
{
    this->_scores[gameName] = score;
}

int Player::getTotalScore() const
{
    int total = 0;
    for (auto &score : this->_scores) {
        total += score.second;
    }
    return total;
}

void Player::setName(const std::string &name)
{
    this->_name = name;
}

const std::string &Player::getName() const
{
    return this->_name;
}

int Player::getScore(const std::string &gameName) const
{
    if (this->_scores.find(gameName) == this->_scores.end())
        return 0;
    return this->_scores.at(gameName);
}

const std::unordered_map<std::string, int> &Player::getScores() const
{
    return this->_scores;
}
