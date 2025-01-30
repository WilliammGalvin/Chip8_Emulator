cmake_minimum_required(VERSION 3.30)
project(Chip8_Emulator)

set(CMAKE_CXX_STANDARD 20)

include_directories("C:/SFML_mingw64/SFML-2.6.2/include")
set(SFML_DIR "C:/SFML_mingw64/SFML-2.6.2/lib/cmake/SFML")

find_package(SFML 2.5 COMPONENTS system window graphics REQUIRED)

add_executable(Chip8_Emulator main.cpp)

target_link_libraries(Chip8_Emulator
        sfml-graphics
        sfml-window
        sfml-system
        opengl32
        winmm
        user32
        gdi32
)
