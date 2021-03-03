#ifndef PLAYER_BULLET_H
#define PLAYER_BULLET_H

#include "GameObject.h"

class PlayerBullet :
    public GameObject
{
public: 
    PlayerBullet(Vector2 direction, Vector2 startPosition);

private:
    const float bulletSpeed = 300.0f;
};

#endif // !PLAYER_BULLET_H