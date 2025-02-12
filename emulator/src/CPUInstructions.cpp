//
// Created by liamg on 2025-01-30.
//

#include "../include/CPUInstructions.hpp"

#include <iostream>
#include <string.h>

namespace emulator {

    CPUInstructions::CPUInstructions(CPU* cpu) : _cpu(cpu) {}

    void CPUInstructions::INSTR_00E0() {
        for (int y = 0; y < HEIGHT; y++) {
            for (int x = 0; x < WIDTH; x++) {
                _cpu->_display->getDisplay()[y * WIDTH + x] = 0x00000000;
            }
        }
    }

    void CPUInstructions::INSTR_00EE() {
        _cpu->_sp--;
        _cpu->_pc = _cpu->_stack[_cpu->_sp];
    }


    void CPUInstructions::INSTR_0() {
        if (_cpu->_opcode == 0x00E0)
            INSTR_00E0();

        if (_cpu->_opcode == 0x00EE)
            INSTR_00EE();
    }

    void CPUInstructions::INSTR_1NNN() {
        _cpu->_pc = _cpu->_NNN;
    }

    void CPUInstructions::INSTR_2NNN() {
        _cpu->_stack[_cpu->_sp] = _cpu->_pc;
        _cpu->_sp++;
        _cpu->_pc = _cpu->_NNN;
    }

    void CPUInstructions::INSTR_3XNN() {
        if (_cpu->_registers[_cpu->_v_x] == _cpu->_NN)
            _cpu->_pc += 2;
    }

    void CPUInstructions::INSTR_4XNN() {
        if (_cpu->_registers[_cpu->_v_x] != _cpu->_NN)
            _cpu->_pc += 2;
    }

    void CPUInstructions::INSTR_5XY0() {
        if (_cpu->_registers[_cpu->_v_x] == _cpu->_registers[_cpu->_v_y])
            _cpu->_pc += 2;
    }

    void CPUInstructions::INSTR_6XNN() {
        _cpu->_registers[_cpu->_v_x] = _cpu->_NN;
    }

    void CPUInstructions::INSTR_7XNN() {
        _cpu->_registers[_cpu->_v_x] += _cpu->_NN;
    }

    void CPUInstructions::INSTR_8XY0() {
        _cpu->_registers[_cpu->_v_x] = _cpu->_registers[_cpu->_v_y];
    }

    void CPUInstructions::INSTR_8XY1() {
        _cpu->_registers[_cpu->_v_x] |= _cpu->_registers[_cpu->_v_y];
    }

    void CPUInstructions::INSTR_8XY2() {
        _cpu->_registers[_cpu->_v_x] &= _cpu->_registers[_cpu->_v_y];
    }

    void CPUInstructions::INSTR_8XY3() {
        _cpu->_registers[_cpu->_v_x] ^= _cpu->_registers[_cpu->_v_y];
    }

    void CPUInstructions::INSTR_8XY4() {
        uint16_t sum = _cpu->_registers[_cpu->_v_x] + _cpu->_registers[_cpu->_v_y];
        _cpu->_registers[_cpu->_v_x] = sum & 0xFF;
        _cpu->_registers[0xF] = sum > 0xFF;
    }

    void CPUInstructions::INSTR_8XY5() {
        _cpu->_registers[0xF] = _cpu->_registers[_cpu->_v_x] > _cpu->_registers[_cpu->_v_y];
        _cpu->_registers[_cpu->_v_x] -= _cpu->_registers[_cpu->_v_y];
    }

    void CPUInstructions::INSTR_8XY6() {
        _cpu->_registers[0xF] = _cpu->_registers[_cpu->_v_x] & 0x1;
        _cpu->_registers[_cpu->_v_x] >>= 1;
    }

    void CPUInstructions::INSTR_8XY7() {
        _cpu->_registers[0xF] = _cpu->_registers[_cpu->_v_y] > _cpu->_registers[_cpu->_v_x];
        _cpu->_registers[_cpu->_v_x] = _cpu->_registers[_cpu->_v_y] - _cpu->_registers[_cpu->_v_x];
    }

    void CPUInstructions::INSTR_8XYE() {
        _cpu->_registers[0xF] = (_cpu->_registers[_cpu->_v_x] & 0x80) >> 7;
        _cpu->_registers[_cpu->_v_x] <<= 1;
    }

    void CPUInstructions::INSTR_8() {
        if (_cpu->_N == 0x0)
            INSTR_8XY0();

        if (_cpu->_N == 0x1)
            INSTR_8XY0();

        if (_cpu->_N == 0x2)
            INSTR_8XY0();

        if (_cpu->_N == 0x3)
            INSTR_8XY0();

        if (_cpu->_N == 0x4)
            INSTR_8XY0();

        if (_cpu->_N == 0x5)
            INSTR_8XY0();

        if (_cpu->_N == 0x6)
            INSTR_8XY0();

        if (_cpu->_N == 0x7)
            INSTR_8XY0();

        if (_cpu->_N == 0xE)
            INSTR_8XY0();
    }

    void CPUInstructions::INSTR_9XY0() {
        if (_cpu->_registers[_cpu->_v_x] != _cpu->_registers[_cpu->_v_y])
            _cpu->_pc += 2;
    }

    void CPUInstructions::INSTR_ANNN() {
        _cpu->_index = _cpu->_NNN;
    }

    void CPUInstructions::INSTR_BNNN() {
        _cpu->_pc = _cpu->_registers[0] + _cpu->_NNN;
    }

    void CPUInstructions::INSTR_CXNN() {
        _cpu->_registers[_cpu->_v_x] = _cpu->genRandByte() & _cpu->_NN;
    }

    void CPUInstructions::INSTR_DXYN() {
        uint8_t xPos = _cpu->_registers[_cpu->_v_x] % WIDTH;
        uint8_t yPos = _cpu->_registers[_cpu->_v_y] % HEIGHT;
        _cpu->_registers[0xF] = 0;

        for (int row = 0; row < _cpu->_N; row++) {
            uint8_t spriteByte = _cpu->_memory[_cpu->_index + row];

            for (int col = 0; col < 8; col++) {
                uint8_t spritePixel = spriteByte & (0x80 >> col);
                uint32_t* screenPixel = &_cpu->_display->getDisplay()[(yPos + row) * WIDTH + (xPos + col)];

                if (spritePixel) {
                    if (*screenPixel == 0xFFFFFFFF)
                        _cpu->_registers[0xF] = 1;

                    *screenPixel ^= 0xFFFFFFFF;
                }
            }
        }
    }

    void CPUInstructions::INSTR_EX9E() {
        if (_cpu->_keypad[_cpu->_registers[_cpu->_v_x]])
            _cpu->_pc += 2;
    }

    void CPUInstructions::INSTR_EXA1() {
        if (!_cpu->_keypad[_cpu->_registers[_cpu->_v_x]])
            _cpu->_pc += 2;
    }

    void CPUInstructions::INSTR_E() {
        if (_cpu->_NN == 0x9E)
            INSTR_EX9E();

        if (_cpu->_NN == 0xA1)
            INSTR_EXA1();
    }

    void CPUInstructions::INSTR_FX07() {
        _cpu->_registers[_cpu->_v_x] = _cpu->_delayTimer;
    }

    void CPUInstructions::INSTR_FX0A() {
        bool keyPressed = false;

        for (int i = 0; i < 16; i++) {
            if (_cpu->_keypad[i]) {
                _cpu->_registers[_cpu->_v_x] = i;
                keyPressed = true;
                break;
            }
        }

        if (!keyPressed)
            _cpu->_pc -= 2;
    }

    void CPUInstructions::INSTR_FX15() {
        _cpu->_delayTimer = _cpu->_registers[_cpu->_v_x];
    }

    void CPUInstructions::INSTR_FX18() {
        _cpu->_soundTimer = _cpu->_registers[_cpu->_v_x];
    }

    void CPUInstructions::INSTR_FX1E() {
        _cpu->_index += _cpu->_registers[_cpu->_v_x];
    }

    void CPUInstructions::INSTR_FX29() {
        _cpu->_index = FONT_SET_START + _cpu->_registers[_cpu->_v_x] * 5;
    }

    void CPUInstructions::INSTR_FX33() {
        _cpu->_memory[_cpu->_index] = _cpu->_registers[_cpu->_v_x] / 100;
        _cpu->_memory[_cpu->_index + 1] = (_cpu->_registers[_cpu->_v_x] / 10) % 10;
        _cpu->_memory[_cpu->_index + 2] = _cpu->_registers[_cpu->_v_x] % 10;
    }

    void CPUInstructions::INSTR_FX55() {
        for (int i = 0; i <= _cpu->_v_x; i++) {
            _cpu->_memory[_cpu->_index + i] = _cpu->_registers[i];
        }
    }

    void CPUInstructions::INSTR_FX65() {
        for (int i = 0; i <= _cpu->_v_x; i++) {
            _cpu->_registers[i] = _cpu->_memory[_cpu->_index + i];
        }
    }

    void CPUInstructions::INSTR_F() {
        if (_cpu->_NN == 0x07)
            INSTR_FX07();

        if (_cpu->_NN == 0x0A)
            INSTR_FX0A();

        if (_cpu->_NN == 0x15)
            INSTR_FX15();

        if (_cpu->_NN == 0x18)
            INSTR_FX18();

        if (_cpu->_NN == 0x1E)
            INSTR_FX1E();

        if (_cpu->_NN == 0x29)
            INSTR_FX29();

        if (_cpu->_NN == 0x33)
            INSTR_FX33();

        if (_cpu->_NN == 0x55)
            INSTR_FX55();

        if (_cpu->_NN == 0x65)
            INSTR_FX65();
    }

}
