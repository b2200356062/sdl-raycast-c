
#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"
#include <math.h>
#include <stdio.h>

#define SCREEN_WIDTH 640
#define SCREEN_HEIGHT 640
#define MAP_WIDTH 8
#define MAP_HEIGTH 8

SDL_Window *window = NULL;
SDL_Renderer *renderer = NULL;


float depth = 8.0f;

// create player

static int map[MAP_WIDTH][MAP_HEIGTH] = {
        1,1,1,1,1,1,1,1,
        1,0,0,0,0,0,0,1,
        1,0,0,0,1,1,0,1,
        1,0,0,0,0,0,0,1,
        1,1,1,0,0,0,0,1,
        1,0,0,0,0,0,0,1,
        1,0,0,0,0,0,0,1,
        1,1,1,1,1,1,1,1,
};


double dtr(double degree){
    return (degree * M_PI) / 180;
}


void rendermap(){
//    SDL_Rect textureRect = {0,0, 100,100};
//    SDL_RenderCopy(renderer, texture, NULL, &textureRect);
    // map grid render
    SDL_SetRenderDrawColor(renderer,255,255,255,SDL_ALPHA_OPAQUE);
    SDL_RenderClear(renderer);

    int mapx = 0;
    int mapy = 0;
    for (int i = 0; i < SCREEN_HEIGHT; i+=80) {
        for (int j = 0; j < SCREEN_WIDTH; j+=80) {
            SDL_Rect rect = {mapx, mapy, 80, 80};

            SDL_SetRenderDrawColor(renderer,255,255,255,SDL_ALPHA_OPAQUE);
            SDL_RenderDrawRect(renderer, &rect);

            if (map[i/80][j/80] == 1){

                SDL_SetRenderDrawColor(renderer,0,0,255,SDL_ALPHA_OPAQUE);
                SDL_RenderFillRect(renderer, &rect);
            }
            mapx += 80;

        }
        mapx = 0;
        mapy += 80;
    }
    SDL_RenderPresent(renderer);
}

void init(){

    if (SDL_Init(SDL_INIT_EVERYTHING ) < 0){
        printf("cannot init sdl\n");
        return;
    }

    if (IMG_Init(IMG_INIT_PNG) != 2){
        printf("img cannot be initted");
        return;
    }

    window = SDL_CreateWindow("oyun",
                              SDL_WINDOWPOS_UNDEFINED,
                              SDL_WINDOWPOS_UNDEFINED,
                              SCREEN_WIDTH, SCREEN_HEIGHT,
                              SDL_WINDOW_RESIZABLE);

    if (window == NULL){
        printf("cannot init window\n");
        return;
    }

    renderer = SDL_CreateRenderer(window, -1 , SDL_RENDERER_PRESENTVSYNC);

    if(renderer == NULL){
        printf("cannot init renderer\n");
        return;
    }
}

typedef struct {
    float posx; float posy; float angle; float fov;
}Player;

void gameloop(){

    double time = 0; // time of current frame
    double oldtime = 0; // time of previous frame
    double dirlength = 30; // direction line uzunluk,

    Player p;

    p.angle = 0;
    p.posx = 250;
    p.posy = 250;
    p.fov = 60;

    SDL_Event e;
    int run = 1;

    while(run){
        
        while(SDL_PollEvent(&e) != 0){
            if (e.type == SDL_QUIT){
                run = 0;
                break;
            }
            else if (e.type == SDL_KEYDOWN){
                switch (e.key.keysym.sym) {
                    case SDLK_w:
                        if(p.posy < 80){
                            continue;
                        }
                        else{
                            p.posy -= 5;
                        }
                        break;
                    case SDLK_a:
                        if (p.posx < 80){
                            
                        }
                        p.posx -= 5;
                        break;
                    case SDLK_s:
                        p.posy += 5;
                        break;
                    case SDLK_d:
                        p.posx += 5;
                        break;
                    case SDLK_q:
                        p.angle -= 0.1f;
                        break;
                    case SDLK_e:
                        p.angle += 0.1f;
                        break;
                    case SDLK_ESCAPE:
                        run = 0;
                        break;
                    default:
                        break;
                }
            }
        }
        
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
        SDL_RenderClear(renderer);
        
        SDL_RenderPresent(renderer);

        }
    }

void close(){
    SDL_DestroyRenderer(renderer);
    renderer = NULL;
    SDL_DestroyWindow(window);
    window = NULL;
    SDL_Quit();
}


int main(int argc, char* argv[]) {

    init();

    gameloop();

    close();

    return 0;
}
