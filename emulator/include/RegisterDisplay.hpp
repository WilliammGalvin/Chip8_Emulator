//
// Created by liamg on 2025-02-12.
//

#ifndef REGISTERDISPLAY_HPP
#define REGISTERDISPLAY_HPP

#include "CPU.hpp"
#include "Display.hpp"

namespace emulator {
    class CPU;

    class RegisterDisplay final : public Display {
        CPU* _cpu;

    public:
        RegisterDisplay(sf::RenderWindow* window, CPU* cpu, sf::Vector2f position, sf::Vector2f size);
        ~RegisterDisplay() override;

        void onUpdate() override;
        void onRender() override;
        void onEvent(const sf::Event& event) override;
    };

}

#endif //REGISTERDISPLAY_HPP
