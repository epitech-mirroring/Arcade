/*
** EPITECH PROJECT, 2024
** Arcade
** File description:
** No file there , just an epitech header example .
** You can even have multiple lines if you want !
*/

#include "core/Arcade.hpp"
#include "core/errors/NoSuchDriverException.hpp"
#include <dirent.h>
#include <unistd.h>
#include <algorithm>
#include <memory>
#include <utility>
#include "json/Json.hpp"
#include "core/menu/Menu.hpp"

Arcade::Arcade(const std::string &firstDriverName) {
    this->_currentPlayer = std::make_unique<Player>("Player", 0);
    this->_game = {nullptr, nullptr};
    this->_driver = {nullptr, nullptr};
    this->_players = std::vector<Player>();
    this->_games = std::vector<SharedLibrary>();
    this->_drivers = std::vector<SharedLibrary>();
    this->_preferredHeight = 800;
    this->_preferredWidth = 800;
    this->_endFrameCallbacks = std::queue<std::function<void()>>();
    this->scanLibs();
    this->loadScore();
    this->bareLoadDriver(firstDriverName);
    this->_currentDriverIndex = 0;
    this->_currentGameIndex = 0;
    this->_running = true;
}

Arcade::~Arcade() {
    if (this->_game.instance != nullptr) {
        this->_game.instance.reset();
        if (this->_game.loader != nullptr)
            this->_game.loader.reset();
    }
    if (this->_driver.instance != nullptr) {
        this->_driver.instance.reset();
        if (this->_driver.loader != nullptr)
            this->_driver.loader.reset();
    }
    this->saveScore();
}

void Arcade::bareLoadDriver(const std::string &driverPath) {
    std::unique_ptr<DLLoader<IDriver>> dl = std::make_unique<DLLoader<IDriver>>(driverPath, "create_driver");
    this->_driver.instance = dl->getInstance();
    this->_driver.loader = std::move(dl);
    this->rebindGlobalKeys();
}

void Arcade::loadDriver(const std::string &driverName) {
    // Check if driver exists
    if (std::find_if(this->_drivers.begin(), this->_drivers.end(), [driverName](const SharedLibrary &lib) { return lib.name == driverName; }) == this->_drivers.end()) {
        throw NoSuchDriverException(driverName);
    }
    SharedLibrary driver = *std::find_if(this->_drivers.begin(), this->_drivers.end(), [driverName](const SharedLibrary &lib) {
        return lib.name == driverName;
    });
    // Load driver
    std::unique_ptr<DLLoader<IDriver>> dl = std::make_unique<DLLoader<IDriver>>("./lib/" + driver.path, "create_driver");
    // If driver already loaded, unload it
    if (this->_driver.instance != nullptr) {
        this->_driver.instance.reset();
        if (this->_driver.loader != nullptr)
            this->_driver.loader.reset();
    }
    // Replace driver
    this->_driver.instance = dl->getInstance();
    this->_driver.loader = std::move(dl);
    this->rebindGlobalKeys();
}

void Arcade::loadGame(const std::string &gameName) {
    // Check if game exists
    if (std::find_if(this->_games.begin(), this->_games.end(), [gameName](const SharedLibrary &lib) { return lib.name == gameName; }) == this->_games.end()) {
        throw NoSuchDriverException(gameName);
    }
    SharedLibrary game = *std::find_if(this->_games.begin(), this->_games.end(), [gameName](const SharedLibrary &lib) {
        return lib.name == gameName;
    });
    // Load game
    std::unique_ptr<DLLoader<IGame>> dl = std::make_unique<DLLoader<IGame>>("./lib/" + game.path, "create_game");
    // If game already loaded, unload it
    if (this->_game.instance != nullptr) {
        if (this->_game.instance->getScore() > this->_currentPlayer->getScore()) {
            this->_currentPlayer->setScore(this->_game.instance->getScore());
        }
        this->saveScore();
        this->_game.instance.reset();
        if (this->_game.loader != nullptr)
            this->_game.loader.reset();
        this->_driver.instance->unbindAll();
        this->_events.clear();
        this->rebindGlobalKeys();
    }
    // Replace game
    this->_game.instance = dl->getInstance();
    this->_game.loader = std::move(dl);
    this->_game.instance->init(this->_arcade);
    this->_game.instance->start();
}

static std::string parseLibName(const std::string &filename) {
    std::string libName = filename;
    // remove "arcade_" prefix
    libName = libName.substr(7);
    // remove ".so" suffix
    libName = libName.substr(0, libName.size() - 3);
    return libName;
}

void Arcade::scanLibs() {
    DIR *dir;
    struct dirent *ent;
    // Clear lists
    this->_games.clear();
    this->_drivers.clear();
    if ((dir = opendir("./lib")) != nullptr) {
        while ((ent = readdir(dir)) != nullptr) {
            std::string filename = ent->d_name;
            if (filename.find(".so") != std::string::npos) {
                std::unique_ptr<DLLoader<IGame>> gameDl = nullptr;
                std::unique_ptr<DLLoader<IDriver>> driverDl = nullptr;
                try {
                    driverDl = std::make_unique<DLLoader<IDriver>>("./lib/" + filename, "create_driver");
                    if (driverDl->getLibName != nullptr)
                        this->_drivers.push_back({driverDl->getLibName(), filename});
                    else
                        this->_drivers.push_back({parseLibName(filename), filename});
                } catch (LibraryFormatException &e) {
                    try {
                        gameDl = std::make_unique<DLLoader<IGame>>("./lib/" + filename, "create_game");
                        if (gameDl->getLibName != nullptr)
                            this->_games.push_back({gameDl->getLibName(), filename});
                        else
                            this->_games.push_back({parseLibName(filename), filename});
                    } catch (std::exception &e) {
                        std::cerr << e.what() << std::endl;
                    }
                } catch (std::exception &e) {
                    std::cerr << "Unexpected error on library scan:\n" << e.what() << std::endl;
                }
                gameDl.reset();
                driverDl.reset();
            }
        }
        closedir(dir);
    }
}

void Arcade::loadScore() {
    // Check if file exists
    if (access("scores.json", F_OK) == -1) {
        return;
    }
    // Load scores
    JsonArray scores = JsonArray::parseFile("scores.json");

    this->_players.clear();
    for (std::size_t i = 0; i < scores.size(); i++) {
        JsonObject score = scores.getValue<JsonObject>(i);
        std::string name = score.getValue<JsonString>("name").getValue();
        int scoreValue = score.getValue<JsonInt>("score").getValue();
        this->_players.emplace_back(name, scoreValue);
    }
    // Update current player
    // Find player with same name
    auto it = std::find_if(this->_players.begin(), this->_players.end(), [this](const Player &player) {
        return player.getName() == this->_currentPlayer->getName();
    });
    // If found, update current player
    if (it != this->_players.end()) {
        this->_currentPlayer = std::make_unique<Player>(*it);
    }
}

void Arcade::saveScore() {
    JsonArray scores = JsonArray("scores");
    for (const Player &player : this->_players) {
        JsonObject score = JsonObject();
        JsonString name = JsonString("name", player.getName());
        JsonInt scoreValue = JsonInt("score", player.getScore());
        score.addValue(name);
        score.addValue(scoreValue);
        scores.addValue(score);
    }
    scores.writeToFile("scores.json");
}

void Arcade::display(const IDisplayable &displayable) {
    this->_driver.instance->display(displayable);
}

void Arcade::flipFrame() {
    this->_driver.instance->flipFrame();
}

void Arcade::bindEvent(IEvent::EventType type, EventKey key, EventCallback callback) {
    this->_driver.instance->bindEvent(type, key, callback);
    this->_events[type][key] = callback;
}

std::vector<SharedLibrary> Arcade::getGames() const {
    return this->_games;
}

std::vector<SharedLibrary> Arcade::getDrivers() const {
    return this->_drivers;
}

void Arcade::run() {
    if (this->_game.instance == nullptr) {
        this->menu();
    }
    long long frameStart = 0; // in milliseconds
    long long frameEnd = 0; // in milliseconds
    float targetFrameTime = 1.f / 60.f; // in seconds
    float targetFrameTimeMs = targetFrameTime * 1000.f; // in milliseconds
    long long frameTime = 0; // in milliseconds
    float toWait = 0; // in milliseconds
    long long lastFrameTime = 0; // in milliseconds
    while (this->_running) {
        frameStart = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count();
        this->_deltaTime = std::max((float) (frameStart - lastFrameTime), 0.f) / 1000.f;
        if (this->_game.instance != nullptr) {
            this->_game.instance->run();
        }
        while (!this->_endFrameCallbacks.empty()) {
            this->_endFrameCallbacks.front()();
            this->_endFrameCallbacks.pop();
        }
        frameEnd = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count();
        frameTime = frameEnd - frameStart;
        toWait = std::max(targetFrameTimeMs - (float) frameTime, 0.f);
        // std::cout << "Frame time: " << frameTime << "ms, waiting " << toWait << "ms" << std::endl;
        lastFrameTime = frameStart;
        usleep((int) (toWait * 1000.f));
    }
}

void Arcade::rebindGlobalKeys() {
    this->_driver.instance->bindEvent(IEvent::_KEY_DOWN, _KEY_ESCAPE, [this](const IEvent &event) {(void) event; this->exit();}); // Exit
    this->_driver.instance->bindEvent(IEvent::_KEY_DOWN, _KEY_F1, [this](const IEvent &event) {(void) event; this->restart();}); // Restart
    this->_driver.instance->bindEvent(IEvent::_KEY_DOWN, _KEY_F2, [this](const IEvent &event) {(void) event; this->menu();}); // Menu
    this->_driver.instance->bindEvent(IEvent::_KEY_DOWN, _KEY_F4, [this](const IEvent &event) {(void) event; this->nextGame();}); // Next game
    this->_driver.instance->bindEvent(IEvent::_KEY_DOWN, _KEY_F5, [this](const IEvent &event) {(void) event; this->nextDriver();}); // Next driver
    this->rebindCustomKeys();
    this->reApplyPreferences();
}

void Arcade::rebindCustomKeys() {
    for (const auto &[type, keys] : this->_events) {
        for (const auto &[key, callback] : keys) {
            this->_driver.instance->bindEvent(type, key, callback);
        }
    }
}

void Arcade::reApplyPreferences() const {
    this->_driver.instance->setPreferredSize(this->_preferredWidth,
                                             this->_preferredHeight);
}

void Arcade::exit() {
    this->_running = false;
}

void Arcade::restart() {
    this->_endFrameCallbacks.emplace([this]() {
        if (this->_game.instance != nullptr) {
            this->_game.instance->start();
        }
    });
}

void Arcade::menu() {
    this->_endFrameCallbacks.emplace([this]() {
        this->_currentGameIndex = 0;
        if (this->_game.instance != nullptr) {
            if (this->_game.instance->getScore() >
                this->_currentPlayer->getScore()) {
                this->_currentPlayer->setScore(
                        this->_game.instance->getScore());
            }
            this->saveScore();
            this->_game.instance.reset();
            if (this->_game.loader != nullptr)
                this->_game.loader.reset();
            this->_driver.instance->unbindAll();
            this->_events.clear();
            this->rebindGlobalKeys();
        }
        this->_game.instance = std::make_unique<Menu>();
        this->_game.loader = nullptr;
        this->_game.instance->init(this->_arcade);
        this->_game.instance->start();
    });
}

void Arcade::nextGame() {
    if (this->_game.instance != nullptr) {
        this->_currentGameIndex++;
        if (this->_currentGameIndex >= this->_games.size()) {
            this->_currentGameIndex = 0;
        }
        this->_endFrameCallbacks.emplace([this]() {this->loadGame(this->_games[this->_currentGameIndex].name);});
    }
}

void Arcade::nextDriver() {
    this->_currentDriverIndex++;
    if (this->_currentDriverIndex >= this->_drivers.size()) {
        this->_currentDriverIndex = 0;
    }
    this->_endFrameCallbacks.emplace([this]() {this->loadDriver(this->_drivers[this->_currentDriverIndex].name);});
}

void Arcade::setPreferredSize(std::size_t width, std::size_t height) {
    this->_preferredWidth = width;
    this->_preferredHeight = height;
    this->_driver.instance->setPreferredSize(width, height);
}

Player &Arcade::getCurrentPlayer() const {
    return *this->_currentPlayer;
}

const std::vector<Player> &Arcade::getPlayers() const {
    return this->_players;
}

void Arcade::setArcadePtr(std::shared_ptr<IArcade> arcade) {
    this->_arcade = std::move(arcade);
}

float Arcade::getDeltaTime() const {
    return this->_deltaTime;
}