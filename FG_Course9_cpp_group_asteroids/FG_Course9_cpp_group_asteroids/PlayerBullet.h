#ifndef PLAYER_BULLET_H
#define PLAYER_BULLET_H

#include "GameObject.h"

class PlayerBullet :
    public GameObject
{
public: 
    PlayerBullet(Vector2 direction, Vector2 startPosition);
    bool update(double dt);

private:
    float bulletSpeed = 300.0f;
    double lifeTime = 1.2;
    double secondsActive = 0.0;

};

#endif // !PLAYER_BULLET_H