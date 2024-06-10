
#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"
#include <cmath>
#include <stdio.h>

#include "player.h"

#define SCREEN_WIDTH 640
#define SCREEN_HEIGHT 640
#define MAP_WIDTH 8
#define MAP_HEIGTH 8

class Game{
    private:
        bool gameRunning;
        SDL_Window *window = nullptr;

        SDL_Renderer *renderer = nullptr;

        Player *player = nullptr;

        const int map[MAP_WIDTH][MAP_HEIGTH] = 
        {
            1,1,1,1,1,1,1,1,
            1,0,0,0,0,0,0,1,
            1,0,0,0,1,1,0,1,
            1,0,0,0,0,0,0,1,
            1,1,1,0,0,0,0,1,
            1,0,0,0,0,0,0,1,
            1,0,0,0,0,0,0,1,
            1,1,1,1,1,1,1,1,
        };

    public:
        
        Game();
        void init();
        void gameloop();
        void render();
        void rendermap();
        void renderplayer(Player *player);
        void close();
};