#include "Resource/sceneManager.h"

#include <nlohmann/json.hpp>

#include "Wrappers/graphicWrapper.h"
#include "Wrappers/windowWrapper.h"

using json = nlohmann::json;


void SceneManager::Init()
{
    m_scenes.push_back(new Scene("Scene_0"));
    LoadScene(0);
    InitScene();
}

void SceneManager::InitScene()
{
    // Init scene
    m_currentScene->Init();
    // Create a framebuffer and pass the scene in it to be used in the viewport 
    GraphicWrapper::CreateFramebuffer(WindowWrapper::GetScreenSize().x, WindowWrapper::GetScreenSize().y);
}

void SceneManager::SaveScene()
{
    // TODO
}

void SceneManager::CreateScene(std::string _sceneName)
{
    m_scenes.push_back(new Scene(_sceneName));
}

void SceneManager::LoadScene(int _sceneId)
{
    m_currentScene = m_scenes[_sceneId];
}


Scene* SceneManager::GetCurrentScene()
{
    return m_currentScene;
}


