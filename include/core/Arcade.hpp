/*
** EPITECH PROJECT, 2024
** Arcade
** File description:
** No file there , just an epitech header example .
** You can even have multiple lines if you want !
*/

#pragma once
#include "shared/IArcade.hpp"
#include "shared/ICanDrawGizmos.hpp"
#include "shared/IDriver.hpp"
#include "shared/IGame.hpp"
#include "core/Player.hpp"
#include "DLLoader.hpp"
#include <list>
#include <memory>
#include <queue>
#include <functional>
#include <map>
#include <chrono>

struct SharedLibrary {
    std::string name;
    std::string path;
};

template<typename T>
struct LoadedLibrary {
    T *instance;
    std::unique_ptr<DLLoader<T>> loader;
    std::string name;
};

class Arcade: public ICanDrawGizmos {
private:
    LoadedLibrary<IDriver> _driver;
    LoadedLibrary<IGame> _game;
    std::vector<Player *> _players;
    Player *_currentPlayer;
    std::vector<SharedLibrary> _games;
    std::vector<SharedLibrary> _drivers;
    std::size_t _currentGameIndex;
    std::size_t _currentDriverIndex;
    std::shared_ptr<IArcade> _arcade;
    std::queue<std::function<void()>> _endFrameCallbacks;
    std::queue<std::function<void()>> _gizmos;
    bool _running;
    bool _gizmosEnabled;
    std::size_t _preferredWidth;
    std::size_t _preferredHeight;
    std::map<IEvent::EventType, std::map<EventKey, EventCallback>> _events;
    float _deltaTime;
    std::vector<std::string> _shaders;


    void bareLoadDriver(const std::string &driverPath);
public:
    explicit Arcade(const std::string& firstDriverName, bool gizmosEnabled = true);
    ~Arcade() override;

    void loadDriver(const std::string &driverName);
    void loadGame(const std::string &gameName);
    void scanLibs();
    void loadScore();
    void saveScore();
    void rebindGlobalKeys();
    void rebindCustomKeys();
    void reApplyPreferences() const;
    [[nodiscard]] Player &getCurrentPlayer();
    [[nodiscard]] const std::vector<Player *> &getPlayers() const;
    void setArcadePtr(std::shared_ptr<IArcade> arcade);
    [[nodiscard]] float getDeltaTime() const override;
    [[nodiscard]] std::size_t getTime() const override;
    void sortPlayers();
    [[nodiscard]] std::size_t getCurrentGameHighScore() const override;
    void updateCurrentPlayerName(const std::string &name);

    void exit();
    void restart();
    void nextGame();
    void nextDriver();
    void menu();

    void run();
    void destroy();

    [[nodiscard]] std::vector<SharedLibrary> getGames() const;
    [[nodiscard]] std::vector<SharedLibrary> getDrivers() const;

    // Gizmos
    [[nodiscard]] bool isGizmosEnabled() const override;
    void drawLine(const ICoordinate &start, const ICoordinate &end, const IColor &color) override;
    void drawCircle(const ICoordinate &center, std::size_t radius, const IColor &color) override;
    void drawRect(const ICoordinate &topLeft, const ICoordinate &bottomRight, bool filled, const IColor &color) override;

    // Driver functions for games
    void display(const IDisplayable &displayable) override;
    void flipFrame() override;
    void bindEvent(IEvent::EventType type, EventKey key, EventCallback callback) override;
    void setPreferredSize(std::size_t width, std::size_t height) override;
    void addShader(const std::string &shaderPath) override;
    void reapplyShaders() const;
};
