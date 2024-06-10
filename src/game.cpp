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

    if(!(IMG_Init(IMG_INIT_JPG | IMG_INIT_PNG))){
        printf("error initing the image library");
        return;
    }

    // init player
    
    player = new Player(100, 10, renderer);
    
}

void Game::gameloop()
{
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
                    // case SDLK_w:
                    // player->setverticalSpeed(10);
                    // player->move(player->getverticalSpeed(), player->gethorizontalSpeed());
                    // break;

                    // case SDLK_a:
                    // player->sethorizontalSpeed(-10);
                    // player->move(player->getverticalSpeed(), player->gethorizontalSpeed());
                    // break;

                    // case SDLK_s:
                    // player->setverticalSpeed(-10);
                    // player->move(player->getverticalSpeed(), player->gethorizontalSpeed());
                    // break;

                    // case SDLK_d:
                    // player->sethorizontalSpeed(10);
                    // player->move(player->getverticalSpeed(), player->gethorizontalSpeed());
                    // break;

                    case SDLK_q:
                    // rotate 

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



    //SDL_RenderPresent(renderer);
}

void Game::renderplayer(Player* player)
{
    SDL_SetRenderDrawColor(renderer,255,255,255,SDL_ALPHA_OPAQUE);
    SDL_RenderCopy(renderer, player->getTexture(), NULL, player->getPlayerRect());
}

void Game::render()
{
    rendermap();
    renderplayer(player);

    SDL_RenderPresent(renderer);
}


void Game::close()
{
    SDL_DestroyRenderer(renderer);
    renderer = nullptr;
    SDL_DestroyWindow(window);
    window = nullptr;
    SDL_Quit();
}
