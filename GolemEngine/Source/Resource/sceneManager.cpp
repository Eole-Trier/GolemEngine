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
}

void SceneManager::SaveScene()
{
    json jScene;
    GetCurrentScene()->to_json(jScene);
    std::string sceneFileName = GetCurrentScene()->name;
    sceneFileName.append(".json");
    // std::string sceneFileName = "scene_0.json";
    std::fstream sceneFile;
    if (Tools::FindFile(sceneFileName) == "")
    {
        std::cout << "Didn't find " << sceneFileName << std::endl;
    }
    sceneFile.open(Tools::FindFile(sceneFileName), std::ios::out);
    sceneFile << jScene.dump(2);
}

void SceneManager::LoadScene(int _id)
{
    m_currentScene = m_scenes[_id];
    if (!m_currentScene->isInit)
    {
        m_currentScene->Init();
        m_currentScene->isInit = true;
    }
    std::cout << "Loaded scene: " << m_currentScene->name << std::endl;
    // std::fstream sceneFile;
    // sceneFile.open(Tools::FindFile("sceneFile.json"), std::ios::in);
    // json jScene;
    // sceneFile >> jScene;
    //
    // std::string sceneName = "scene_";
    // sceneName.append(std::to_string(m_scenes.size()-1));
    // CreateScene(sceneName);
    //
    // std::cout << "Loaded scene " << sceneName << std::endl;
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


