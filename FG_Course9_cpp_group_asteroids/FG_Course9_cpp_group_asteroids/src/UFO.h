#ifndef UFO_H
#define UFO_H

#include "GameObject.h"
#include "PlayerSpaceship.h"

class UFO : public GameObject
{
public:
	UFO() = delete;
	UFO(Vector2 spawnPoint, PlayerSpaceship* playerObject);
	void update();
private:
	PlayerSpaceship* player;
	static constexpr float speed = 40.0f;
};


#endif // !UFO_H