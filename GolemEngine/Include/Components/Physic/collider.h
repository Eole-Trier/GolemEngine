#pragma once

#include "Components/component.h"

#include <Jolt/Jolt.h>
#include <Jolt/Physics/Body/BodyCreationSettings.h>

#include "Physic/physicSystem.h"
#include "Components/component.h"
#include "Resource/Rendering/model.h"
#include "Core/camera.h"
#include "Refl/refl.hpp"

using namespace JPH;

class Collider : public Component
{
private:
	bool m_IsActivated;
	MotionType m_MotionType;
	Model* m_model = nullptr;
	const char* m_modelPath;

public:
	BodyID id;

public:
	Collider();
	virtual ~Collider();

	virtual void Begin() override;

	virtual void PreUpdate();
	virtual void Update() override;
	virtual void PostUpdate();

	virtual void Draw(Camera* _camera) {};

	virtual void ToJson(json& j) const {}

	Model* GetModel();
	void SetModel(Model* _model); 
	const char* GetModelPath();
	void SetModelPath(const char* _path);

	friend refl_impl::metadata::type_info__<Collider>; // needed to reflect private members
};

REFL_AUTO(
	type(Collider, bases<Component>),
	field(m_IsActivated),
	field(m_MotionType)
)