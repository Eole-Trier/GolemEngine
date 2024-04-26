#include "Resource/sceneManager.h"

#include <nlohmann/json.hpp>
#include <fstream>

#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"
#include "imgui_internal.h"
#include "Components/audio.h"
#include "Components/meshRenderer.h"
#include "Components/Light/directionalLight.h"
#include "Components/Light/pointLight.h"
#include "Components/Light/spotLight.h"
#include "Wrappers/graphicWrapper.h"
#include "Wrappers/windowWrapper.h"
#include "Resource/Rendering/mesh.h"
#include "Resource/Rendering/model.h"
#include "Resource/Rendering/texture.h"
#include "Utils/tools.h"
#include "Resource/resourceManager.h"
#include "WorldBuilder/terrain.h"
#include "WorldBuilder/defaultTerrain.h"
#include "WorldBuilder/noisemapTerrain.h"

using json = nlohmann::json;


void SceneManager::Init()
{
    ResourceManager::CreateAndLoadResources();
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
        SaveScene();
    }
}

void SceneManager::SaveScene()
{
    json jScene;
    // Get scene name and add .json type to it
    GetCurrentScene()->ToJson(jScene);
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
    ResourceManager* resourceManager = ResourceManager::GetInstance();
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
        if (jScene["gameObjects"][i]["name"] != "World" && !jScene["gameObjects"][i]["name"].is_null())
        {
            GameObject* gameObject = new GameObject();
            gameObject->name = jScene["gameObjects"][i]["name"];
            Guid gameObjectGuid;
            gameObjectGuid.FromString(jScene["gameObjects"][i]["guid"]);
            gameObject->guid = gameObjectGuid;
            
            // Setup components
            for (int j = 0; j < jScene["gameObjects"][i]["components"].size(); j++)
            {
                // Setup each component
                
                // Setup transform component
                if (jScene["gameObjects"][i]["components"][j]["name"] == "transform")
                {
                    Guid gameObjectGuid;
                    gameObjectGuid.FromString(jScene["gameObjects"][i]["components"][j]["data"]["guid"]);
                    gameObject->transform->guid = gameObjectGuid;
                    gameObject->transform->localPosition = jScene["gameObjects"][i]["components"][j]["data"]["localPosition"];
                    gameObject->transform->rotation = jScene["gameObjects"][i]["components"][j]["data"]["rotation"];
                    gameObject->transform->scaling = jScene["gameObjects"][i]["components"][j]["data"]["scaling"];
                }
                // Setup directionalLight component
                // std::cout << jScene["gameObjects"][i]["components"][j]["name"] << std::endl;
                if (jScene["gameObjects"][i]["components"][j]["name"] == "directionalLight")
                {
                    gameObject->AddComponent<DirectionalLight>();
                    gameObject->GetComponent<DirectionalLight>()->id = jScene["gameObjects"][i]["components"][j]["data"]["id"];
                    gameObject->GetComponent<DirectionalLight>()->diffuseColor = jScene["gameObjects"][i]["components"][j]["data"]["diffuseColor"];
                    gameObject->GetComponent<DirectionalLight>()->ambientColor = jScene["gameObjects"][i]["components"][j]["data"]["ambientColor"];
                    gameObject->GetComponent<DirectionalLight>()->specularColor = jScene["gameObjects"][i]["components"][j]["data"]["specularColor"];
                    gameObject->GetComponent<DirectionalLight>()->direction = jScene["gameObjects"][i]["components"][j]["data"]["direction"];
                }
                
                // Setup pointLight component
                if (jScene["gameObjects"][i]["components"][j]["name"] == "pointLight")
                {
                    gameObject->AddComponent<PointLight>();
                    gameObject->GetComponent<PointLight>()->id = jScene["gameObjects"][i]["components"][j]["data"]["id"];
                    gameObject->GetComponent<PointLight>()->diffuseColor = jScene["gameObjects"][i]["components"][j]["data"]["diffuseColor"];
                    gameObject->GetComponent<PointLight>()->ambientColor = jScene["gameObjects"][i]["components"][j]["data"]["ambientColor"];
                    gameObject->GetComponent<PointLight>()->specularColor = jScene["gameObjects"][i]["components"][j]["data"]["specularColor"];
                    gameObject->GetComponent<PointLight>()->position = jScene["gameObjects"][i]["components"][j]["data"]["position"];
                    gameObject->GetComponent<PointLight>()->constant = jScene["gameObjects"][i]["components"][j]["data"]["constant"];
                    gameObject->GetComponent<PointLight>()->linear = jScene["gameObjects"][i]["components"][j]["data"]["linear"];
                    gameObject->GetComponent<PointLight>()->quadratic = jScene["gameObjects"][i]["components"][j]["data"]["quadratic"];
                }
                
                // Setup spotLight component
                if (jScene["gameObjects"][i]["components"][j]["name"] == "spotLight")
                {
                    gameObject->AddComponent<SpotLight>();
                    gameObject->GetComponent<SpotLight>()->id = jScene["gameObjects"][i]["components"][j]["data"]["id"];
                    gameObject->GetComponent<SpotLight>()->diffuseColor = jScene["gameObjects"][i]["components"][j]["data"]["diffuseColor"];
                    gameObject->GetComponent<SpotLight>()->ambientColor = jScene["gameObjects"][i]["components"][j]["data"]["ambientColor"];
                    gameObject->GetComponent<SpotLight>()->specularColor = jScene["gameObjects"][i]["components"][j]["data"]["specularColor"];
                    gameObject->GetComponent<SpotLight>()->position = jScene["gameObjects"][i]["components"][j]["data"]["position"];
                    gameObject->GetComponent<SpotLight>()->direction = jScene["gameObjects"][i]["components"][j]["data"]["direction"];
                    gameObject->GetComponent<SpotLight>()->constant = jScene["gameObjects"][i]["components"][j]["data"]["constant"];
                    gameObject->GetComponent<SpotLight>()->linear = jScene["gameObjects"][i]["components"][j]["data"]["linear"];
                    gameObject->GetComponent<SpotLight>()->quadratic = jScene["gameObjects"][i]["components"][j]["data"]["quadratic"];
                    gameObject->GetComponent<SpotLight>()->cutOff = jScene["gameObjects"][i]["components"][j]["data"]["cutOff"];
                    gameObject->GetComponent<SpotLight>()->outerCutOff = jScene["gameObjects"][i]["components"][j]["data"]["outerCutOff"];
                }

                // Setup audio component
                if (jScene["gameObjects"][i]["components"][j]["name"] == "audio")
                {
                    gameObject->AddComponent<Audio>();
                    gameObject->GetComponent<Audio>()->musicPath = Tools::GetPathFromJsonString(jScene["gameObjects"][i]["components"][j]["data"]["musicPath"]);
                    gameObject->GetComponent<Audio>()->SetVolume(jScene["gameObjects"][i]["components"][j]["data"]["volume"]);
                    gameObject->GetComponent<Audio>()->SetLoop(jScene["gameObjects"][i]["components"][j]["data"]["isLooping"]);
                    gameObject->GetComponent<Audio>()->StopMusic(jScene["gameObjects"][i]["components"][j]["data"]["isPlaying"]);
                }

                // Setup meshRenderer component
                if (jScene["gameObjects"][i]["components"][j]["name"] == "meshRenderer")
                {
                    Shader* shader = resourceManager->Get<Shader>(ResourceManager::GetDefaultShader());
                    Texture* texture = resourceManager->Get<Texture>(ResourceManager::GetDefaultTexture());
                    Model* model = resourceManager->Get<Model>(ResourceManager::GetDefaultModel());
                    gameObject->AddComponent(new MeshRenderer(new Mesh(model, texture, shader)));
                }
            }
        }
        else if (jScene["gameObjects"][i]["name"] == "World")    // Setup World seperatly
        {
            // Setup guids
            Guid worldGuid;
            worldGuid.FromString(jScene["gameObjects"][i]["guid"]);
            scene->GetWorld()->guid = worldGuid;
            Guid worldTransformGuid;
            worldTransformGuid.FromString(jScene["gameObjects"][i]["components"][0]["data"]["guid"]);
            scene->GetWorld()->transform->guid = worldTransformGuid;
            
            scene->GetWorld()->transform->localPosition = jScene["gameObjects"][i]["components"][0]["data"]["localPosition"];
            scene->GetWorld()->transform->rotation = jScene["gameObjects"][i]["components"][0]["data"]["rotation"];
            scene->GetWorld()->transform->scaling = jScene["gameObjects"][i]["components"][0]["data"]["scaling"];

            // Setup world directionalLight
            if (jScene["gameObjects"][i]["components"].size() > 1)
            {
                for (int j = 0; j < jScene["gameObjects"][j]["components"].size(); j++)
                {
                    if (jScene["gameObjects"][i]["components"][j]["name"] == "directionalLight")
                    {
                        scene->GetWorld()->AddComponent<DirectionalLight>();
                        scene->GetWorld()->GetComponent<DirectionalLight>()->id = jScene["gameObjects"][i]["components"][j]["data"]["id"];
                        scene->GetWorld()->GetComponent<DirectionalLight>()->diffuseColor = jScene["gameObjects"][i]["components"][j]["data"]["diffuseColor"];
                        scene->GetWorld()->GetComponent<DirectionalLight>()->ambientColor = jScene["gameObjects"][i]["components"][j]["data"]["ambientColor"];
                        scene->GetWorld()->GetComponent<DirectionalLight>()->specularColor = jScene["gameObjects"][i]["components"][j]["data"]["specularColor"];
                        scene->GetWorld()->GetComponent<DirectionalLight>()->direction = jScene["gameObjects"][i]["components"][j]["data"]["direction"];
                    }
                }
            }
        }
    }

    for (int i = 0; i < jScene["terrains"].size(); i++)
    {
        // If the terrain is a default terrain
        if (Tools::GetPathFromJsonString(jScene["terrains"][i]["noisemapPath"]) == "")
        {
            std::string name = "terraind";
            Transform* transform = new Transform();
            DefaultTerrain* terrain = new DefaultTerrain(transform, name);
            terrain->Init(
                jScene["terrains"][i]["xResolution"],
                jScene["terrains"][i]["zResolution"],
                jScene["terrains"][i]["size"]
            );
            CreateTerrainFromFile(terrain, scene, jScene, i);
        }
        // If the terrain is a noisemap terrain
        else
        {
            std::string name = "terrainn";
            Transform* transform = new Transform();
            NoisemapTerrain* terrain = new NoisemapTerrain(transform, name);
            terrain->Init(
                Tools::GetPathFromJsonString(jScene["terrains"][i]["noisemapPath"]).c_str(),
                jScene["terrains"][i]["size"],
                jScene["terrains"][i]["amplitude"]
            );
            CreateTerrainFromFile(terrain, scene, jScene, i);
        }
    }
    
    m_scenes.push_back(scene);    
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

void SceneManager::SetCurrentScene(Scene* _scene)
{
    m_currentScene = _scene;
}

void SceneManager::CreateTerrainFromFile(Terrain* _terrain, Scene* _scene, json& _jScene, int _i)
{
    // Setup guid
    Guid terrainGuid;
    terrainGuid.FromString(_jScene["terrains"][_i]["guid"]);
    _terrain->guid = terrainGuid;

    _terrain->name = _jScene["terrains"][_i]["name"];

    _scene->AddTerrain(_terrain);  
}
