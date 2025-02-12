//
// Created by liamg on 2025-02-12.
//

#ifndef COMMANDINFODISPLAY_HPP
#define COMMANDINFODISPLAY_HPP
#include "Display.hpp"

namespace emulator {

    class CommandInfoDisplay final : public Display {
    public:
        CommandInfoDisplay(sf::RenderWindow* window, sf::Vector2f position, sf::Vector2f size);

        void onUpdate() override;
        void onRender() override;
        void onEvent(const sf::Event& event) override;
    };

}

#endif //COMMANDINFODISPLAY_HPP
