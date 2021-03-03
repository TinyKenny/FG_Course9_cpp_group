#ifndef PLAYER_SPACESHIP_H
#define PLAYER_SPACESHIP_H

#include "GameObject.h"

#include "Matrix2x2.h"

class PlayerSpaceship :
    public GameObject
{
public:
    PlayerSpaceship();
    void update(double dt);
    const std::vector<Vector2> getPoints() override;
    // TODO player spaceship should have rotation
    // TODO player spaceship should have player controls
private:
    Matrix2x2 localToWorldMatrix;
};

#endif // !PLAYER_SPACESHIP_H