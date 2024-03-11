#pragma once

#include "vector3.h"

#include "Components/component.h"

class Transform : public Component
{
public:
	void Update() override;

private:
	Vector3 m_transform;
	Vector3 m_rotation;
	Vector3 m_scaling;
};
