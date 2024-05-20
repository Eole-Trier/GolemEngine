#pragma once

#include "dll.h"

#include <vector>
#include <string>
#include <unordered_map>


#include "Utils/tools.h"

class GOLEM_ENGINE_API Skybox
{
private:
	Skybox();
	Skybox(const Skybox& skybox) = delete;
	~Skybox();

	Skybox* m_instance;

	static unsigned int m_cubemapId;
	static unsigned int m_skyboxVAO;
	static unsigned int m_skyboxVBO;

	std::unordered_map<std::string, unsigned int> m_loadedTextures;

public:
	static Skybox& GetInstance();
	unsigned int LoadCubemap(std::vector<std::string> faces);
	void SetTexture();
	void SetSpaceSkybox();
	unsigned int GetSkyboxCubeMapId();
	unsigned int GetSkyboxVAO();

	std::vector<std::string> faces
	{
		Tools::FindFile("skybox_right.jpg"),
		Tools::FindFile("skybox_left.jpg"),
		Tools::FindFile("skybox_bottom.jpg"),
		Tools::FindFile("skybox_top.jpg"),
		Tools::FindFile("skybox_front.jpg"),
		Tools::FindFile("skybox_back.jpg"),
	};

	std::vector<std::string> faces2
	{
		Tools::FindFile("Left_Tex.jpg"),
		Tools::FindFile("Right_Tex.jpg"),
		Tools::FindFile("Down_Tex.jpg"),
		Tools::FindFile("Up_Tex.jpg"),
		Tools::FindFile("Front_Tex.jpg"),
		Tools::FindFile("Back_Tex.jpg"),
	};
};