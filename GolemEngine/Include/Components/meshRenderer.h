#pragma once

#include "component.h"
#include "Resource/Rendering/mesh.h"
#include "Core/camera.h"
#include "Refl/refl.hpp"

class MeshRenderer : public Component
{
private:
	Mesh* m_mesh = nullptr;
public:
	MeshRenderer();
	MeshRenderer(Mesh* _mesh);
	~MeshRenderer();

	void Draw(float _width, float _height, Camera* _cam);
};

REFL_AUTO(
	type(MeshRenderer)
)