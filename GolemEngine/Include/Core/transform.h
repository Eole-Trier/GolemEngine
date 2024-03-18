#pragma once

#include <vector>

#include "vector3.h"
#include "matrix4.h"

#include "Components/component.h"

class Transform : public Component
{
private:
	Transform* m_parent;
	std::vector<Transform*> m_children;
	Matrix4 m_globalModel;
	Matrix4 m_localModel;

public:
	Vector3 position;
	Vector3 rotation;
	Vector3 scaling;

public:
	Transform(Vector3 _position, Vector3 _rotation, Vector3 _scaling);
	void Update() override;

	void UpdateSelfAndChilds();
	void AddChild(Transform* const t);
	void AddChildren(std::vector<Transform*> const ts);
	void RemoveChild(Transform* const t);
	void SetParent(Transform* const t);

	Matrix4 GetGlobalModel();
	Matrix4 GetLocalModel();

	GOLEM_ENGINE_API const std::vector<Transform*>& GetChildren() const;

};
