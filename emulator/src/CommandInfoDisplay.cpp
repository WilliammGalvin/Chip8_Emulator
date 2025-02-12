//
// Created by liamg on 2025-02-12.
//

#include "../include/CommandInfoDisplay.hpp"
#include "../include/EmulatorHistory.hpp"

#include <sstream>
#include <GL/gl.h>

namespace emulator {

    CommandInfoDisplay::CommandInfoDisplay(sf::RenderWindow *window, sf::Vector2f position, sf::Vector2f size)
        : Display(window, position, size) {}

    void CommandInfoDisplay::onUpdate() {}

    void CommandInfoDisplay::onRender() {
        Display::onRender();

        sf::Text text;
        text.setFont(getFont());
        text.setCharacterSize(22);
        text.setFillColor(sf::Color::White);

        sf::Vector2f initPos = getPos() + sf::Vector2f{ 10.0f, 5.0f };
        int historySize = EmulatorHistory::getHistory().size();

        glEnable(GL_SCISSOR_TEST);
        glScissor(getPos().x, getPos().y + getSize().y * 1.05, getSize().x, getSize().y);

        for (int i = historySize; i > 0; i--) {
            if (i == historySize) {
                sf::RectangleShape rect;
                rect.setFillColor(sf::Color(162, 155, 254));
                rect.setPosition(initPos + sf::Vector2f{ -4.0f, 4.0f });
                rect.setSize({ getSize().x - 12.0f, 22.0f });
                getWindow().draw(rect);
            }

            std::stringstream stream;
            stream << std::hex << EmulatorHistory::getHistory()[i - 1];

            text.setString("Executing opcode: 0x" + stream.str());
            text.setPosition(initPos + sf::Vector2f{ 0.0f, 22.0f * (historySize - i) });
            getWindow().draw(text);
        }

        glDisable(GL_SCISSOR_TEST);
    }

    void CommandInfoDisplay::onEvent(const sf::Event &event) {}

}
