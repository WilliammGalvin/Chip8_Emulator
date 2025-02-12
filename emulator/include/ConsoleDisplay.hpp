//
// Created by liamg on 2025-02-12.
//

#ifndef CONSOLEDISPLAY_HPP
#define CONSOLEDISPLAY_HPP
#include "Display.hpp"

namespace emulator {

    class ConsoleDisplay final : public Display {
    public:
        ConsoleDisplay(sf::RenderWindow* window, sf::Vector2f position, sf::Vector2f size);

        void onUpdate() override;
        void onRender() override;
        void onEvent(const sf::Event& event) override;
    };

}

#endif //CONSOLEDISPLAY_HPP
