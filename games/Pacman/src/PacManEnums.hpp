/*
** EPITECH PROJECT, 2024
** Pacman
** File description:
** No file there , just an epitech header example .
** You can even have multiple lines if you want !
*/

#pragma once

enum BonusPoint {
    _100 = 100,
    _200 = 200,
    _300 = 300,
    _400 = 400,
    _500 = 500,
    _700 = 700,
    _800 = 800,
    _1000 = 1000,
    _1600 = 1600,
    _2000 = 2000,
    _3000 = 3000,
    _5000 = 5000
};

enum GhostStrategy {
    CHASE = 0,
    SCATTER = 1
};

enum BonusType {
    CHERRY = 0,
    STRAWBERRY = 1,
    PEACH = 2,
    APPLE = 3,
    GRAPES = 4,
    GALAXIAN = 5,
    BELL = 6,
    KEY = 7
};

enum Direction {
    UP = 3,
    DOWN = 1,
    LEFT = 2,
    RIGHT = 0,
    NONE = -1
};

enum Animation {
    BoardBlink = 0,
    Ready = 1,
    None = 100
};