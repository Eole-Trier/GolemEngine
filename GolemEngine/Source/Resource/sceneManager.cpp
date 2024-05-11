#include "Resource/sceneManager.h"

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

    SetupWorldFromJson(scene, jScene);
    SetupGameObjectsFromJson(scene, jScene);
    SetupDefaultTerrainsFromJson(scene, jScene);
    SetupNoisemapTerrainsFromJson(scene, jScene);
    
    m_scenes.push_back(scene);    
}

void SceneManager::SetupWorldFromJson(Scene* _scene, json _jsonFile)
{
    for (int i = 0; i < _jsonFile["gameObjects"].size(); i++)
    {
        if (_jsonFile["gameObjects"][i]["name"] == "World")
        {
            // Setup guids
            Guid worldGuid;
            worldGuid.FromString(_jsonFile["gameObjects"][i]["guid"]);
            _scene->GetWorld()->guid = worldGuid;
            Guid worldTransformGuid;
            worldTransformGuid.FromString(_jsonFile["gameObjects"][i]["components"][0]["data"]["guid"]);
            _scene->GetWorld()->transform->guid = worldTransformGuid;
            
            _scene->GetWorld()->transform->localPosition = _jsonFile["gameObjects"][i]["components"][0]["data"]["localPosition"];
            _scene->GetWorld()->transform->rotation = _jsonFile["gameObjects"][i]["components"][0]["data"]["rotation"];
            _scene->GetWorld()->transform->scaling = _jsonFile["gameObjects"][i]["components"][0]["data"]["scaling"];

            // Setup world directionalLight
            if (_jsonFile["gameObjects"][i]["components"].size() > 1)
            {
                for (int j = 0; j < _jsonFile["gameObjects"][j]["components"].size(); j++)
                {
                    if (_jsonFile["gameObjects"][i]["components"][j]["name"] == "directionalLight")
                    {
                        _scene->GetWorld()->AddComponent<DirectionalLight>();
                        _scene->GetWorld()->GetComponent<DirectionalLight>()->id = _jsonFile["gameObjects"][i]["components"][j]["data"]["id"];
                        _scene->GetWorld()->GetComponent<DirectionalLight>()->diffuseColor = _jsonFile["gameObjects"][i]["components"][j]["data"]["diffuseColor"];
                        _scene->GetWorld()->GetComponent<DirectionalLight>()->ambientColor = _jsonFile["gameObjects"][i]["components"][j]["data"]["ambientColor"];
                        _scene->GetWorld()->GetComponent<DirectionalLight>()->specularColor = _jsonFile["gameObjects"][i]["components"][j]["data"]["specularColor"];
                        _scene->GetWorld()->GetComponent<DirectionalLight>()->direction = _jsonFile["gameObjects"][i]["components"][j]["data"]["direction"];
                    }
                }
            }
        }
    }
}

void SceneManager::SetupGameObjectsFromJson(Scene* _scene, json _jsonFile)
{
    ResourceManager* resourceManager = ResourceManager::GetInstance();
    
    for (int i = 0; i < _jsonFile["gameObjecs"].size(); i++)
    {
        if (_jsonFile["gameObjects"][i]["name"] != "World" &&    // Check if the gameObject being created is not the World because World is created already on Scene constructor
            !_jsonFile["gameObjects"][i]["name"].is_null() &&
            _jsonFile["gameObjects"][i]["isTerrain"] == false)
        {
            GameObject* gameObject = new GameObject();
            gameObject->name = _jsonFile["gameObjects"][i]["name"];
            Guid gameObjectGuid;
            gameObjectGuid.FromString(_jsonFile["gameObjects"][i]["guid"]);
            gameObject->guid = gameObjectGuid;
            
            // Setup components
            for (int j = 0; j < _jsonFile["gameObjects"][i]["components"].size(); j++)
            {
                // Setup each component
                
                // Setup transform component
                if (_jsonFile["gameObjects"][i]["components"][j]["name"] == "transform")
                {
                    Guid gameObjectGuid;
                    gameObjectGuid.FromString(_jsonFile["gameObjects"][i]["components"][j]["data"]["guid"]);
                    gameObject->transform->guid = gameObjectGuid;
                    gameObject->transform->localPosition = _jsonFile["gameObjects"][i]["components"][j]["data"]["localPosition"];
                    gameObject->transform->rotation = _jsonFile["gameObjects"][i]["components"][j]["data"]["rotation"];
                    gameObject->transform->scaling = _jsonFile["gameObjects"][i]["components"][j]["data"]["scaling"];
                }
                // Setup directionalLight component
                // std::cout << _jsonFile["gameObjects"][i]["components"][j]["name"] << std::endl;
                if (_jsonFile["gameObjects"][i]["components"][j]["name"] == "directionalLight")
                {
                    gameObject->AddComponent<DirectionalLight>();
                    gameObject->GetComponent<DirectionalLight>()->id = _jsonFile["gameObjects"][i]["components"][j]["data"]["id"];
                    gameObject->GetComponent<DirectionalLight>()->diffuseColor = _jsonFile["gameObjects"][i]["components"][j]["data"]["diffuseColor"];
                    gameObject->GetComponent<DirectionalLight>()->ambientColor = _jsonFile["gameObjects"][i]["components"][j]["data"]["ambientColor"];
                    gameObject->GetComponent<DirectionalLight>()->specularColor = _jsonFile["gameObjects"][i]["components"][j]["data"]["specularColor"];
                    gameObject->GetComponent<DirectionalLight>()->direction = _jsonFile["gameObjects"][i]["components"][j]["data"]["direction"];
                }
                
                // Setup pointLight component
                if (_jsonFile["gameObjects"][i]["components"][j]["name"] == "pointLight")
                {
                    gameObject->AddComponent<PointLight>();
                    gameObject->GetComponent<PointLight>()->id = _jsonFile["gameObjects"][i]["components"][j]["data"]["id"];
                    gameObject->GetComponent<PointLight>()->diffuseColor = _jsonFile["gameObjects"][i]["components"][j]["data"]["diffuseColor"];
                    gameObject->GetComponent<PointLight>()->ambientColor = _jsonFile["gameObjects"][i]["components"][j]["data"]["ambientColor"];
                    gameObject->GetComponent<PointLight>()->specularColor = _jsonFile["gameObjects"][i]["components"][j]["data"]["specularColor"];
                    gameObject->GetComponent<PointLight>()->position = _jsonFile["gameObjects"][i]["components"][j]["data"]["position"];
                    gameObject->GetComponent<PointLight>()->constant = _jsonFile["gameObjects"][i]["components"][j]["data"]["constant"];
                    gameObject->GetComponent<PointLight>()->linear = _jsonFile["gameObjects"][i]["components"][j]["data"]["linear"];
                    gameObject->GetComponent<PointLight>()->quadratic = _jsonFile["gameObjects"][i]["components"][j]["data"]["quadratic"];
                }
                
                // Setup spotLight component
                if (_jsonFile["gameObjects"][i]["components"][j]["name"] == "spotLight")
                {
                    gameObject->AddComponent<SpotLight>();
                    gameObject->GetComponent<SpotLight>()->id = _jsonFile["gameObjects"][i]["components"][j]["data"]["id"];
                    gameObject->GetComponent<SpotLight>()->diffuseColor = _jsonFile["gameObjects"][i]["components"][j]["data"]["diffuseColor"];
                    gameObject->GetComponent<SpotLight>()->ambientColor = _jsonFile["gameObjects"][i]["components"][j]["data"]["ambientColor"];
                    gameObject->GetComponent<SpotLight>()->specularColor = _jsonFile["gameObjects"][i]["components"][j]["data"]["specularColor"];
                    gameObject->GetComponent<SpotLight>()->position = _jsonFile["gameObjects"][i]["components"][j]["data"]["position"];
                    gameObject->GetComponent<SpotLight>()->direction = _jsonFile["gameObjects"][i]["components"][j]["data"]["direction"];
                    gameObject->GetComponent<SpotLight>()->constant = _jsonFile["gameObjects"][i]["components"][j]["data"]["constant"];
                    gameObject->GetComponent<SpotLight>()->linear = _jsonFile["gameObjects"][i]["components"][j]["data"]["linear"];
                    gameObject->GetComponent<SpotLight>()->quadratic = _jsonFile["gameObjects"][i]["components"][j]["data"]["quadratic"];
                    gameObject->GetComponent<SpotLight>()->cutOff = _jsonFile["gameObjects"][i]["components"][j]["data"]["cutOff"];
                    gameObject->GetComponent<SpotLight>()->outerCutOff = _jsonFile["gameObjects"][i]["components"][j]["data"]["outerCutOff"];
                }

                // Setup audio component
                if (_jsonFile["gameObjects"][i]["components"][j]["name"] == "audio")
                {
                    gameObject->AddComponent<Audio>();
                    gameObject->GetComponent<Audio>()->musicPath = Tools::GetPathFromJsonString(_jsonFile["gameObjects"][i]["components"][j]["data"]["musicPath"]);
                    gameObject->GetComponent<Audio>()->SetVolume(_jsonFile["gameObjects"][i]["components"][j]["data"]["volume"]);
                    gameObject->GetComponent<Audio>()->SetLoop(_jsonFile["gameObjects"][i]["components"][j]["data"]["isLooping"]);
                    gameObject->GetComponent<Audio>()->StopMusic(_jsonFile["gameObjects"][i]["components"][j]["data"]["isPlaying"]);
                }

                // Setup meshRenderer component
                if (_jsonFile["gameObjects"][i]["components"][j]["name"] == "meshRenderer")
                {
                    Shader* shader = resourceManager->Get<Shader>(ResourceManager::GetDefaultShader());
                    Texture* texture = resourceManager->Get<Texture>(ResourceManager::GetDefaultTexture());
                    Model* model = resourceManager->Get<Model>(ResourceManager::GetDefaultModel());
                    gameObject->AddComponent(new MeshRenderer(new Mesh(model, texture, shader)));
                }
            }
        }
    }
}

void SceneManager::SetupDefaultTerrainsFromJson(Scene* _scene, json _jsonFile)
{
    for (int i = 0; i < _jsonFile["gameObjects"].size(); i++)
    {
        if (_jsonFile["gameObjects"][i]["name"] != "World" &&
            !_jsonFile["gameObjects"][i]["name"].is_null() &&
            _jsonFile["gameObjects"][i]["isTerrain"] == true &&
            _jsonFile["gameObjects"][i]["terrainData"]["noisemapPath"] == "")
        {
            std::string name = _jsonFile["gameObjects"][i]["name"];
            Guid terrainGuid;
            terrainGuid.FromString(_jsonFile["gameObjects"][i]["guid"]);

            Guid terrainTranformGuid;
            Vector3 localPosition;
            Vector3 rotation;
            Vector3 scaling;

            for (int j = 0; j < _jsonFile["gameObjects"][i]["components"].size(); j++)
            {
                // Setup transform
                if (_jsonFile["gameObjects"][i]["components"][j]["name"] == "transform")
                {
                    terrainTranformGuid.FromString(_jsonFile["gameObjects"][i]["components"][j]["data"]["guid"]);
                    localPosition = _jsonFile["gameObjects"][i]["components"][j]["data"]["localPosition"];
                    rotation = _jsonFile["gameObjects"][i]["components"][j]["data"]["rotation"];
                    scaling = _jsonFile["gameObjects"][i]["components"][j]["data"]["scaling"];
                }
            }
            Transform* transform = new Transform();
            transform->localPosition = localPosition;
            transform->rotation = rotation;
            transform->scaling = scaling;
            DefaultTerrain* defaultTerrain = new DefaultTerrain(name, transform);
            defaultTerrain->xResolution = _jsonFile["gameObjects"][i]["terrainData"]["xResolution"];
            defaultTerrain->zResolution = _jsonFile["gameObjects"][i]["terrainData"]["zResolution"];
        }
    }
}

void SceneManager::SetupNoisemapTerrainsFromJson(Scene* _scene, json _jsonFile)
{
    for (int i = 0; i < _jsonFile["gameObjects"].size(); i++)
    {
        if (_jsonFile["gameObjects"][i]["name"] != "World" &&
            !_jsonFile["gameObjects"][i]["name"].is_null() &&
            _jsonFile["gameObjects"][i]["isTerrain"] == true &&
            _jsonFile["gameObjects"][i]["terrainData"]["noisemapPath"] != "")
        {
            std::string name = _jsonFile["gameObjects"][i]["name"];
            Guid terrainGuid;
            terrainGuid.FromString(_jsonFile["gameObjects"][i]["guid"]);

            Guid terrainTranformGuid;
            Vector3 localPosition;
            Vector3 rotation;
            Vector3 scaling;

            for (int j = 0; j < _jsonFile["gameObjects"][i]["components"].size(); j++)
            {
                // Setup transform
                if (_jsonFile["gameObjects"][i]["components"][j]["name"] == "transform")
                {
                    terrainTranformGuid.FromString(_jsonFile["gameObjects"][i]["components"][j]["data"]["guid"]);
                    localPosition = _jsonFile["gameObjects"][i]["components"][j]["data"]["localPosition"];
                    rotation = _jsonFile["gameObjects"][i]["components"][j]["data"]["rotation"];
                    scaling = _jsonFile["gameObjects"][i]["components"][j]["data"]["scaling"];
                }
            }
            Transform* transform = new Transform();
            transform->guid = terrainTranformGuid;
            transform->localPosition = localPosition;
            transform->rotation = rotation;
            transform->scaling = scaling;
            NoisemapTerrain* noisemapTerrain = new NoisemapTerrain(name, transform);
            noisemapTerrain->xResolution = _jsonFile["gameObjects"][i]["terrainData"]["xResolution"];
            noisemapTerrain->zResolution = _jsonFile["gameObjects"][i]["terrainData"]["zResolution"];
        }
    }
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
