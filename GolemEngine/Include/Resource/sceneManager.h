#pragma once

#include <vector>
#include <string>

#include "dll.h"
#include "Core/scene.h"


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
    static void CreateScene(std::string _sceneName);
    static void LoadScene(int _id);
    
    static Scene* GetCurrentScene();
    static Scene* GetScene(int _id);
    static int GetSceneCount();
};