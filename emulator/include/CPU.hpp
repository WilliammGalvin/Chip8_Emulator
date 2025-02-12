//
// Created by liamg on 2025-01-30.
//

#ifndef CPU_HPP
#define CPU_HPP

#define FONT_SET_START 0x50
#define ROM_START 0x200

#include <cstdint>
#include <random>

#include "EmulatorDisplay.hpp"

namespace emulator {
    class EmulatorDisplay;
    class CPUInstructions;

    class CPU {
        friend class CPUInstructions;

        EmulatorDisplay* _display;
        CPUInstructions* _instructions;

        uint8_t _registers[16]{};
        uint8_t _memory[4096]{};
        uint16_t _index{};
        uint16_t _pc{};
        uint16_t _stack[16]{};
        uint8_t _sp{};

        uint8_t _delayTimer{};
        uint8_t _soundTimer{};
        uint8_t _keypad[16]{};

        uint16_t _opcode{};
        int _instr, _v_x, _v_y, _N, _NN, _NNN;

        std::default_random_engine _randGen;
        std::uniform_int_distribution<uint8_t> _randByte{ 0, 255 };

        void fetch();
        void decode();

    public:
        CPU();
        ~CPU();

        void loadFontIntoMemory(const uint8_t* fontSet, int fontSetSize);
        void loadRomIntoMemory(const char* fileName);
        void runCycle();

        void setDisplay(EmulatorDisplay* display);
        void setKeyState(int keyIndex, uint8_t state);

        int getRegisterValue(int index) const;
        int getDelayTimer() const;
        int getSoundTimer() const;
        int getIndexRegister() const;
        int getProgramCounter() const;
        int getStackPointer() const;

        uint8_t genRandByte();
    };

}

#endif //CPU_HPP
