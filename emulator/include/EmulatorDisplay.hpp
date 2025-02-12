//
// Created by liamg on 2025-01-30.
//

#ifndef EMULATOR_DISPLAY_HPP
#define EMULATOR_DISPLAY_HPP

#define WIDTH 64
#define HEIGHT 32
#define PIXEL_SIZE 12
#define FONT_SET_SIZE 80

#include <cstdint>
#include <map>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Window/Keyboard.hpp>
#include <SFML/Window/Window.hpp>

#include "Display.hpp"

namespace emulator {
    class CPU;

    class EmulatorDisplay final : public Display {
        uint32_t _display[WIDTH * HEIGHT]{};
        CPU* _cpu;
        std::map<sf::Keyboard::Key, int> _keyMap{};

        void initializeKeyMap();
        void loadFont();

    public:
        EmulatorDisplay(const char* romPath, sf::RenderWindow* window, CPU* cpu, sf::Vector2f position, sf::Vector2f size);
        ~EmulatorDisplay() override;

        void onUpdate() override;
        void onRender() override;
        void onEvent(const sf::Event& event) override;

        uint32_t* getDisplay();
    };

}

#endif //EMULATOR_DISPLAY_HPP
