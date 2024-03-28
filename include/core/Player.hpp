/*
** EPITECH PROJECT, 2024
** Arcade
** File description:
** No file there , just an epitech header example .
** You can even have multiple lines if you want !
*/

#pragma once
#include <string>

class Player {
protected:
    std::string _name;
    int _score;
public:
    Player(const std::string &name, int score = 0);
    ~Player() = default;
    void setScore(int score);
    int getScore() const;
    void setName(const std::string &name);
    const std::string &getName() const;
};
