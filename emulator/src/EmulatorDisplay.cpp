//
// Created by liamg on 2025-01-30.
//

#include "../include/EmulatorDisplay.hpp"

#include <filesystem>
#include <iostream>

#include "../include/CPU.hpp"
#include "../include/Display.hpp"

#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Window/Event.hpp>

#include "../include/EmulatorConsole.hpp"

namespace emulator {

    void EmulatorDisplay::initializeKeyMap() {
        _keyMap = {
            {sf::Keyboard::Num1, 0x1},  // 1
            {sf::Keyboard::Num2, 0x2},  // 2
            {sf::Keyboard::Num3, 0x3},  // 3
            {sf::Keyboard::Num4, 0xC},  // C
            {sf::Keyboard::Q, 0x4},     // 4
            {sf::Keyboard::W, 0x5},     // 5
            {sf::Keyboard::E, 0x6},     // 6
            {sf::Keyboard::R, 0xD},     // D
            {sf::Keyboard::A, 0x7},     // 7
            {sf::Keyboard::S, 0x8},     // 8
            {sf::Keyboard::D, 0x9},     // 9
            {sf::Keyboard::F, 0xE},     // E
            {sf::Keyboard::Z, 0xA},     // A
            {sf::Keyboard::X, 0x0},     // 0
            {sf::Keyboard::C, 0xB},     // B
            {sf::Keyboard::V, 0xF}      // F
        };

        std::cout << "Key map initialized." << std::endl;
    }

    void EmulatorDisplay::loadFont() {
        const uint8_t fontSet[FONT_SET_SIZE] =
        {
            0xF0, 0x90, 0x90, 0x90, 0xF0, // 0
            0x20, 0x60, 0x20, 0x20, 0x70, // 1
            0xF0, 0x10, 0xF0, 0x80, 0xF0, // 2
            0xF0, 0x10, 0xF0, 0x10, 0xF0, // 3
            0x90, 0x90, 0xF0, 0x10, 0x10, // 4
            0xF0, 0x80, 0xF0, 0x10, 0xF0, // 5
            0xF0, 0x80, 0xF0, 0x90, 0xF0, // 6
            0xF0, 0x10, 0x20, 0x40, 0x40, // 7
            0xF0, 0x90, 0xF0, 0x90, 0xF0, // 8
            0xF0, 0x90, 0xF0, 0x10, 0xF0, // 9
            0xF0, 0x90, 0xF0, 0x90, 0x90, // A
            0xE0, 0x90, 0xE0, 0x90, 0xE0, // B
            0xF0, 0x80, 0x80, 0x80, 0xF0, // C
            0xE0, 0x90, 0x90, 0x90, 0xE0, // D
            0xF0, 0x80, 0xF0, 0x80, 0xF0, // E
            0xF0, 0x80, 0xF0, 0x80, 0x80  // F
        };

        _cpu->loadFontIntoMemory(fontSet, FONT_SET_SIZE);
    }

    void EmulatorDisplay::onEvent(const sf::Event& event) {
        if (event.type == sf::Event::KeyPressed) {
            sf::Keyboard::Key key = event.key.code;

            if (_keyMap.contains(key))
                _cpu->setKeyState(_keyMap.at(key), 1);
        }

        if (event.type == sf::Event::KeyReleased) {
            sf::Keyboard::Key key = event.key.code;

            if (_keyMap.contains(key))
                _cpu->setKeyState(_keyMap.at(key), 0);
        }
    }

    void EmulatorDisplay::onRender() {
        Display::onRender();

        sf::RectangleShape rect;
        rect.setSize(sf::Vector2f(PIXEL_SIZE, PIXEL_SIZE));

        for (int y = 0; y < HEIGHT; y++) {
            for (int x = 0; x < WIDTH; x++) {
                auto pixel = _display[y * WIDTH + x];

                if (pixel == 0xFFFFFFFF)
                    rect.setFillColor(sf::Color::White);
                else if (pixel == 0x00000000)
                    rect.setFillColor(sf::Color::Black);
                else
                    rect.setFillColor(sf::Color::Red);

                rect.setPosition(sf::Vector2f{
                    static_cast<float>(x) * PIXEL_SIZE,
                    static_cast<float>(y) * PIXEL_SIZE
                } + getPos());


                getWindow().draw(rect);
            }
        }
    }

    void EmulatorDisplay::onUpdate() {
        _cpu->runCycle();
    }

    EmulatorDisplay::EmulatorDisplay(
        const char* romPath, sf::RenderWindow* window, CPU* cpu, sf::Vector2f position, sf::Vector2f size
        ) : Display(window, position, size), _cpu(cpu) {
        initializeKeyMap();

        std::filesystem::path path = romPath;
        EmulatorConsole::print("Loading " + path.filename().string());

        _cpu->loadRomIntoMemory(romPath);
        loadFont();
    }

    EmulatorDisplay::~EmulatorDisplay() {
        delete _cpu;
    }

    uint32_t* EmulatorDisplay::getDisplay() {
        return _display;
    }

}
