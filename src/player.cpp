#include "player.h"

Player::Player(int health, float speed, SDL_Renderer *renderer)
{
    this->health = health;
    this->verticalspeed = 0;
    this->horizontalspeed = 0;
    this->rect = {int(xpos), int(ypos), 40, 40};
    if(initPlayer(renderer, this->rect) == 1){
        return;
    }
}

int Player::initPlayer(SDL_Renderer* renderer, SDL_Rect &rect){
    this->texture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_ABGR8888, SDL_TEXTUREACCESS_STREAMING, 40, 40);
    
    if(this->texture == nullptr){
        printf("error initing the player texture");
        return 1;
    }
    else{
        return 0;
    }
}

int Player::getHealth()
{
    return health;
}

int Player::getAmmo()
{
    return ammo;
}

float Player::getverticalSpeed()
{
    return verticalspeed;
}

float Player::gethorizontalSpeed()
{
    return horizontalspeed;
}

float Player::getxpos()
{
    return xpos;
}

float Player::getypos()
{
    return ypos;
}

SDL_Rect* Player::getPlayerRect()
{
    return &this->rect;
}

SDL_Texture* Player::getTexture()
{
    return this->texture;
}

void Player::setTexture(SDL_Texture* texture){
    this->texture = texture;
}
void Player::move(float verticalspeed, float horizontalspeed)
{
    ypos += horizontalspeed * deltatime;
    xpos += verticalspeed * deltatime;
}

void Player::setPlayerRect(SDL_Rect *rect)
{
    this->rect = *rect;
}

void Player::setHealth(int health)
{
    this->health = health;
}

void Player::setAmmo(int ammo)
{
    this->ammo = ammo;
}


void Player::setypos(float ypos)
{
   this->ypos = ypos;
}

void Player::setxpos(float xpos)
{
    this->xpos = xpos;
}

void Player::setverticalSpeed(float verticalspeed)
{
    this->verticalspeed = verticalspeed;
}

void Player::sethorizontalSpeed(float horizontalspeed)
{
    this->horizontalspeed = horizontalspeed;
}
