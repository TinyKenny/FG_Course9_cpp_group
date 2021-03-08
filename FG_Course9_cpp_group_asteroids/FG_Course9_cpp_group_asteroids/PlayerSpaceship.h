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
    void reset();
    void update(double dt);
    std::vector<Vector2> getPoints() const override;

public:
    Application *application;
private:
    Matrix2x2 localToWorldMatrix;
    const double fireRate = 0.3f;
    double fireCooldownTimer = 0.0f;
};

#endif // !PLAYER_SPACESHIP_H