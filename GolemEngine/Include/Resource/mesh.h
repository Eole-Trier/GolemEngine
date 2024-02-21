#pragma once

#include <string>
#include <vector>

#include "resource.h"
#include "vector3.h"
#include "shader.h"
#include "texture.h"
#include "vertex.h"
#include "model.h"
#include "Viewport/camera.h"

class GOLEM_ENGINE_API Mesh : public Resource
{
private:
	Model* m_model;
	Texture* m_texture;
	Shader* m_shader;
	

private:
	void SetupMesh();

public:
	Mesh();
	~Mesh();

	void Init(Model* _model, Texture* _texture, Shader* _shader);

	void Draw(float _width, float height, Camera& _cam, const Matrix4& _localModel);
};