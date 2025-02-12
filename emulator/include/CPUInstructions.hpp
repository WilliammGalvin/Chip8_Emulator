//
// Created by liamg on 2025-01-30.
//

#ifndef CPUINSTRUCTIONS_HPP
#define CPUINSTRUCTIONS_HPP

#include "CPU.hpp"

namespace emulator {

    class CPUInstructions {
        CPU* _cpu;

    public:
        CPUInstructions(CPU* cpu);

        void INSTR_00EE();
        void INSTR_00E0();
        void INSTR_0();

        void INSTR_1NNN();
        void INSTR_2NNN();
        void INSTR_3XNN();
        void INSTR_4XNN();
        void INSTR_5XY0();
        void INSTR_6XNN();
        void INSTR_7XNN();

        void INSTR_8XY0();
        void INSTR_8XY1();
        void INSTR_8XY2();
        void INSTR_8XY3();
        void INSTR_8XY4();
        void INSTR_8XY5();
        void INSTR_8XY6();
        void INSTR_8XY7();
        void INSTR_8XYE();
        void INSTR_8();

        void INSTR_9XY0();
        void INSTR_ANNN();
        void INSTR_BNNN();
        void INSTR_CXNN();
        void INSTR_DXYN();

        void INSTR_EX9E();
        void INSTR_EXA1();
        void INSTR_E();

        void INSTR_FX07();
        void INSTR_FX0A();
        void INSTR_FX15();
        void INSTR_FX18();
        void INSTR_FX1E();
        void INSTR_FX29();
        void INSTR_FX33();
        void INSTR_FX55();
        void INSTR_FX65();
        void INSTR_F();
    };

}

#endif //CPUINSTRUCTIONS_HPP
