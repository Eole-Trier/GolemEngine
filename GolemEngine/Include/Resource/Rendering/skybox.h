#pragma once

#include <vector>
#include <string>

class Skybox
{
private:
	Skybox();
	Skybox(const Skybox& skybox) = delete;
	~Skybox();

	Skybox* m_instance;

	static unsigned int m_cubemapId;
	static unsigned int m_skyboxVAO;
	static unsigned int m_skyboxVBO;

public:
	static Skybox& GetInstance();
	unsigned int LoadCubemap(std::vector<std::string> faces);
	void SetTexture();
	unsigned int GetSkyboxId();
	unsigned int GetSkyboxVAO();
};