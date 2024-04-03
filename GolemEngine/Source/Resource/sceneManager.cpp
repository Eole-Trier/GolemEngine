#include "Resource/sceneManager.h"

#include <nlohmann/json.hpp>
#include <fstream>

#include "Utils/tools.h"
#include "Wrappers/graphicWrapper.h"
#include "Wrappers/windowWrapper.h"

using json = nlohmann::json;


class TestClass {
public:
    std::string name;
    int age;
    std::vector<int> data;
    std::string words;
    // Pointer member variable
    int* T;

    // Define serialization and deserialization functions manually
    void to_json(json& j) const {
        j = json{{"name", name}, {"age", age}, {"data", data}, {"words", words}};
        // Serialize the pointed-to value if it's not null
        if (T != nullptr) {
            j["T"] = *T;
        }
    }

    void from_json(const json& j) {
        j.at("name").get_to(name);
        j.at("age").get_to(age);
        j.at("data").get_to(data);
        j.at("words").get_to(words);
        // Deserialize the pointed-to value if it exists
        if (j.contains("T")) {
            T = new int(j.at("T").get<int>());
        } else {
            T = nullptr;
        }
    }

};

// // Custom serializer for std::vector<int>
// void to_json(json& j, const std::vector<int>& vec) {
//     j = json::array(); // Create a JSON array
//     for (const auto& elem : vec) {
//         j.push_back(elem); // Add each element of the vector to the JSON array
//     }
// }
//
// void from_json(const json& j, std::vector<int>& vec) {
//     if (j.is_array()) {
//         vec.clear(); // Clear the vector to avoid appending to existing data
//         for (const auto& elem : j) {
//             vec.push_back(elem); // Add each element of the JSON array to the vector
//         }
//     }
// }


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
    GraphicWrapper::CreateFramebuffer(GL_RGB, WindowWrapper::GetScreenSize().x, WindowWrapper::GetScreenSize().y);
}


// void SceneManager::SaveScene()
// {
//     // Create an instance of TestClass
//     TestClass* testClass1 = new TestClass();
//     testClass1->name = "Maxime";
//     testClass1->data = {1, 2, 3};
//     testClass1->age = 19;
//     testClass1->words = "Hello";
//     // Assuming T is properly allocated and assigned
//     testClass1->T = new int(42);
//
//     // Serialize the object pointed to by testClass1
//     json jScene;
//     testClass1->to_json((jScene));
//
//     std::fstream sceneFile;
//     sceneFile.open(R"(C:\Users\m.leguevacques\Documents\Projects\2023_gp_2027_gp_2027_projet_moteur-golem\Saves\Scenes\sceneFile.json)", std::ios::out);
//     if (!sceneFile.is_open()) {
//         std::cerr << "Error opening file." << std::endl;
//         delete testClass1; // Cleanup memory
//         return;
//     }
//     sceneFile << jScene.dump(2);
//
//     std::cout << "Saved Scene as :\n";
//     std::cout << jScene.dump(2) << std::endl;
//
//     // Remember to delete the dynamically allocated memory
//     delete testClass1;
//
// }

void SceneManager::SaveScene()
{
    json jScene;
    GetCurrentScene()->to_json(jScene);
    std::fstream sceneFile;
    sceneFile.open(R"(C:\Users\m.leguevacques\Documents\Projects\2023_gp_2027_gp_2027_projet_moteur-golem\Saves\Scenes\sceneFile.json)", std::ios::out);
    sceneFile << jScene.dump(2);

    std::cout << "Saved Scene as :\n";
    std::cout << jScene.dump(2) << std::endl;
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

/*void SceneManager::LoadScene(int _sceneId)
{
    m_currentScene = m_scenes[_sceneId];
}*/


Scene* SceneManager::GetCurrentScene()
{
    return m_currentScene;
}


