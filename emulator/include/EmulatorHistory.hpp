//
// Created by liamg on 2025-02-12.
//

#ifndef EMULATORHISTORY_HPP
#define EMULATORHISTORY_HPP

#include <vector>

namespace emulator {

    class EmulatorHistory {
        static std::vector<int> _cmdHistory;

    public:
        static void addToHistory(int opcode);

        static const std::vector<int>& getHistory();
    };

}

#endif //EMULATORHISTORY_HPP
