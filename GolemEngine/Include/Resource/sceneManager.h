#pragma once

#include <vector>
#include <string>
#include <nlohmann/json.hpp>


#include "dll.h"
#include "Core/scene.h"

using json = nlohmann::json;


class GOLEM_ENGINE_API SceneManager
{
private:
    static inline std::vector<Scene*> m_scenes;
    static inline Scene* m_currentScene = nullptr;
    
private:
    // Private constructors and destructor to make static class
    SceneManager() = delete;
    SceneManager(SceneManager& _other) = delete;
    SceneManager(SceneManager&& _other) = delete;
    SceneManager& operator=(SceneManager& _other) = delete;
    SceneManager& operator=(SceneManager&& _other) = delete;
    void operator=(const SceneManager&) = delete;
    ~SceneManager() = delete;

public:
    static void Init();

    static void SaveScene();
    static void LoadScene(int _id);
    static void CreateScene(std::string _sceneName);
    static void CreateSceneFromFile(std::string _sceneFileName);
    static void SetupWorldFromJson(Scene* _scene, json _jScene, int _i);
    static void SetupGameObjectsFromJson(Scene* _scene, json _jScene, int _i);
    static void SetupDefaultTerrainsFromJson(Scene* _scene, json _jScene, int _i);
    static void SetupNoisemapTerrainsFromJson(Scene* _scene, json _jScene, int _i);

    static Scene* GetCurrentScene();
    static Scene* GetScene(int _id);
    static int GetSceneCount();
    
    static void SetCurrentScene(Scene* _scene);
};