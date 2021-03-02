#ifndef PLAYER_SPACESHIP_H
#define PLAYER_SPACESHIP_H


#include "GameObject.h"
class PlayerSpaceship :
    public GameObject
{
public:
    PlayerSpaceship();
    void update(double dt);
    // TODO player spaceship should have rotation
    // TODO player spaceship should have player controls
};

#endif // !PLAYER_SPACESHIP_H