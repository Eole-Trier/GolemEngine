#pragma once

#include <string>
#include <vector>

#include "resource.h"
#include "vector3.h"
#include "shader.h"
#include "texture.h"
#include "vertex.h"

class GOLEM_ENGINE_API Mesh : public Resource
{
private:
	std::vector<Vertex> m_vertices;
	std::vector<unsigned int> m_indices;
	std::vector<Texture> m_textures;
	unsigned int m_vao;
	unsigned int m_vbo;
	unsigned int m_ebo;

private:
	void SetupMesh();

public:
	Mesh();
	~Mesh();
	Mesh(std::vector<Vertex> _vertices, std::vector<unsigned int> _indices, std::vector<Texture> _textures);
	
	void Draw(Shader& _shader);
};