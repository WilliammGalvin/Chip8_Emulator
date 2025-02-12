//
// Created by liamg on 2025-02-10.
//

#include "../include/Display.hpp"

#include <iostream>
#include <SFML/Graphics/RectangleShape.hpp>

#include "../include/EmulatorConsole.hpp"

namespace emulator {

    sf::Font Display::_font{};

    Display::Display(sf::RenderWindow* window, sf::Vector2f position, sf::Vector2f size) :
        _window(window), _pos(position), _size(size) {
        _pos = _pos + _padding;
    }

    void Display::onRender() {
        sf::RectangleShape border;

        // Top
        border.setFillColor(sf::Color(0, 0, 0));
        border.setPosition(_pos - _padding);
        border.setSize({ _size.x + _padding.x * 2.0f, _padding.y });
        getWindow().draw(border);

        // Left
        border.setSize({ _padding.x, _size.y + _padding.y * 2.0f });
        getWindow().draw(border);

        // Right
        border.setFillColor(sf::Color(77, 96, 130));
        border.setPosition(_pos + sf::Vector2f(_size.x, 0));
        border.setSize({ _padding.x, _size.y + _padding.y });
        getWindow().draw(border);

        // Bottom
        border.setPosition(_pos + sf::Vector2f(0, _size.y));
        border.setSize({ _size.x + _padding.x, _padding.y });
        getWindow().draw(border);
    }

    void Display::loadFont() {
        if (!_font.loadFromFile("assets/fonts/VT323-Regular.ttf")) {
            std::cerr << "Failed to load font." << std::endl;
            exit(1);
        }
    }

    sf::Font& Display::getFont() {
        return _font;
    }


    const sf::Vector2f& Display::getPos() const {
        return _pos;
    }

    const sf::Vector2f &Display::getSize() const {
        return _size;
    }


    sf::RenderWindow& Display::getWindow() {
        return *_window;
    }

}
