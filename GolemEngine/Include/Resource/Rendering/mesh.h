#pragma once

#include <string>
#include <vector>

#include "Resource/resource.h"
#include "vector3.h"
#include "shader.h"
#include "texture.h"
#include "vertex.h"
#include "model.h"
#include "Viewport/camera.h"
#include "Core/gameobject.h"

class GOLEM_ENGINE_API Mesh : public GameObject
{
private:
	Model* m_model;
	Texture* m_texture;
	Shader* m_shader;

private:
	void SetupMesh();

public:
	Mesh(const std::string& _name, Transform* _transform, Model* _model, Texture* _texture, Shader* _shader);
	~Mesh();

	void Draw(float _width, float _height, Camera* _cam);
};