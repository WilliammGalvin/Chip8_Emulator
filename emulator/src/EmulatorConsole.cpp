//
// Created by liamg on 2025-02-12.
//

#include "../include/EmulatorConsole.hpp"

#include <iostream>

namespace emulator {

    std::vector<std::string> EmulatorConsole::_console = {};

    void EmulatorConsole::print(const std::string &message) {
        // Console max of 25 lines
        if (_console.size() + 1 > 25)
            _console.erase(_console.begin());

        std::string msg = message;

        for (auto& c : msg) {
            c = static_cast<char>(std::toupper(c));
        }

        std::cout << "CONSOLE: " << msg << std::endl;
        _console.push_back(msg);
    }

    void EmulatorConsole::clear() {
        _console.clear();
    }

    const std::vector<std::string> &EmulatorConsole::getConsole() {
        return _console;
    }

}
