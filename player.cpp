#include "player.h"

Player::Player(int health, float speed)
{
    this->health = health;
    this->speed = speed;
}

int Player::getHealth()
{
    return health;
}

int Player::getAmmo()
{
    return ammo;
}

float Player::getSpeed()
{
    return speed;
}

float Player::getxpos()
{
    return xpos;
}

float Player::getypos()
{
    return ypos;
}

void Player::setHealth(int health)
{
    this->health = health;
}

void Player::setAmmo(int ammo)
{
    this->ammo = ammo;
}

void Player::setSpeed(float speed)
{
    this->speed = speed;
}

void Player::setypos(float ypos)
{
   this->ypos = ypos;
}

void Player::setxpos(float xpos)
{
    this->xpos = xpos;
}
