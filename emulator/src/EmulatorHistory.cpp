//
// Created by liamg on 2025-02-12.
//

#include "../include/EmulatorHistory.hpp"

namespace emulator {

    std::vector<int> EmulatorHistory::_cmdHistory = {};

    void EmulatorHistory::addToHistory(int opcode) {
        if (_cmdHistory.size() + 1 > 35)
            _cmdHistory.erase(_cmdHistory.begin());

        _cmdHistory.push_back(opcode);
    }

    const std::vector<int>& EmulatorHistory::getHistory() {
        return _cmdHistory;
    }


}