/*
** EPITECH PROJECT, 2024
** Arcade
** File description:
** No file there , just an epitech header example .
** You can even have multiple lines if you want !
*/

#pragma once
#include "shared/IArcade.hpp"
#include "shared/IDriver.hpp"
#include "shared/IGame.hpp"
#include "core/Player.hpp"
#include <list>
#include <memory>

class Arcade: public IArcade {
private:
    std::unique_ptr<IDriver> _driver;
    std::unique_ptr<IGame> _game;
    std::list<Player> _players;
    std::unique_ptr<Player> _currentPlayer;
    std::list<std::string> _games;
    std::list<std::string> _drivers;
    int _currentGameIndex;
    int _currentDriverIndex;

    void bareLoadDriver(const std::string &driverPath);
public:
    explicit Arcade(const std::string& firstDriverName);
    ~Arcade() override = default;

    void loadDriver(const std::string &driverName);
    void loadGame(const std::string &gameName);
    void scanLibs();
    void loadScore();
    void rebindGlobalKeys();

    void exit(IEvent &event);
    void restart(IEvent &event);
    void nextGame(IEvent &event);
    void nextDriver(IEvent &event);
    void menu(IEvent &event);

    void run();

    [[nodiscard]] std::list<std::string> getGames() const;
    [[nodiscard]] std::list<std::string> getDrivers() const;

    // Driver functions for games
    void display(std::shared_ptr<IDisplayable> displayable) override;
    void flipFrame() override;
    void bindEvent(IEvent::EventType type, EventKey key, EventCallback callback) override;
};
