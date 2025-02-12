//
// Created by liamg on 2025-02-12.
//

#ifndef EMULATORCONSOLE_HPP
#define EMULATORCONSOLE_HPP

#include <vector>
#include <string>

namespace emulator {

    class EmulatorConsole {
        static std::vector<std::string> _console;

    public:
        static void print(const std::string& message);

        static void clear();

        static const std::vector<std::string>& getConsole();
    };

}

#endif //EMULATORCONSOLE_HPP
