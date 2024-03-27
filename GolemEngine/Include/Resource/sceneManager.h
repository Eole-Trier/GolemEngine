#pragma once

#include <vector>

#include "dll.h"
#include "Viewport/scene.h"


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
    static void InitScene();
    static void Init();

    static Scene* GetCurrentScene();

    static void SetCurrentScene(int _sceneId);
};