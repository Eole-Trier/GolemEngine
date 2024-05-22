#pragma once

#include "Components/script.h"
#include "Components/Physic/sphereCollider.h"
#include "Refl/refl.hpp"

class Test : public Script
{
private:
	SphereCollider* m_sphereCollider;
public:
	Test();
	~Test();

	void Begin() override;
	void Update() override;

	void FunctionThatIGiveToACollider(Collider* _collider, Collider* _other);

	void ToJson(json& j) const {}
};

REFL_AUTO(
	type(Test, bases<Script>)
)