cmake_minimum_required(VERSION 3.10)
project(BeatEmUp)

set(CMAKE_CXX_STANDARD 17)

set(SDL2_DIR C:/SDL2)

include_directories(
        ${SDL2_DIR}/include
        ${CMAKE_SOURCE_DIR}
)

link_directories(${SDL2_DIR}/lib/x64)

add_executable(main
        main.cpp
        Game.cpp
        Player.cpp
        Enemy.cpp
        Input.cpp
        Combo.cpp
        Combat.cpp
        Animation.cpp
        Render.cpp
        level.cpp
)

target_link_libraries(main SDL2 SDL2main)
