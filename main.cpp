#include <chrono>
#include <SFML/Graphics.hpp>
#include <fstream>
#include <iostream>
#include <random>
#include <cstring>

#define WIDTH 64
#define HEIGHT 32
#define PIXEL_SIZE 10
#define FONTSET_SIZE 80

uint8_t registers[16]{};
uint8_t memory[4096]{};
uint16_t index{};
uint16_t pc{};
uint16_t stack[16]{};
uint8_t sp{};

uint8_t delayTimer{};
uint8_t soundTimer{};
uint8_t keypad[16]{};

uint16_t opcode{};
uint32_t display[WIDTH * HEIGHT]{};

std::default_random_engine randGen;
std::uniform_int_distribution<uint8_t> randByte{ 0, 255 };

void loadROM(const char* fileName) {
    std::ifstream file(fileName, std::ios::binary | std::ios::ate);

    if (!file.is_open()) {
        throw std::runtime_error("Failed to open file.");
    }

    std::streampos size = file.tellg();
    char* buffer = new char[size];

    file.seekg(0, std::ios::beg);
    file.read(buffer, size);
    file.close();

    for (long i = 0; i < size; i++) {
        memory[0x200 + i] = buffer[i];
    }

    delete[] buffer;
    std::cout << "ROM has been loaded successfully." << std::endl;
}

void loadFont() {
    uint8_t fontSet[FONTSET_SIZE] =
    {
        0xF0, 0x90, 0x90, 0x90, 0xF0, // 0
        0x20, 0x60, 0x20, 0x20, 0x70, // 1
        0xF0, 0x10, 0xF0, 0x80, 0xF0, // 2
        0xF0, 0x10, 0xF0, 0x10, 0xF0, // 3
        0x90, 0x90, 0xF0, 0x10, 0x10, // 4
        0xF0, 0x80, 0xF0, 0x10, 0xF0, // 5
        0xF0, 0x80, 0xF0, 0x90, 0xF0, // 6
        0xF0, 0x10, 0x20, 0x40, 0x40, // 7
        0xF0, 0x90, 0xF0, 0x90, 0xF0, // 8
        0xF0, 0x90, 0xF0, 0x10, 0xF0, // 9
        0xF0, 0x90, 0xF0, 0x90, 0x90, // A
        0xE0, 0x90, 0xE0, 0x90, 0xE0, // B
        0xF0, 0x80, 0x80, 0x80, 0xF0, // C
        0xE0, 0x90, 0x90, 0x90, 0xE0, // D
        0xF0, 0x80, 0xF0, 0x80, 0xF0, // E
        0xF0, 0x80, 0xF0, 0x80, 0x80  // F
    };

    for (int i = 0; i < FONTSET_SIZE; i++) {
        memory[0x50 + i] = fontSet[i];
    }

    std::cout << "Font loaded successfully." << std::endl;
}

void fetch() {
    opcode = memory[pc] << 8 | memory[pc + 1];
    pc += 2;
}

void decode() {
    const auto instr = opcode >> 12;
    const auto X = (opcode & 0x0F00) >> 8;
    const auto Y = (opcode & 0x00F0) >> 4;
    const auto NNN = opcode & 0x0FFF;
    const auto NN = opcode & 0x00FF;
    const auto N = opcode & 0x000F;

    if (opcode == 0x00E0) {
        memset(display, 0, sizeof(display));
    }

    if (opcode == 0x00EE) {
        sp--;
        pc = stack[sp];
    }

    if (instr == 0x1) {
        pc = NNN;
    }

    if (instr == 0x2) {
        stack[sp] = pc;
        sp++;
        pc = NNN;
    }

    if (instr == 0x3) {
        if (registers[X] == NN)
            pc += 2;
    }

    if (instr == 0x4) {
        if (registers[X] != NN)
            pc += 2;
    }

    if (instr == 0x5) {
        if (registers[X] == registers[Y])
            pc += 2;
    }

    if (instr == 0x6) {
        registers[X] = NN;
    }

    if (instr == 0x7) {
        registers[X] += NN;
    }

    if (instr == 0x8) {
        if (N == 0x0) {
            registers[X] = registers[Y];
        }

        if (N == 0x1) {
            registers[X] |= registers[Y];
        }

        if (N == 0x2) {
            registers[X] &= registers[Y];
        }

        if (N == 0x3) {
            registers[X] ^= registers[Y];
        }

        if (N == 0x4) {
            uint16_t sum = registers[X] + registers[Y];
            registers[0xF] = sum > 0xFF ? 1 : 0;
            registers[X] = sum & 0xFF;
        }

        if (N == 0x5) {
            registers[0xF] = registers[X] > registers[Y] ? 1 : 0;
            registers[X] -= registers[Y];
        }

        if (N == 0x6) {
            registers[0xF] = registers[X] & 0x1;
            registers[X] >>= 1;
        }

        if (N == 0x7) {
            registers[0xF] = registers[Y] > registers[X] ? 1 : 0;
            registers[X] = registers[Y] - registers[X];
        }

        if (N == 0xE) {
            registers[0xF] = (registers[X] & 0x80) >> 7;
            registers[X] <<= 1;
        }
    }

    if (instr == 0x9) {
        if (registers[X] != registers[Y])
            pc += 2;
    }

    if (instr == 0xA) {
        index = NNN;
    }

    if (instr == 0xB) {
        pc = NNN + registers[0];
    }

    if (instr == 0xC) {
        registers[X] = randByte(randGen) & NN;
    }

    if (instr == 0xD) {
        uint8_t xPos = registers[X] % WIDTH;
        uint8_t yPos = registers[Y] % HEIGHT;
        registers[0xF] = 0;

        for (int row = 0; row < N; row++) {
            uint8_t spriteByte = memory[index + row];

            for (int col = 0; col < 8; col++) {
                uint8_t spritePixel = spriteByte & (0x80 >> col);
                uint32_t* screenPixel = &display[(yPos + row) * WIDTH + (xPos + col)];

                if (spritePixel) {
                    if (*screenPixel == 0xFFFFFFFF)
                        registers[0xF] = 1;

                    *screenPixel ^= 0xFFFFFFFF;
                }
            }
        }
    }

    if (instr == 0xE) {
        if (NN == 0x9E) {
            if (keypad[registers[X]])
                pc += 2;
        }

        if (NN == 0xA1) {
            if (!keypad[registers[X]])
                pc += 2;
        }
    }

    if (instr == 0xF) {
        if (NN == 0x07) {
            registers[X] = delayTimer;
        }

        if (NN == 0x15) {
            delayTimer = registers[X];
        }

        if (NN == 0x18) {
            soundTimer = registers[X];
        }

        if (NN == 0x1E) {
            index += registers[X];
        }

        if (NN == 0x0A) {
            bool keyPressed = false;

            for (int i = 0; i < 16; i++) {
                if (keypad[i]) {
                    registers[X] = i;
                    keyPressed = true;
                    break;
                }
            }

            if (!keyPressed)
                pc -= 2;
        }

        if (NN == 0x29) {
            index = 0x50 + registers[X] * 5;
        }

        if (NN == 0x33) {
            memory[index] = registers[X] / 100;
            memory[index + 1] = (registers[X] / 10) % 10;
            memory[index + 2] = registers[X] % 10;
        }

        if (NN == 0x55) {
            for (int i = 0; i <= X; i++) {
                memory[index + i] = registers[i];
            }
        }

        if (NN == 0x65) {
            for (int i = 0; i <= X; i++) {
                registers[i] = memory[index + i];
            }
        }
    }
}

int main() {
    sf::RenderWindow window(
        sf::VideoMode(WIDTH * PIXEL_SIZE, HEIGHT * PIXEL_SIZE),
        "Chip-8 Emulator",
        sf::Style::Titlebar | sf::Style::Close
    );

    // window.setFramerateLimit(60);

    pc = 0x200;

    // loadROM("apps/IBM Logo.ch8");
    // loadROM("apps/octojam1title.ch8");
    // loadROM("apps/octojam2title.ch8");
    loadROM("apps/RPS.ch8");
    loadFont();

    randGen = std::default_random_engine(std::chrono::system_clock::now().time_since_epoch().count());

    const std::map<sf::Keyboard::Key, int> keyMap = {
        {sf::Keyboard::Num1, 0x1},  // 1
        {sf::Keyboard::Num2, 0x2},  // 2
        {sf::Keyboard::Num3, 0x3},  // 3
        {sf::Keyboard::Num4, 0xC},  // C
        {sf::Keyboard::Q, 0x4},     // 4
        {sf::Keyboard::W, 0x5},     // 5
        {sf::Keyboard::E, 0x6},     // 6
        {sf::Keyboard::R, 0xD},     // D
        {sf::Keyboard::A, 0x7},     // 7
        {sf::Keyboard::S, 0x8},     // 8
        {sf::Keyboard::D, 0x9},     // 9
        {sf::Keyboard::F, 0xE},     // E
        {sf::Keyboard::Z, 0xA},     // A
        {sf::Keyboard::X, 0x0},     // 0
        {sf::Keyboard::C, 0xB},     // B
        {sf::Keyboard::V, 0xF}      // F
    };

    while (window.isOpen()) {
        sf::Event event{};

        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();

            if (event.type == sf::Event::KeyPressed) {
                sf::Keyboard::Key key = event.key.code;

                if (keyMap.contains(key))
                    keypad[keyMap.at(key)] = 1;
            }

            if (event.type == sf::Event::KeyReleased) {
                sf::Keyboard::Key key = event.key.code;

                if (keyMap.contains(key))
                    keypad[keyMap.at(key)] = 0;
            }
        }

        fetch();
        decode();

        window.clear(sf::Color::Red);

        sf::RectangleShape rect;
        rect.setSize(sf::Vector2f(PIXEL_SIZE, PIXEL_SIZE));

        for (int y = 0; y < HEIGHT; y++) {
            for (int x = 0; x < WIDTH; x++) {
                auto pixel = display[y * WIDTH + x];

                if (pixel == 0xFFFFFFFF)
                    rect.setFillColor(sf::Color::White);
                else if (pixel == 0x00000000)
                    rect.setFillColor(sf::Color::Black);
                else
                    rect.setFillColor(sf::Color::Red);

                rect.setPosition(sf::Vector2f{
                    static_cast<float>(x) * PIXEL_SIZE,
                    static_cast<float>(y) * PIXEL_SIZE
                });

                window.draw(rect);
            }
        }

        window.display();
    }

    return 0;
}