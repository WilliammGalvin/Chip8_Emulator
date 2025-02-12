#include <iostream>
#include <SFML/Window/Event.hpp>

#include "emulator/include/CommandInfoDisplay.hpp"
#include "emulator/include/ConsoleDisplay.hpp"
#include "emulator/include/EmulatorConsole.hpp"
#include "emulator/include/EmulatorDisplay.hpp"
#include "emulator/include/RegisterDisplay.hpp"

using namespace emulator;

int main() {
    const float padding = 12.0f;
    const sf::Vector2f emulatorSize = { PIXEL_SIZE * WIDTH, PIXEL_SIZE * HEIGHT };

    sf::RenderWindow window(
        sf::VideoMode(
            emulatorSize.x * 1.5 + padding * 3,
            emulatorSize.y * 2 + padding * 3
            ),
        "Chip-8 Emulator",
        sf::Style::Titlebar | sf::Style::Close
    );

    Display::loadFont();
    EmulatorConsole::print("Chip-8 emulator by William Galvin");

    CPU cpu = CPU();

    auto emulatorView = new EmulatorDisplay(
            "assets/apps/octojam2title.ch8", &window, &cpu,
            { padding, padding },
            { emulatorSize.x, emulatorSize.y }
            );

    const std::vector<Display*> views = {
        emulatorView,
        new ConsoleDisplay(
            &window,
            { padding, emulatorSize.y + padding * 2 },
            { emulatorSize.x, emulatorSize.y }
        ),
        new CommandInfoDisplay(
            &window,
            { emulatorSize.x + padding * 2, padding },
            { emulatorSize.x / 2, emulatorSize.y }
        ),
        new RegisterDisplay(
            &window, &cpu,
            { emulatorSize.x + padding * 2, emulatorSize.y + padding * 2 },
            { emulatorSize.x / 2, emulatorSize.y }
        )
    };

    cpu.setDisplay(emulatorView);

    while (window.isOpen()) {
        sf::Event event{};

        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            } else {
                for (auto& view : views) {
                    view->onEvent(event);
                }
            }
        }

        for (auto& view : views) {
            view->onUpdate();
        }

        window.clear(sf::Color(44, 56, 77));

        for (auto& view : views) {
            view->onRender();
        }

        window.display();
    }

    return 0;
}