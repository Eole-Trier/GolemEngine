#include "Resource/sceneManager.h"
#include "Wrappers/graphicWrapper.h"
#include "Wrappers/windowWrapper.h"


void SceneManager::Init()
{
    m_scenes.push_back(new Scene("Scene_1"));
    SetCurrentScene(0);
}

void SceneManager::InitScene()
{
    // Init scene
    m_currentScene->Init();
    // Create a framebuffer and pass the scene in it to be used in the viewport 
    GraphicWrapper::CreateFramebuffer(WindowWrapper::GetScreenSize().x, WindowWrapper::GetScreenSize().y);
}


Scene* SceneManager::GetCurrentScene()
{
    return  m_currentScene;
}

void SceneManager::SetCurrentScene(int _sceneId)
{
    m_currentScene = m_scenes[_sceneId];
}



