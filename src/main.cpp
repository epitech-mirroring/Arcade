/*
** EPITECH PROJECT, 2024
** Arcade
** File description:
** No file there , just an epitech header example .
** You can even have multiple lines if you want !
*/

#include <iostream>
#include "core/Arcade.hpp"
#include "shared/errors/IError.hpp"
#include <memory>

static void print_usage() {
    std::cout << "USAGE" << std::endl;
    std::cout << "\t./arcade path_to_graphical_library" << std::endl;
    std::cout << "DESCRIPTION" << std::endl;
    std::cout << "\tpath_to_graphical_library\tThe path to the graphical library you want to use at first" << std::endl;
}

int main(int argc, char **argv) {
    if (argc != 2) {
        print_usage();
        return 84;
    }
    try {
        Arcade arcade = Arcade(argv[1]);
        arcade.run();
    } catch (IError &e) {
        std::cerr << e.what() << std::endl;
        return e.getCode();
    } catch (...) {
        std::cerr << "An error occurred" << std::endl;
        return 84;
    }
    return 0;
}
