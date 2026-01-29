cmake_minimum_required(VERSION 3.10)
project(BeatEmUp)

set(CMAKE_CXX_STANDARD 17)

# Znajdź SDL2 z systemu
find_package(SDL2 REQUIRED)
include_directories(${SDL2_INCLUDE_DIRS} ${CMAKE_SOURCE_DIR})

# Dodaj własne flagi kompilatora
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -O2")

# Pliki źródłowe
set(SRCS
    main.cpp
    Game.cpp
    Player.cpp
    Enemy.cpp
    Input.cpp
    Combat.cpp
    Animation.cpp
    Render.cpp
    level.cpp
    Collision.cpp
)

# Utwórz plik wykonywalny
add_executable(main ${SRCS})

# Linkuj SDL2
target_link_libraries(main ${SDL2_LIBRARIES})
