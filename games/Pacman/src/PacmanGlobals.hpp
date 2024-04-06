/*
** EPITECH PROJECT, 2024
** Pacman
** File description:
** No file there , just an epitech header example .
** You can even have multiple lines if you want !
*/

#pragma once
#include "shared/IArcade.hpp"
#include "PacManEnums.hpp"
#include "Pacman.hpp"

#define SCALE 2
#define MAP_WIDTH 28
#define MAP_HEIGHT 37
#define GIZMOS(x) (dynamic_cast<ICanDrawGizmos *>(&x))
#define IS_GIZMOS(x) (dynamic_cast<ICanDrawGizmos *>(&x) != nullptr && GIZMOS(x)->isGizmosEnabled())

Direction operator!(Direction dir);

struct Level {
    BonusType bonus;
    BonusPoint point;
    float pacmanSpeed;
    float ghostSpeed;
    float pacmanFrightenedSpeed;
    float ghostFrightenedSpeed;
    int frightenedDuration;
    float ghostTunnelSpeed;
    float pacDotSpeed;
    float pacDotFrightenedSpeed;
    int elroyDots;
    float elroySpeed;
};

const Level levels[] = {
{CHERRY     ,   _100,   0.8, 0.75, 0.9  , 0.5   ,   6, 0.4  , 0.71, 0.79,   20  ,   0.8}, // Level 1
{STRAWBERRY ,   _300,   0.9, 0.85, 0.95 , 0.55  ,   5, 0.45 , 0.79, 0.83,   30  ,   0.9}, // Level 2
{PEACH      ,   _500,   0.9, 0.85, 0.95 , 0.55  ,   4, 0.45 , 0.79, 0.83,   40  ,   0.9}, // Level 3
{PEACH      ,   _500,   0.9, 0.85, 0.95 , 0.55  ,   3, 0.45 , 0.79, 0.83,   40  ,   0.9}, // Level 4
{APPLE      ,   _700,   1  , 0.95, 1    , 0.6   ,   2, 0.5  , 0.87, 0.87,   40  ,   1  }, // Level 5
{APPLE      ,   _700,   1  , 0.95, 1    , 0.6   ,   5, 0.5  , 0.87, 0.87,   50  ,   1  }, // Level 6
{GRAPES     ,   _1000,  1  , 0.95, 1    , 0.6   ,   2, 0.5  , 0.87, 0.87,   50  ,   1  }, // Level 7
{GRAPES     ,   _1000,  1  , 0.95, 1    , 0.6   ,   2, 0.5  , 0.87, 0.87,   50  ,   1  }, // Level 8
{GALAXIAN   ,   _2000,  1  , 0.95, 1    , 0.6   ,   1, 0.5  , 0.87, 0.87,   60  ,   1  }, // Level 9
{GALAXIAN   ,   _2000,  1  , 0.95, 1    , 0.6   ,   5, 0.5  , 0.87, 0.87,   60  ,   1  }, // Level 10
{BELL       ,   _3000,  1  , 0.95, 1    , 0.6   ,   2, 0.5  , 0.87, 0.87,   60  ,   1  }, // Level 11
{BELL       ,   _3000,  1  , 0.95, 1    , 0.6   ,   1, 0.5  , 0.87, 0.87,   80  ,   1  }, // Level 12
{KEY        ,   _5000,  1  , 0.95, 1    , 0.6   ,   1, 0.5  , 0.87, 0.87,   80  ,   1  }, // Level 13
{KEY        ,   _5000,  1  , 0.95, 1    , 0.6   ,   3, 0.5  , 0.87, 0.87,   80  ,   1  }, // Level 14
{KEY        ,   _5000,  1  , 0.95, 1    , 0.6   ,   1, 0.5  , 0.87, 0.87,   100 ,   1  }, // Level 15
{KEY        ,   _5000,  1  , 0.95, 1    , 0.6   ,   1, 0.5  , 0.87, 0.87,   100 ,   1  }, // Level 16
{KEY        ,   _5000,  1  , 0.95, 1    , 0.6   ,   0, 0.5  , 0.87, 0   ,   100 ,   1  }, // Level 17
{KEY        ,   _5000,  1  , 0.95, 1    , 0.6   ,   1, 0.5  , 0.87, 0.87,   100 ,   1  }, // Level 18
{KEY        ,   _5000,  1  , 0.95, 1    , 0.6   ,   0, 0.5  , 0.87, 0   ,   120 ,   1  }, // Level 19
{KEY        ,   _5000,  1  , 0.95, 1    , 0.6   ,   0, 0.5  , 0.87, 0   ,   120 ,   1  }, // Level 20
{KEY        ,   _5000,  0.9, 0.95, 1    , 0.6   ,   0, 0.5  , 0.79, 0   ,   120 ,   1  }};// Level 21+

struct GhostStrategyTime {
    GhostStrategy strategy;
    std::size_t lasting; // in ms
};

const GhostStrategyTime strategyTimes[3][8]= {
        {{GhostStrategy::SCATTER, 7000}, {CHASE, 20000}, {SCATTER, 7000}, {CHASE, 20000}, {SCATTER, 5000}, {CHASE, 20000}, {SCATTER, 5000}, {CHASE, 0}}, // Level 1
        {{GhostStrategy::SCATTER, 7000}, {CHASE, 20000}, {SCATTER, 7000}, {CHASE, 20000}, {SCATTER, 5000}, {CHASE, 1033000}, {SCATTER, 16}, {CHASE, 0}}, // Level 2-4
        {{GhostStrategy::SCATTER, 5000}, {CHASE, 20000}, {SCATTER, 5000}, {CHASE, 20000}, {SCATTER, 5000}, {CHASE, 1037000}, {SCATTER, 16}, {CHASE, 0}}, // Level 5+
};

extern bool isFrightened;
extern int frightenedMsLeft;
extern int currentLevel;
extern int currentLives;
extern std::shared_ptr<IArcade> arcade;
extern int *score;
extern Pacman *game;
extern bool isGlobalDotCounter;
extern std::size_t globalDotCounter;
extern bool isInAnimation;
extern Animation animation;
extern std::size_t animationStart;
extern bool shouldDisplayActors;
extern bool shouldDisplayAnything;