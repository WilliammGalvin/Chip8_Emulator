cmake_minimum_required(VERSION 3.30)
project(Chip8_Emulator)

set(CMAKE_CXX_STANDARD 20)

include_directories("C:/SFML_mingw64/SFML-2.6.2/include")
set(SFML_DIR "C:/SFML_mingw64/SFML-2.6.2/lib/cmake/SFML")

find_package(SFML 2.5 COMPONENTS system window graphics REQUIRED)

add_executable(Chip8_Emulator main.cpp
        emulator/include/CPU.hpp
        emulator/src/CPU.cpp
        emulator/include/CPUInstructions.hpp
        emulator/src/CPUInstructions.cpp
        emulator/include/Instruction.hpp
        emulator/include/Display.hpp
        emulator/src/Display.cpp
        emulator/include/EmulatorDisplay.hpp
        emulator/src/EmulatorDisplay.cpp
        emulator/include/ConsoleDisplay.hpp
        emulator/src/ConsoleDisplay.cpp
        emulator/include/CommandInfoDisplay.hpp
        emulator/src/CommandInfoDisplay.cpp
        emulator/include/RegisterDisplay.hpp
        emulator/src/RegisterDisplay.cpp
        emulator/include/EmulatorConsole.hpp
        emulator/src/EmulatorConsole.cpp
        emulator/include/EmulatorHistory.hpp
        emulator/src/EmulatorHistory.cpp
)

target_link_libraries(Chip8_Emulator
        sfml-graphics
        sfml-window
        sfml-system
        opengl32
        winmm
        user32
        gdi32
)
