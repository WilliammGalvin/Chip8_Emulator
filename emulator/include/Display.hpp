//
// Created by liamg on 2025-02-10.
//

#ifndef DISPLAY_HPP
#define DISPLAY_HPP

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/System/Vector2.hpp>
#include <SFML/Graphics.hpp>

namespace emulator {

    class Display {
        sf::RenderWindow* _window;
        sf::Vector2f _pos, _size;

        static sf::Font _font;

        const sf::Vector2f _padding = { 2.0f, 2.0f };

    public:
        Display(sf::RenderWindow* window, sf::Vector2f position, sf::Vector2f size);
        virtual ~Display() = default;

        virtual void onUpdate() {}

        virtual void onRender();

        virtual void onEvent(const sf::Event& event) {}

        static void loadFont();

        sf::Font& getFont();

    protected:
        const sf::Vector2f& getPos() const;
        const sf::Vector2f& getSize() const;
        sf::RenderWindow& getWindow();
    };

}

#endif //DISPLAY_HPP
