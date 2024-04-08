#pragma once

#include <string>

#include "dll.h"
#include "Core/gameobject.h"

class Model;
class Texture;
class Shader;
class Transform;
class Camera;

class GOLEM_ENGINE_API Mesh
{
private:
	Model* m_model;
	Texture* m_texture;
	Shader* m_shader;

private:
	void SetupMesh();

public:
	Mesh(Model* _model, Texture* _texture, Shader* _shader);
	~Mesh();

	Texture* GetTexture();
	Model* GetModel();
	Shader* GetShader();
};