#include "Resource/sceneManager.h"

#include <nlohmann/json.hpp>
#include <fstream>

#include "Wrappers/graphicWrapper.h"
#include "Wrappers/windowWrapper.h"
#include "Resource/Rendering/mesh.h"
#include "Resource/Rendering/model.h"
#include "Resource/Rendering/texture.h"
#include "Resource/tools.h"

using json = nlohmann::json;


void SceneManager::Init()
{
    CreateAndLoadResources();
    // Create a framebuffer and pass the scene in it to be used in the viewport 
    GraphicWrapper::CreateFramebuffer(GL_RGBA, WindowWrapper::GetScreenSize().x, WindowWrapper::GetScreenSize().y);

    if (Tools::GetFolderSize(Tools::FindFolder("Scenes")) != 0)    // Check if there are already saved scenes
    {
        // Init scenes that are already saved
        std::vector<std::string> sceneNames = Tools::GetFolderElementsNames(Tools::FindFolder("Scenes"));
        for (int i = 0; i < Tools::GetFolderSize(Tools::FindFolder("Scenes")); i++)
        {
            CreateSceneFromFile(Tools::RemoveExtension(sceneNames[i]));
            
        }
        // Load the first scene
        LoadScene(0);
    }
    else    // If there are no scenes saved, Create one
    {
        CreateScene("scene_0");
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
}

void SceneManager::LoadScene(int _id)
{
    m_currentScene = m_scenes[_id];
}

void SceneManager::CreateScene(std::string _sceneName)
{
    m_scenes.push_back(new Scene(_sceneName, 0));
}

void SceneManager::CreateSceneFromFile(std::string _sceneName)
{
    // Get the name pf the scene and append .json
    std::string sceneFileName = _sceneName;
    sceneFileName.append(".json");
    // Open the corresponding folder
    std::fstream sceneFile;
    sceneFile.open(Tools::FindFile(sceneFileName), std::ios::in);
    // Parse the json doc to a json variable here
    json jScene{json::parse(sceneFile)};
    
    Scene* scene = new Scene(_sceneName, 1);
    scene->name = jScene["name"];
    // scene.
    // Initialize the scene gameObjects corresponding to the json doc
    for (int i = 0; i < jScene["gameObjects"].size(); i++)
    {
        // Check if the gameObject being created is not the World because World is created already on Scene constructor
        if (jScene["gameObjects"][i]["name"] != "World")
        {
            GameObject* gameObject = new GameObject();
            gameObject->name = jScene["gameObjects"][i]["name"];
            Guid gameObjectGuid;
            gameObjectGuid.FromString(jScene["gameObjects"][i]["guid"]);
            gameObject->guid = gameObjectGuid;
            
            // Setup components
            for (int j = 0; j < jScene["gameObjects"][i]["components"].size(); j++)
            {
                // gameObject->AddComponent()
            }
            
        }
        else if (jScene["gameObjects"][i]["name"] == "World")
        {
            Guid worldGuid;
            worldGuid.FromString(jScene["gameObjects"][i]["guid"]);
            scene->GetWorld()->guid = worldGuid;
            Guid worldTransformGuid;
            worldTransformGuid.FromString(jScene["gameObjects"][i]["components"][0]["data"]["guid"]);
            scene->GetWorld()->transform->guid = worldTransformGuid;
            
            scene->GetWorld()->transform->localPosition = jScene["gameObjects"][i]["components"][0]["data"]["localPosition"];
            scene->GetWorld()->transform->rotation = jScene["gameObjects"][i]["components"][0]["data"]["rotation"];
            scene->GetWorld()->transform->scaling = jScene["gameObjects"][i]["components"][0]["data"]["scaling"];
        }
        
    }

    // std::cout << jScene.dump(2) << std::endl;
    
    m_scenes.push_back(scene);    
}

void SceneManager::CreateAndLoadResources()
{
    ResourceManager* resourceManager = ResourceManager::GetInstance();

    Shader* defaultShader = resourceManager->Create<Shader>(m_defaultShader, Tools::FindFile("default.vs"));
    defaultShader->SetVertexAndFragmentShader(defaultShader->path.c_str(), Tools::FindFile("default.fs").c_str());

    Texture* defaultTexture = resourceManager->Create<Texture>(m_defaultTexture, Tools::FindFile("default_texture.png"));
    defaultTexture->Load(defaultTexture->path.c_str());

    Texture* vikingTexture = resourceManager->Create<Texture>("viking_texture", Tools::FindFile("viking_room.jpg"));
    vikingTexture->Load(vikingTexture->path.c_str());

    Texture* allBaldTexture = resourceManager->Create<Texture>("all_bald_texture", Tools::FindFile("all_bald.jpg"));
    allBaldTexture->Load(allBaldTexture->path.c_str());

    Model* vikingModel = resourceManager->Create<Model>("viking_room", Tools::FindFile("viking_room.obj"));
    vikingModel->Load(vikingModel->path.c_str());

    Model* defaultModel = resourceManager->Create<Model>(m_defaultModel, Tools::FindFile("cube.obj"));
    defaultModel->Load(defaultModel->path.c_str());

    Model* sphereModel = resourceManager->Create<Model>("sphere", Tools::FindFile("sphere.obj"));
    sphereModel->Load(sphereModel->path.c_str());

    Model* cubeModel = resourceManager->Create<Model>("cube", Tools::FindFile("cube.obj"));
    cubeModel->Load(cubeModel->path.c_str());
}

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

std::string SceneManager::GetDefaultShader()
{
    return  m_defaultShader;
}

std::string SceneManager::GetDefaultTexture()
{
    return m_defaultTexture;
}

std::string SceneManager::GetDefaultModel()
{
    return m_defaultModel;
}

void SceneManager::SetCurrentScene(Scene* _scene)
{
    m_currentScene = _scene;
}


