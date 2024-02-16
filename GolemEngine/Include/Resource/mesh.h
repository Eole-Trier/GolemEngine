#pragma once

#include <string>
#include <vector>

#include "iResource.h"
#include "vector3.h"

struct Vertex
{
	Vector3 Position;
	Vector3 Normal;
	Vector3 TextureCoords;
};

struct Texture
{
	unsigned int id;
	std::string path;
};


class Mesh : IResource
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
	
	void Draw();
};