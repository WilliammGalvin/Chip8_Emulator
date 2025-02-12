//
// Created by liamg on 2025-01-30.
//

#ifndef INSTRUCTION_HPP
#define INSTRUCTION_HPP
#include <cstdint>

namespace emulator {

    struct Instruction {
        uint16_t opcode;
        uint8_t instr;
    };

}

#endif //INSTRUCTION_HPP
