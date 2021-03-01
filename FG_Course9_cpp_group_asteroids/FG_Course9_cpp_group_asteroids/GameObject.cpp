#include "GameObject.h"

void GameObject::Update(double dt)
{
	for (Component comp : components)
	{
		comp.Update(dt);
	}
}
