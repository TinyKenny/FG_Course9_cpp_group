#ifndef PLAYER_SPACESHIP_H
#define PLAYER_SPACESHIP_H

#include "GameObject.h"
#include "Matrix2x2.h"

class Application;

class PlayerSpaceship :
    public GameObject
{
public:
    PlayerSpaceship(Application *application);
    void update(double dt);
    std::vector<Vector2> getPoints() const override;
    // TODO player spaceship should have rotation
    // TODO player spaceship should have player controls
public:
    Application *application;
private:
    Matrix2x2 localToWorldMatrix;
};

#endif // !PLAYER_SPACESHIP_H