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
#include "json/Json.hpp"
#include "core/menu/Menu.hpp"

Arcade::Arcade(const std::string &firstDriverName) {
    this->_arcade = std::shared_ptr<IArcade>(this);
    this->_currentPlayer = std::make_unique<Player>("Player", 0);
    this->_game = {nullptr, nullptr};
    this->_driver = {nullptr, nullptr};
    this->_players = std::vector<Player>();
    this->_games = std::vector<SharedLibrary>();
    this->_drivers = std::vector<SharedLibrary>();
    this->scanLibs();
    this->loadScore();
    this->bareLoadDriver(firstDriverName);
    this->_currentDriverIndex = 0;
    this->_currentGameIndex = 0;
    this->_running = true;
    this->_game = {std::make_unique<Menu>(), nullptr};
    this->_game.instance->init(this->_arcade);
    this->_game.instance->start();
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
    this->_driver = {dl->getInstance(), std::move(dl)};
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
        this->_driver.loader.reset();
    }
    // Replace driver
    this->_driver = {dl->getInstance(), std::move(dl)};
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
    }
    // Replace game
    this->_game = {dl->getInstance(), std::move(dl)};
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
                try {
                    std::unique_ptr<DLLoader<IDriver>> dl = std::make_unique<DLLoader<IDriver>>("./lib/" + filename, "create_driver");
                    if (dl->getLibName != nullptr)
                        this->_drivers.push_back({dl->getLibName(), filename});
                    else
                        this->_drivers.push_back({filename, parseLibName(filename)});
                    dl.reset();
                } catch (LibraryFormatException &e) {
                    try {
                        std::unique_ptr<DLLoader<IGame>> dl = std::make_unique<DLLoader<IGame>>("./lib/" + filename, "create_game");
                        if (dl->getLibName != nullptr)
                            this->_games.push_back({dl->getLibName(), filename});
                        else
                            this->_games.push_back({filename, parseLibName(filename)});
                        dl.reset();
                    } catch (std::exception &e) {
                        std::cerr << e.what() << std::endl;
                        continue;
                    }
                } catch (std::exception &e) {
                    std::cerr << "Unexpected error on library scan:\n" << e.what() << std::endl;
                    continue;
                }
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
}

std::vector<SharedLibrary> Arcade::getGames() const {
    return this->_games;
}

std::vector<SharedLibrary> Arcade::getDrivers() const {
    return this->_drivers;
}

void Arcade::run() {
    while (this->_running) {
        if (this->_game.instance != nullptr) {
            this->_game.instance->run();
        }
        usleep((int) (1.f/60.f * 1000000.f));
    }
}

void Arcade::rebindGlobalKeys() {
    this->_driver.instance->bindEvent(IEvent::KEY_DOWN, KEY_ESCAPE, [this](const IEvent &event) {this->exit(event);}); // Exit
    this->_driver.instance->bindEvent(IEvent::KEY_DOWN, KEY_F1, [this](const IEvent &event) {this->restart(event);}); // Restart
    this->_driver.instance->bindEvent(IEvent::KEY_DOWN, KEY_F2, [this](const IEvent &event) {this->menu(event);}); // Menu
    this->_driver.instance->bindEvent(IEvent::KEY_DOWN, KEY_F4, [this](const IEvent &event) {this->nextGame(event);}); // Next game
    this->_driver.instance->bindEvent(IEvent::KEY_DOWN, KEY_F5, [this](const IEvent &event) {this->nextDriver(event);}); // Next driver
}

void Arcade::exit(const IEvent &event) {
    (void) event;
    this->_running = false;
}

void Arcade::restart(const IEvent &event) {
    (void) event;
    if (this->_game.instance != nullptr) {
        this->_game.instance->start();
    }
}

void Arcade::menu(const IEvent &event) {
    (void) event;
    //TODO
}

void Arcade::nextGame(const IEvent &event) {
    (void) event;
    if (this->_game.instance != nullptr) {
        this->_currentGameIndex++;
        if (this->_currentGameIndex >= this->_games.size()) {
            this->_currentGameIndex = 0;
        }
        this->loadGame(this->_games[this->_currentGameIndex].name);
    }
}

void Arcade::nextDriver(const IEvent &event) {
    (void) event;
    this->_currentDriverIndex++;
    if (this->_currentDriverIndex >= this->_drivers.size()) {
        this->_currentDriverIndex = 0;
    }
    this->loadDriver(this->_drivers[this->_currentDriverIndex].name);
}

void Arcade::setPreferredSize(std::size_t width, std::size_t height) {
    this->_driver.instance->setPreferredSize(width, height);
}

Player &Arcade::getCurrentPlayer() const {
    return *this->_currentPlayer;
}

const std::vector<Player> &Arcade::getPlayers() const {
    return this->_players;
}

std::shared_ptr<IArcade> Arcade::getArcade() const {
    return this->_arcade;
}
