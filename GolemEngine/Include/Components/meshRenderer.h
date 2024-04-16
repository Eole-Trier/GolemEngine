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

	void Draw(float _width, float _height, Camera* _camera);

	Mesh* GetMesh();


	// Define serialization and deserialization functions manually because the
	// macro is not used due to the pointer member variable.
	void to_json(json& j) const
	{
		if (m_mesh != nullptr)
		{
			j["name"] = "meshRenderer";
			json jMesh;
			m_mesh->to_json(jMesh);
			j["data"] = jMesh;
		}
	}
};

REFL_AUTO(
	type(MeshRenderer)
)