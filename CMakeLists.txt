cmake_minimum_required(VERSION 3.26)
project(main)

set(CMAKE_CPP_STANDARD 11)
find_package(SDL2 REQUIRED)

add_executable(main main.cpp player.h game.h player.cpp game.cpp)
target_link_libraries(main ${SDL_LIBRARY} -lmingw32 -lSDL2main -lSDL2 -lSDL2_image)