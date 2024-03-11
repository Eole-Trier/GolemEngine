#pragma once

#include "vector3.h"

#include "Components/component.h"

class Transform : public Component
{
public:
	Vector3 position;
	Vector3 rotation;
	Vector3 scaling;

public:
	Transform(Vector3 _position, Vector3 _rotation, Vector3 _scaling);
	void Update() override;

};
