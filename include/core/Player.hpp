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
    std::unordered_map<std::string, int> _scores;
public:
    explicit Player(const std::string &name);
    ~Player() = default;
    void setScore(const std::string &gameName, int score);
    [[nodiscard]] int getTotalScore() const;
    void setName(const std::string &name);
    [[nodiscard]] const std::string &getName() const;
    [[nodiscard]] int getScore(const std::string &gameName) const;
    [[nodiscard]] const std::unordered_map<std::string, int> &getScores() const;
};
