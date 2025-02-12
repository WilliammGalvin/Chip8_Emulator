//
// Created by liamg on 2025-01-30.
//


#include <chrono>
#include <iostream>
#include <fstream>

#include "../include/CPU.hpp"
#include "../include/EmulatorDisplay.hpp"
#include "../include/CPUInstructions.hpp"
#include "../include/EmulatorConsole.hpp"
#include "../include/EmulatorHistory.hpp"

namespace emulator {

    void CPU::fetch() {
        _opcode = _memory[_pc] << 8 | _memory[_pc + 1];
        _pc += 2;

        EmulatorHistory::addToHistory(_opcode);
    }

    void CPU::decode() {
        _instr = _opcode >> 12;
        _v_x = (_opcode & 0x0F00) >> 8;
        _v_y = (_opcode & 0x00F0) >> 4;
        _NNN = _opcode & 0x0FFF;
        _NN = _opcode & 0x00FF;
        _N = _opcode & 0x000F;

        if (_instr == 0x0) _instructions->INSTR_0();
        else if (_instr == 0x1) _instructions->INSTR_1NNN();
        else if (_instr == 0x2) _instructions->INSTR_2NNN();
        else if (_instr == 0x3) _instructions->INSTR_3XNN();
        else if (_instr == 0x4) _instructions->INSTR_4XNN();
        else if (_instr == 0x5) _instructions->INSTR_5XY0();
        else if (_instr == 0x6) _instructions->INSTR_6XNN();
        else if (_instr == 0x7) _instructions->INSTR_7XNN();
        else if (_instr == 0x8) _instructions->INSTR_8();
        else if (_instr == 0x9) _instructions->INSTR_9XY0();
        else if (_instr == 0xA) _instructions->INSTR_ANNN();
        else if (_instr == 0xB) _instructions->INSTR_BNNN();
        else if (_instr == 0xC) _instructions->INSTR_CXNN();
        else if (_instr == 0xD) _instructions->INSTR_DXYN();
        else if (_instr == 0xE) _instructions->INSTR_E();
        else if (_instr == 0xF) _instructions->INSTR_F();
    }

    CPU::CPU() :
    _instructions(new CPUInstructions(this)),
    _randGen(std::chrono::system_clock::now().time_since_epoch().count())
    {
        _pc = ROM_START;
    }

    CPU::~CPU() {
        delete _display;
        delete _instructions;
    }

    void CPU::loadFontIntoMemory(const uint8_t* fontSet, int fontSetSize) {
        for (int i = 0; i < fontSetSize; i++) {
            _memory[FONT_SET_START + i] = fontSet[i];
        }

        std::cout << "Font loaded successfully." << std::endl;
    }

    void CPU::loadRomIntoMemory(const char* fileName) {
        std::ifstream file(fileName, std::ios::binary | std::ios::ate);

        if (!file.is_open()) {
            throw std::runtime_error("Failed to open file.");
        }

        std::streampos size = file.tellg();
        char* buffer = new char[size];

        file.seekg(0, std::ios::beg);
        file.read(buffer, size);
        file.close();

        for (long i = 0; i < size; i++) {
            _memory[ROM_START + i] = buffer[i];
        }

        delete[] buffer;
        EmulatorConsole::print(std::to_string(size) + " bytes");
    }

    void CPU::runCycle() {
        fetch();
        decode();
    }

    int CPU::getRegisterValue(int index) const {
        return _registers[index];
    }

    int CPU::getDelayTimer() const {
        return _delayTimer;
    }

    int CPU::getSoundTimer() const {
        return _soundTimer;
    }

    int CPU::getIndexRegister() const {
        return _index;
    }

    int CPU::getProgramCounter() const {
        return _pc;
    }

    int CPU::getStackPointer() const {
        return _sp;
    }

    void CPU::setDisplay(EmulatorDisplay* display) {
        _display = display;
    }

    void CPU::setKeyState(int keyIndex, uint8_t state) {
        _keypad[keyIndex] = state;
    }

    uint8_t CPU::genRandByte() {
        return _randByte(_randGen);
    }

}
