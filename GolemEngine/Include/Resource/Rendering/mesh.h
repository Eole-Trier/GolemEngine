#pragma once

#include <string>

#include "dll.h"
#include "Core/gameobject.h"

class Model;
class Texture;
class Shader;
class Transform;
class Camera;

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