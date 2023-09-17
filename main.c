
#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"
#include "math.h"
#include "stdio.h"
#include "stdbool.h"


#define SCREEN_WIDTH 640
#define SCREEN_HEIGHT 640
#define MAP_WIDTH 8
#define MAP_HEIGTH 8

typedef struct {
    float posx, posy, dir, fov, height;
}Player;

SDL_Window *window = NULL;
SDL_Renderer *renderer = NULL;
SDL_Texture *texture = NULL;

// create player

static int map[MAP_WIDTH][MAP_HEIGTH] = {
        1,1,1,1,1,1,1,1,
        1,0,0,0,0,0,0,1,
        1,0,0,0,0,0,0,1,
        1,0,0,0,0,0,0,1,
        1,0,0,0,0,0,0,1,
        1,0,0,0,0,0,0,1,
        1,0,0,0,0,0,0,1,
        1,1,1,1,1,1,1,1,
};


double dtr(double degree){
    return (degree * M_PI) / 180;
}

void drawmap(){
    for (int i = 0; i < MAP_WIDTH; i++) {
        for (int j = 0; j < MAP_HEIGTH; j++) {
            if(map[i][j] == 1){

            }
        }
        printf("\n");
    }
}

void init(){

    if (SDL_Init(SDL_INIT_EVERYTHING ) < 0){
        printf("cannot init sdl\n");
        return;
    }

    if (IMG_Init(IMG_INIT_PNG) == 0){
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

//    wsurface = SDL_GetWindowSurface(window);
//    if (wsurface == NULL){
//        return;
//    }

    texture = IMG_LoadTexture(renderer, "char.png");
    if (texture == NULL){
        printf("texture cannot be loaded");
        return;
    }
}

void rendermap(){
//    SDL_Rect textureRect = {0,0, 100,100};
//    SDL_RenderCopy(renderer, texture, NULL, &textureRect);


}

void gameloop(){
    bool run = true;
    SDL_Event e;

    double posx = SCREEN_WIDTH / 2, posy = SCREEN_HEIGHT / 2; // x and y start pos

    double time = 0; // time of current frame
    double oldtime = 0; // time of previous frame
    double degree = -150; // start derecesi
    double playerx = SCREEN_WIDTH / 2 - 70; // 250
    double playery = SCREEN_HEIGHT / 2 - 40; // 290
    int mapx = 0;
    int mapy = 0;
    double dirlength = 200; // direction line uzunluk,
    double FOV = 0;

    Player p = {playerx, playery, 45, 100}; // dir = 45 derece

    while(run){

        // map grid render
        for (int i = 0; i < SCREEN_HEIGHT; i+=80) {
            for (int j = 0; j < SCREEN_WIDTH; j+=80) {
                SDL_Rect rect = {mapx, mapy, 80, 80};
                SDL_SetRenderDrawColor(renderer,255,255,255,SDL_ALPHA_OPAQUE);
                SDL_RenderDrawRect(renderer, &rect);

                if (map[(i/80)][j/80] == 1){
                    SDL_SetRenderDrawColor(renderer,0,0,255,SDL_ALPHA_OPAQUE);
                    SDL_RenderFillRect(renderer, &rect);
                }
                mapx += 80;
                SDL_RenderPresent(renderer);
            }
            mapx = 0;
            mapy += 80;
        }


        for (int x = 0; x < SCREEN_WIDTH; x++) {
            p.dir = x;

        }

        SDL_SetRenderDrawColor(renderer,255,100,0,SDL_ALPHA_OPAQUE);
        SDL_RenderDrawLine(renderer, p.posx, p.posy, p.posx+dirlength, p.posy-dirlength); // direction ray
        SDL_RenderDrawLine(renderer, p.posx, p.posy, p.posx+200, p.posy-100); // yatay çizgi
        SDL_RenderDrawLine(renderer, p.posx, p.posy, p.posx+100, p.posy-200); // dikey çizgi
        SDL_RenderPresent(renderer);

        FOV = atan(50/100) + atan(100 / 50);
        FOV = (FOV * 180 / M_PI);  // radian to degrees;


//        posx = cos(dtr(degree)) * 100 + 320;
//        posy = sin(dtr(degree)) * 100 + 240;
//
//        if (degree == -29){degree = -150;}
//        printf("%f\n", degree);
//        degree++;

        while(SDL_PollEvent(&e) != 0){
            if (e.type == SDL_QUIT){
                run = false;
                break;
            }
            else if (e.type == SDL_KEYDOWN){
                switch (e.key.keysym.sym) {
                    case SDLK_w:
                        p.posy-=20;
                        break;
                    case SDLK_a:
                        p.posx-=20;
                        break;
                    case SDLK_s:
                        p.posy += 20;
                        break;
                    case SDLK_d:
                        p.posx += 20;
                        break;
                    case SDLK_q:

                    default:
                        break;
                }
            }
        }
    }
}

void close(){
    SDL_DestroyTexture(texture);
    texture = NULL;
    SDL_DestroyRenderer(renderer);
    renderer = NULL;
    SDL_DestroyWindow(window);
    window = NULL;
    SDL_Quit();
}

int main(int argc, char* argv[]) {

    (void) argc;
    (void) argv;

    init();

    gameloop();

    close();

    return 0;
}
