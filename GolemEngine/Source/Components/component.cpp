#include "Components/component.h"
#include "Core/gameobject.h"

void Component::SetOwner(GameObject* _owner)
{
	owner = _owner;
}

