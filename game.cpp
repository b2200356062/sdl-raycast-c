#include "game.h"

Game::Game()
{
    init();
    gameloop();
    close();
}

void Game::init()
{
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

    if (window == nullptr){
        printf("cannot init window\n");
        return;
    }

    renderer = SDL_CreateRenderer(window, -1 , SDL_RENDERER_PRESENTVSYNC | SDL_RENDERER_ACCELERATED);

    if(renderer == nullptr){
        printf("cannot init renderer\n");
        return;
    }
}

void Game::gameloop()
{
    double time = 0; // time of current frame
    double oldtime = 0; // time of previous frame
    double dirlength = 30; // direction line uzunluk,

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

                    case SDLK_a:

                    case SDLK_s:

                    case SDLK_d:

                    case SDLK_q:

                    case SDLK_e:

                    case SDLK_ESCAPE:
                        run = 0;
                        break;

                    default:
                        break;
                }
            }
        }

        render();

        // SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
        // SDL_RenderClear(renderer);        
        // SDL_RenderPresent(renderer);
    }
}

void Game::rendermap()
{
//    SDL_Rect textureRect = {0,0, 100,100};
//    SDL_RenderCopy(renderer, texture, nullptr, &textureRect);
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

                SDL_SetRenderDrawColor(renderer,0,0,0,SDL_ALPHA_OPAQUE);
                SDL_RenderFillRect(renderer, &rect);
            }
            mapx += 80;

        }
        mapx = 0;
        mapy += 80;
    }
    SDL_RenderPresent(renderer);
}


void Game::render()
{
    rendermap();
}


void Game::close()
{
    SDL_DestroyRenderer(renderer);
    renderer = nullptr;
    SDL_DestroyWindow(window);
    window = nullptr;
    SDL_Quit();
}
