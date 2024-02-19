
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
        
        SDL_SetRenderDrawColor(renderer, 0,0,0,0);
        SDL_RenderClear(renderer);

        for (int i = 0; i < SCREEN_WIDTH; i++){   
            float rayangle = (p.angle - p.fov / 2.0f) + ((float) i / (float) SCREEN_WIDTH);

            int distancetowall = 0;
            int hitwall = 0;

            float eyex = sin(rayangle);
            float eyey = cos(rayangle);

            while(!hitwall && distancetowall < depth){
                distancetowall += 1;

                int testx = (int)(p.posx + eyex * distancetowall);
                int testy = (int)(p.posy + eyey * distancetowall);

                printf("testx: %d\n", testx);
                printf("testy: %d\n", testy);

                if(testx < 0 || testx >= MAP_WIDTH * 80 || testy < 0 || testy >= MAP_HEIGTH * 80){
                    hitwall = 1;
                    distancetowall = depth;
                }
                else{

                    if(map[testy * MAP_WIDTH + testx] == 1){
                        hitwall = 1;
                    }
                }
            }
        SDL_SetRenderDrawColor(renderer,255,100,0,SDL_ALPHA_OPAQUE);
        
        rendermap();
        
        SDL_RenderDrawLine(renderer, p.posx, p.posy, p.posx, p.posy - dirlength); // direction ray
        SDL_RenderDrawLine(renderer, p.posx, p.posy, p.posx - p.angle, p.posy - p.angle);
        
        SDL_RenderDrawLine(renderer, p.posx, p.posy, p.posx + p.angle, p.posy - p.angle);
        
        SDL_SetRenderDrawColor(renderer,255,255,0,SDL_ALPHA_OPAQUE);

        SDL_RenderDrawRect(renderer, &(SDL_Rect){p.posx-5, p.posy, 10, 10}); // draw player
        SDL_RenderPresent(renderer);

        }
        
       
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
