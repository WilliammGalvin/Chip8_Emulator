//
// Created by liamg on 2025-02-12.
//

#include "../include/RegisterDisplay.hpp"

#include <iostream>
#include <sstream>

#include "../include/CPU.hpp"

namespace emulator {

    RegisterDisplay::RegisterDisplay(sf::RenderWindow *window, CPU* cpu, sf::Vector2f position, sf::Vector2f size)
        : Display(window, position, size), _cpu(cpu) {}

    RegisterDisplay::~RegisterDisplay() {
        delete _cpu;
    }


    void RegisterDisplay::onUpdate() {}

    void RegisterDisplay::onRender() {
        Display::onRender();

        sf::Text text;
        text.setFont(getFont());
        text.setCharacterSize(22);
        text.setFillColor(sf::Color::White);

        sf::Vector2f initPos = getPos() + sf::Vector2f{ 10.0f, 5.0f };

        for (int i = 0; i <= 0xF; i++) {
            std::stringstream stream;
            stream << std::hex << i;

            std::string hexRegister = stream.str();
            std::string registerValue = std::to_string(_cpu->getRegisterValue(i));

            text.setString("V" + hexRegister + " = " + registerValue);
            text.setPosition(initPos + sf::Vector2f{ 0.0f, 22.0f * i });
            getWindow().draw(text);
        }

        std::vector<std::string> otherRegisterInfo = {
            "DT = " + std::to_string(_cpu->getDelayTimer()),
            "ST = " + std::to_string(_cpu->getSoundTimer()),
            "I = " + std::to_string(_cpu->getIndexRegister()),
            "PC = " + std::to_string(_cpu->getProgramCounter()),
            "SP = " + std::to_string(_cpu->getStackPointer())
        };

        initPos += sf::Vector2f{ 100.0f, 0.0f };

        for (int i = 0; i < otherRegisterInfo.size(); i++) {
            text.setString(otherRegisterInfo[i]);
            text.setPosition(initPos + sf::Vector2f{ 0.0f, 22.0f * i });
            getWindow().draw(text);
        }
    }

    void RegisterDisplay::onEvent(const sf::Event &event) {}

}
