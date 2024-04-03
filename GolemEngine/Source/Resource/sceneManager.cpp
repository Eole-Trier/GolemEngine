#include "Resource/sceneManager.h"

#include <nlohmann/json.hpp>
#include <fstream>

#include "Resource/tools.h"
#include "Wrappers/graphicWrapper.h"
#include "Wrappers/windowWrapper.h"

using json = nlohmann::json;


class TestClass
{
public:
    std::string name;
    int age;
    std::vector<int> data; 

    TestClass() {}

    NLOHMANN_DEFINE_TYPE_INTRUSIVE(TestClass, name, age, data);
};


void SceneManager::Init()
{
    m_scenes.push_back(new Scene("Scene_0"));
    LoadScene();
    InitScene();
}

void SceneManager::InitScene()
{
    // Init scene
    m_currentScene->Init();
    // Create a framebuffer and pass the scene in it to be used in the viewport 
    GraphicWrapper::CreateFramebuffer(WindowWrapper::GetScreenSize().x, WindowWrapper::GetScreenSize().y);
}

void SceneManager::SaveScene()
{
    std::cout << "Saved scene" << std::endl;

    TestClass testClass1;
    testClass1.name = "Maxime";
    std::vector<int> data = {1, 2, 3};
    testClass1.age = 19;
    
    nlohmann::ordered_json jScene;
    jScene["name"] = testClass1.name;
    jScene["data"] = testClass1.data;
    jScene["age"] = testClass1.age;
    std::fstream File;
    File.open(R"(C:\Users\m.leguevacques\Documents\Projects\2023_gp_2027_gp_2027_projet_moteur-golem\Saves\Scenes\file.json)", std::ios::out);
    File << jScene.dump(2);

}

void SceneManager::LoadScene()
{
    std::cout << "Loaded scene" << std::endl;

    m_currentScene = m_scenes[0];    std::cout << "Saved scene" << std::endl;

    // TestClass testClass2;
    //
    // std::fstream File;
    // File.open(R"(C:\Users\m.leguevacques\Documents\Projects\2023_gp_2027_gp_2027_projet_moteur-golem\Saves\Scenes\file.json)", std::ios::in);
    // json jScene;
    // File >> jScene;
    // testClass2 = jScene;
    //
    // testClass2.name = jScene["name"];
    // testClass2.data[0] = jScene["data"][0];
    // testClass2.age = jScene["age"];
    //
    // std::cout << testClass2.name << " " << testClass2.data[0] << " " << testClass2.data[1] << " " << testClass2.data[2] << " " << testClass2.age << std::endl;
}

void SceneManager::CreateScene(std::string _sceneName)
{
    m_scenes.push_back(new Scene(_sceneName));
}

Scene* SceneManager::GetCurrentScene()
{
    return m_currentScene;
}


