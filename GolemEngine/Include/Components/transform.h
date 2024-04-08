#pragma once

#include <vector>

#include "vector3.h"
#include "quaternion.h"
#include "matrix4.h"
#include "Components/component.h"


class Transform : public Component
{
private:
	Transform* m_parent;
	std::vector<Transform*> m_children;
	Matrix4 m_localModel;
	Matrix4 m_globalModel;

public:

	
	Vector3 globalPosition; // access only, modification is useless yet
	Vector3 localPosition;
	Vector3 rotation;
	Vector3 scaling;

public:
	GOLEM_ENGINE_API Transform();
	GOLEM_ENGINE_API Transform(Transform* _parent);
	GOLEM_ENGINE_API Transform(Vector3 _position, Vector3 _rotation, Vector3 _scaling, Transform* _parent);
	GOLEM_ENGINE_API ~Transform();
	GOLEM_ENGINE_API void Update() override;

	GOLEM_ENGINE_API void UpdateSelfAndChilds();
	GOLEM_ENGINE_API void AddChild(Transform* const _t);
	GOLEM_ENGINE_API void AddChildren(std::vector<Transform*> const _ts);
	GOLEM_ENGINE_API void RemoveChild(Transform* const _t);
	GOLEM_ENGINE_API void SetParent(Transform* const _t);
	GOLEM_ENGINE_API bool IsChildOf(Transform* const _parent);
	_NODISCARD GOLEM_ENGINE_API bool IsAParentOf(Transform* const _t);


	GOLEM_ENGINE_API Transform* GetParent();

	GOLEM_ENGINE_API Matrix4 GetGlobalModel();
	GOLEM_ENGINE_API Matrix4 GetLocalModel();

	GOLEM_ENGINE_API const std::vector<Transform*>& GetChildren() const;
};

REFL_AUTO(
	type(Transform, bases<Component>),
	field(localPosition),
	field(rotation),
	field(scaling)
)