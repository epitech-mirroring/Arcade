/*
** EPITECH PROJECT, 2024
** Arcade
** File description:
** No file there , just an epitech header example .
** You can even have multiple lines if you want !
*/

#include "core/Arcade.hpp"
#include "core/errors/NoSuchDriverException.hpp"
#include "core/DLLoader.hpp"
#include <dirent.h>

Arcade::Arcade(const std::string &firstDriverName) {
    this->_currentPlayer = nullptr;
    this->_game = nullptr;
    this->_driver = nullptr;
    this->_players = std::list<Player>();
    this->_games = std::list<std::string>();
    this->_drivers = std::list<std::string>();
    this->scanLibs();
    this->loadScore();
    this->bareLoadDriver(firstDriverName);
}

void Arcade::bareLoadDriver(const std::string &driverPath) {
    DLLoader<IDriver> dl = DLLoader<IDriver>(driverPath, "create_driver");
    this->_driver = dl.getInstance();
}

void Arcade::loadDriver(const std::string &driverName) {
    // Check if driver exists
    if (std::find(this->_drivers.begin(), this->_drivers.end(), driverName) == this->_drivers.end()) {
        throw NoSuchDriverException(driverName);
    }
    // Load driver
    DLLoader<IDriver> dl = DLLoader<IDriver>("./lib/" + driverName + ".so", "create_driver");
    // If driver already loaded, unload it
    if (this->_driver != nullptr) {
        this->_driver.reset();
    }
    // Replace driver
    this->_driver = dl.getInstance();
}

void Arcade::loadGame(const std::string &gameName) {
    // Check if game exists
    if (std::find(this->_games.begin(), this->_games.end(), gameName) == this->_games.end()) {
        throw NoSuchDriverException(gameName);
    }
    // Load game
    DLLoader<IGame> dl = DLLoader<IGame>("./lib/" + gameName + ".so", "create_game");
    // If game already loaded, unload it
    if (this->_game != nullptr) {
        this->_game.reset();
    }
    // Replace game
    this->_game = dl.getInstance();
    this->_game->init(std::shared_ptr<IArcade>(this));
    this->_game->start();
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
    if ((dir = opendir("./lib")) != nullptr) {
        while ((ent = readdir(dir)) != nullptr) {
            std::string filename = ent->d_name;
            if (filename.find(".so") != std::string::npos) {
                try {
                    DLLoader<IDriver> dl = DLLoader<IDriver>("./lib/" + filename, "create_driver");
                    if (dl.getLibName != nullptr)
                        this->_drivers.push_back(dl.getLibName());
                    else
                        this->_drivers.push_back(parseLibName(filename));
                } catch (LibraryFormatException &e) {
                    try {
                        DLLoader<IGame> dl = DLLoader<IGame>("./lib/" + filename, "create_game");
                        if (dl.getLibName != nullptr)
                            this->_games.push_back(dl.getLibName());
                        else
                            this->_games.push_back(parseLibName(filename));
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
    //TODO
}

void Arcade::display(std::shared_ptr<IDisplayable> displayable) {
    this->_driver->display(displayable);
}

void Arcade::flipFrame() {
    this->_driver->flipFrame();
}

void Arcade::bindEvent(IEvent::EventType type, EventKey key, EventCallback callback) {
    this->_driver->bindEvent(type, key, callback);
}

std::list<std::string> Arcade::getGames() const {
    return this->_games;
}

std::list<std::string> Arcade::getDrivers() const {
    return this->_drivers;
}

void Arcade::run() {
    while (true) {
        if (this->_game != nullptr) {
            this->_game->run();
        }
    }
}