#include "golemEngine.h"

#include "Wrappers/graphicWrapper.h"
#include "Wrappers/windowWrapper.h"
#include "Resource/sceneManager.h"
#include "Core/scene.h"
#include "Core/camera.h"
#include "Inputs/inputManager.h"
#include "vector4.h"
#include "Reflection/classesManager.h"

#include "SystemTable.h"
#include "RuntimeObjectSystem.h"
#include "StdioLogSystem.h"
#include "rccppMainLoop.h"

static IRuntimeObjectSystem* g_pRuntimeObjectSystem;
static StdioLogSystem           g_Logger;
static SystemTable              g_SystemTable;

bool RCCppInit()
{
    g_pRuntimeObjectSystem = new RuntimeObjectSystem;
    if (!g_pRuntimeObjectSystem->Initialise(&g_Logger, &g_SystemTable))
    {
        delete g_pRuntimeObjectSystem;
        g_pRuntimeObjectSystem = NULL;
        return false;
    }

    // ensure include directories are set - use location of this file as starting point
    FileSystemUtils::Path basePath = g_pRuntimeObjectSystem->FindFile(__FILE__).ParentPath();
    FileSystemUtils::Path imguiIncludeDir = basePath / "imgui";
    g_pRuntimeObjectSystem->AddIncludeDir(imguiIncludeDir.c_str());
    g_pRuntimeObjectSystem->AddIncludeDir("C:\\dev\\2023_gp_2027_gp_2027_projet_moteur-golem\\GolemEngine\\GameClasses");
    return true;
}

void RCCppUpdate()
{
    //check status of any compile
    if (g_pRuntimeObjectSystem->GetIsCompiledComplete())
    {
        // load module when compile complete
        g_pRuntimeObjectSystem->LoadCompiledModule();
    }

    if (!g_pRuntimeObjectSystem->GetIsCompiling())
    {
        float deltaTime = 1.0f / ImGui::GetIO().Framerate;
        g_pRuntimeObjectSystem->GetFileChangeNotifier()->Update(deltaTime);
    }
}

void RCCppCleanup()
{
    delete g_pRuntimeObjectSystem;
}

void GolemEngine::Init()
{
    RCCppInit();
    ClassesManager::AddAllClasses();
    SceneManager::Init();
    InputManager::Init(WindowWrapper::window);
    m_camera = new Camera();
}

void GolemEngine::UpdateDeltaTime()
{
    static float lastFrame = 0;
    m_deltaTime = static_cast<float>(glfwGetTime()) - lastFrame;
    lastFrame = static_cast<float>(glfwGetTime());
}

void GolemEngine::ProcessInput()
{
    if (InputManager::IsKeyPressed(KEY_ESCAPE))
    {
        glfwSetWindowShouldClose(WindowWrapper::window, true);
    }
}

void GolemEngine::Update()
{
    RCCppUpdate();
    g_SystemTable.pRCCppMainLoopI->MainLoop();

    UpdateDeltaTime();
    // Bind next framebuffer to the scene buffer
    GraphicWrapper::BindFramebuffer();
    // Assign background color and clear previous scene buffers
    GraphicWrapper::SetBackgroundColor(Vector4(0.2f, 0.3f, 0.3f, 1.0f));
    // Clear buffer
    GraphicWrapper::ClearBuffer();
    // Render the scene to the framebuffer
    //for (int i = 0; i < texList.size(); i++)
    //{
    SceneManager::GetCurrentScene()->Update(WindowWrapper::GetScreenSize().x, WindowWrapper::GetScreenSize().y, m_camera);
    //}

    // Go back to original framebuffer
    GraphicWrapper::UnbindFramebuffer();
}

void GolemEngine::Close()
{
    glfwTerminate();
    RCCppCleanup();
}

Camera* GolemEngine::GetCamera()
{
    return m_camera;
}

float GolemEngine::GetDeltaTime()
{
    return m_deltaTime;
}

float GolemEngine::GetTime()
{
    return static_cast<float>(glfwGetTime());
}