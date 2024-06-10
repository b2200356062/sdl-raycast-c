cmake_minimum_required(VERSION 3.26)
project(main)

set(CMAKE_CPP_STANDARD 17)
find_package(SDL2 REQUIRED)

add_executable(main src/main.cpp src/player.h src/game.h src/player.cpp src/game.cpp)
target_link_libraries(main ${SDL_LIBRARY} -lmingw32 -lSDL2main -lSDL2 -lSDL2_image)