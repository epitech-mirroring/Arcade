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

struct SharedLibrary {
    std::string name;
    std::string path;
};

class Arcade: public IArcade {
private:
    std::unique_ptr<IDriver> _driver;
    std::unique_ptr<IGame> _game;
    std::list<Player> _players;
    std::unique_ptr<Player> _currentPlayer;
    std::list<SharedLibrary> _games;
    std::list<SharedLibrary> _drivers;
    int _currentGameIndex;
    int _currentDriverIndex;
    bool _running;

    void bareLoadDriver(const std::string &driverPath);
public:
    explicit Arcade(const std::string& firstDriverName);
    ~Arcade() override;

    void loadDriver(const std::string &driverName);
    void loadGame(const std::string &gameName);
    void scanLibs();
    void loadScore();
    void saveScore();
    void rebindGlobalKeys();

    void exit(IEvent &event);
    void restart(IEvent &event);
    void nextGame(IEvent &event);
    void nextDriver(IEvent &event);
    void menu(IEvent &event);

    void run();

    [[nodiscard]] std::list<SharedLibrary> getGames() const;
    [[nodiscard]] std::list<SharedLibrary> getDrivers() const;

    // Driver functions for games
    void display(std::shared_ptr<IDisplayable> displayable) override;
    void flipFrame() override;
    void bindEvent(IEvent::EventType type, EventKey key, EventCallback callback) override;
};
