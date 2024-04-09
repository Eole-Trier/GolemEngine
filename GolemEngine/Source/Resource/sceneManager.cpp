#include "Resource/sceneManager.h"

#include <nlohmann/json.hpp>
#include <fstream>

#include "Resource/tools.h"
#include "Wrappers/graphicWrapper.h"
#include "Wrappers/windowWrapper.h"

using json = nlohmann::json;


void SceneManager::Init()
{
    // Create a framebuffer and pass the scene in it to be used in the viewport 
    GraphicWrapper::CreateFramebuffer(GL_RGBA, WindowWrapper::GetScreenSize().x, WindowWrapper::GetScreenSize().y);
    m_scenes.push_back(new Scene("scene_0"));
    LoadScene(0);
    SaveScene();

    // Init also scenes that are already saved
    for (int i = 0; i < Tools::GetFolderSize(Tools::FindFolder("Scenes")); i++)
    {
        // CreateScene()
    }
}

void SceneManager::SaveScene()
{
    json jScene;
    // Get scene name and add .json type to it
    GetCurrentScene()->to_json(jScene);
    std::string sceneFileName = GetCurrentScene()->name;
    sceneFileName.append(".json");

    // Create or find the file and save it
    std::fstream sceneFile;
    if (Tools::FindFile(sceneFileName) != "")
    {
        sceneFile.open(Tools::FindFile(sceneFileName), std::ios::out);
        sceneFile << jScene.dump(2);
    }
    else if (Tools::FindFile(sceneFileName) == "")
    {
        sceneFile.open(Tools::FindFolder("Scenes").append("\\" + sceneFileName), std::ios::out);
        sceneFile << jScene.dump(2);
    }
    // Tools::GetFolderSize(Tools::FindFolder("Scenes"));

}

void SceneManager::LoadScene(int _id)
{
    m_currentScene = m_scenes[_id];
    if (!m_currentScene->isInit)
    {
        m_currentScene->Init();
    }
    std::cout << "Loaded scene: " << m_currentScene->name << std::endl;
}

void SceneManager::CreateScene(std::string _sceneName)
{
    m_scenes.push_back(new Scene(_sceneName));
}

/*void SceneManager::LoadScene(int _sceneId)
{
    m_currentScene = m_scenes[_sceneId];
}*/


Scene* SceneManager::GetCurrentScene()
{
    return m_currentScene;
}

Scene* SceneManager::GetScene(int _id)
{
    Scene* scene = nullptr;
    for (int i = 0; i < m_scenes.size(); i++)
    {
        if (i == _id)
        {
            scene = m_scenes[i];
        }
    }
    
    return  scene;
}

int SceneManager::GetSceneCount()
{
    return  m_scenes.size();
}


