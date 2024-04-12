#pragma once

#include <vector>
#include <string>

#include "dll.h"
#include "Core/scene.h"


class GOLEM_ENGINE_API SceneManager
{
private:
public:
    static inline std::string m_defaultTexture = "default_texture";
    static inline std::string m_defaultModel = "default_model";
    static inline std::string m_defaultShader = "default_shader";
    static inline Scene* m_currentScene = nullptr;
    static inline std::vector<Scene*> m_scenes;
    
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
    static void CreateScene(std::string _sceneName);
    static void LoadScene(int _id);
    static void CreateAndLoadResources();

    
    static Scene* GetCurrentScene();
    static Scene* GetScene(int _id);
    static int GetSceneCount();
};