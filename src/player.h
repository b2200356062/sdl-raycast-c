
#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"
#include <stdio.h>

class Player{
    private:
        int health;
        int ammo;
        float verticalspeed, horizontalspeed;
        float xpos = 250, ypos = 250;
        float deltatime = 0.0069;
        SDL_Rect rect;
        SDL_Surface* surface = nullptr;
        SDL_Texture *texture = nullptr;
    
    public:
        Player(int health, float speed, SDL_Renderer* renderer);
        int getHealth();
        int getAmmo();
        float gethorizontalSpeed();
        float getverticalSpeed();
        float getxpos();
        float getypos();
        SDL_Rect *getPlayerRect();
        SDL_Texture* getTexture();

        int initPlayer(SDL_Renderer* renderer, SDL_Rect &rect);

        void move(float verticalspeed, float horizontalspeed);
        void setPlayerRect(SDL_Rect *rect);
        void setTexture(SDL_Texture* texture);
        void setHealth(int health);
        void setAmmo(int ammo);
        void setypos(float ypos);
        void setxpos(float xpos);
        void setverticalSpeed(float verticalspeed);
        void sethorizontalSpeed(float horizontalspeed);
};