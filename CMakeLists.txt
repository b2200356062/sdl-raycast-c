cmake_minimum_required(VERSION 3.26)
project(sdlraycastingc C)

set(CMAKE_C_STANDARD 11)
find_package(SDL2 REQUIRED)

add_executable(sdlraycastingc main.c
)
target_link_libraries(sdlraycastingc ${SDL_LIBRARY} -lmingw32 -lSDL2main -lSDL2 -lSDL2_image)