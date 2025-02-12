//
// Created by liamg on 2025-02-12.
//

#include "../include/ConsoleDisplay.hpp"
#include <SFML/Graphics.hpp>

#include "../include/EmulatorConsole.hpp"

namespace emulator {

    ConsoleDisplay::ConsoleDisplay(sf::RenderWindow *window, sf::Vector2f position, sf::Vector2f size)
        : Display(window, position, size) {}

    void ConsoleDisplay::onUpdate() {}

    void ConsoleDisplay::onRender() {
        Display::onRender();

        sf::Text consoleText;
        consoleText.setFont(getFont());
        consoleText.setCharacterSize(22);
        consoleText.setFillColor(sf::Color::White);

        sf::Vector2f initPos = getPos() + sf::Vector2f{ 10.0f, 5.0f };

        for (int i = 0; i < EmulatorConsole::getConsole().size(); i++) {
            std::string msg = EmulatorConsole::getConsole()[i];

            consoleText.setString(msg);
            consoleText.setPosition(initPos + sf::Vector2f{ 0.0f, 24.0f * i });
            getWindow().draw(consoleText);
        }
    }

    void ConsoleDisplay::onEvent(const sf::Event &event) {}

}
