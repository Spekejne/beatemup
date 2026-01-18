cmake_minimum_required(VERSION 3.10)
project(BeatEmUp)

set(CMAKE_CXX_STANDARD 17)

# Znajdź SDL2 z systemu
find_package(SDL2 REQUIRED)
include_directories(${SDL2_INCLUDE_DIRS} ${CMAKE_SOURCE_DIR})

# Tworzymy plik wykonywalny
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

# Linkujemy SDL2
target_link_libraries(main ${SDL2_LIBRARIES})
