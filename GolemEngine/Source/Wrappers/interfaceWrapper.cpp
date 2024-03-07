#include "Wrappers/interfaceWrapper.h"
#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"
#include "imgui_internal.h"
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "Viewport/camera.h"

InterfaceWrapper* InterfaceWrapper::m_instancePtr = nullptr;

InterfaceWrapper* InterfaceWrapper::GetInstance()
{
    return m_instancePtr;
}

void InterfaceWrapper::SliderFloat(const char* _label, float* _v, float _vMin, float _vMax, const char* _format, ImGuiSliderFlags _flags)
{
    ImGui::SliderFloat(_label, _v, _vMin, _vMax, _format, _flags);
}

InterfaceWrapper::InterfaceWrapper() {}

InterfaceWrapper::~InterfaceWrapper() {}

void InterfaceWrapper::Init(GLFWwindow* _window)
{
    // Setup Imgui context
    IMGUI_CHECKVERSION();
    CreateContext();
    ImGuiIO& io = GetIO(); (void)io;
    io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;
    io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;

    // Setup style
    StyleColorsDark();

    // When viewports are enabled we tweak WindowRounding/WindowBg so platform windows can look identical to regular ones
    ImGuiStyle& style = GetStyle();
    if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
    {
        style.WindowRounding = 0.0f;
        style.Colors[ImGuiCol_WindowBg].w = 1.0f;
    }

    ImGui_ImplGlfw_InitForOpenGL(_window, true);
    ImGui_ImplOpenGL3_Init("#version 460");
}

void InterfaceWrapper::NewFrameImGui()
{
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    NewFrame();
}

void InterfaceWrapper::StyleColorsDark(ImGuiStyle* _dst)
{
    ImGui::StyleColorsDark(_dst);
}

ImGuiIO& InterfaceWrapper::GetIO()
{
    return(ImGui::GetIO());
}

ImGuiStyle& InterfaceWrapper::GetStyle()
{
    return(ImGui::GetStyle());
}

ImGuiID InterfaceWrapper::GetID(const char* _strId)
{
    return(ImGui::GetID(_strId));
}

ImGuiID InterfaceWrapper::GetID(const char* _strIdBegin, const char* _strIdEnd)
{
    return(ImGui::GetID(_strIdBegin, _strIdEnd));
}

ImGuiID InterfaceWrapper::GetID(const void* _ptrId)
{
    return(ImGui::GetID(_ptrId));
}

ImGuiViewport* InterfaceWrapper::GetMainViewport()
{
    return(ImGui::GetMainViewport());
}

ImDrawData* InterfaceWrapper::GetDrawData()
{
    return(ImGui::GetDrawData());
}

ImGuiContext* InterfaceWrapper::CreateContext(ImFontAtlas* _sharedFontAtlas)
{
    return(ImGui::CreateContext(_sharedFontAtlas));
}

void InterfaceWrapper::EditorStyle()
{
    ImGuiStyle& style = GetStyle();

    style.WindowRounding = 4;
    style.FrameRounding = 4;
    style.GrabRounding = 3;
    style.ScrollbarSize = 7;
    style.ScrollbarRounding = 0;
}

void InterfaceWrapper::End()
{
    ImGui::End();
}

void InterfaceWrapper::Render()
{
    ImGui::Render();
}

void InterfaceWrapper::NewFrame()
{
    ImGui::NewFrame();
}

void InterfaceWrapper::Begin(const char* _name, bool* _open, ImGuiWindowFlags flags)
{
    ImGui::Begin(_name, _open, flags);
}

void InterfaceWrapper::SetNextWindowPos(const ImVec2& _pos, ImGuiCond _cond, const ImVec2& _pivot)
{
    ImGui::SetNextWindowPos(_pos, _cond, _pivot);
}

void InterfaceWrapper::SetNextWindowSize(const ImVec2& _size, ImGuiCond _cond)
{
    ImGui::SetNextWindowSize(_size, _cond);
}

void InterfaceWrapper::SetNextWindowViewport(ImGuiID _viewportId)
{
    ImGui::SetNextWindowViewport(_viewportId);
}

void InterfaceWrapper::DockSpace(ImGuiID _id, const ImVec2& _size, ImGuiDockNodeFlags _flags, const ImGuiWindowClass* _windowClass)
{
    ImGui::DockSpace(_id, _size, _flags, _windowClass);
}

void InterfaceWrapper::DockBuilderAddNode(ImGuiID _id, ImGuiDockNodeFlags _flags)
{
    ImGui::DockBuilderAddNode(_id, _flags);
}

void InterfaceWrapper::DockBuilderSetNodeSize(ImGuiID _id, ImVec2 _size)
{
    ImGui::DockBuilderSetNodeSize(_id, _size);
}

void InterfaceWrapper::DockBuilderSplitNode(ImGuiID _id, ImGuiDir _splitDir, float _sizeRatioForNodeAtDir, ImGuiID* _outIdAtDir, ImGuiID* _outIdAtOppositeDir)
{
    ImGui::DockBuilderSplitNode(_id, _splitDir, _sizeRatioForNodeAtDir, _outIdAtDir, _outIdAtOppositeDir);
}

void InterfaceWrapper::DockBuilderDockWindow(const char* _windowName, ImGuiID _id)
{
    ImGui::DockBuilderDockWindow(_windowName, _id);
}

void InterfaceWrapper::DockBuilderFinish(ImGuiID _id)
{
    ImGui::DockBuilderFinish(_id);
}

void InterfaceWrapper::PushStyleVar(ImGuiStyleVar _idx, float _val)
{
    ImGui::PushStyleVar(_idx, _val);
}

void InterfaceWrapper::PushStyleVar(ImGuiStyleVar _idx, const ImVec2& _val)
{
    ImGui::PushStyleVar(_idx, _val);
}

void InterfaceWrapper::PopStyleVar(int _count)
{
    ImGui::PopStyleVar(_count);
}

void InterfaceWrapper::UpdatePlatformWindows()
{
    ImGui::UpdatePlatformWindows();
}

void InterfaceWrapper::RenderPlatformWindowsDefault(void* _platformRenderArg, void* _rendererRenderArg)
{
    ImGui::RenderPlatformWindowsDefault(_platformRenderArg, _rendererRenderArg);
}

void InterfaceWrapper::Dock()
{
    static bool dockspaceOpen = true;
    static bool optFullscreenPersistant = true;
    const bool optFullscreen = optFullscreenPersistant;

    ImGuiDockNodeFlags dockspaceFlags = ImGuiDockNodeFlags_None;
    if (optFullscreen)
    {
        dockspaceFlags |= ImGuiDockNodeFlags_PassthruCentralNode;
    }

    ImGuiWindowFlags windowFlags = ImGuiWindowFlags_MenuBar | ImGuiWindowFlags_NoDocking;
    if (optFullscreen)
    {
        const ImGuiViewport* viewport = GetMainViewport();
        SetNextWindowPos(viewport->WorkPos);
        SetNextWindowSize(viewport->WorkSize);
        SetNextWindowViewport(viewport->ID);
        PushStyleVar(ImGuiStyleVar_WindowRounding, 0.0f);
        PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0.0f);
        PushStyleVar(ImGuiStyleVar_WindowPadding, { 0, 0 });

        windowFlags |= ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove;
        windowFlags |= ImGuiWindowFlags_NoBringToFrontOnFocus | ImGuiWindowFlags_NoNavFocus | ImGuiWindowFlags_NoBackground;
    }

    Begin("DockSpace Demo", &dockspaceOpen, windowFlags);

    ImGuiID dockspace_id = GetID("DockSpace");
    DockSpace(dockspace_id, ImVec2(0.0f, 0.0f), dockspaceFlags);

    static bool init = true;
    if (init)
    {
        ImGuiID dock_id_left, dock_id_right;
        init = false;
        DockBuilderAddNode(dockspace_id);
        DockBuilderSetNodeSize(dockspace_id, ImGui::GetMainViewport()->Size);

        DockBuilderSplitNode(dockspace_id, ImGuiDir_Left, 0.8f, &dock_id_left, &dock_id_right);

        ImGuiID dock_id_topRight, dock_id_bottomRight;
        DockBuilderSplitNode(dock_id_right, ImGuiDir_Up, 0.8f, &dock_id_topRight, &dock_id_bottomRight);

        ImGuiID dock_id_topLeft, dock_id_bottomLeft;
        DockBuilderSplitNode(dock_id_left, ImGuiDir_Up, 0.8f, &dock_id_topLeft, &dock_id_bottomLeft);

        DockBuilderDockWindow("Basic_Actors", dock_id_topRight);
        DockBuilderDockWindow("File_Browser", dock_id_bottomLeft);
        DockBuilderDockWindow("Viewport", dock_id_topLeft);
        DockBuilderDockWindow("World_Actors", dock_id_topRight);
        DockBuilderDockWindow("Debug", dock_id_bottomRight);

        DockBuilderFinish(dockspace_id);
    }

    if (optFullscreen)
    {
        PopStyleVar(3);
    }
}

void InterfaceWrapper::Loop()
{
    ImGuiIO& io = GetIO();
    Camera* camera = Camera::instance;

    Begin("Camera");

    SliderFloat("Camera Move Speed : ",  &camera->movementSpeed, 0, 30.0f, 0);
    SliderFloat("Camera Move Sensitivity : ", &camera->mouseSensitivity, 0, 2.0f, 0);

    End();

    Render();

    ImGui_ImplOpenGL3_RenderDrawData(GetDrawData());

    if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
    {
        GLFWwindow* backup_current_context = glfwGetCurrentContext();
        UpdatePlatformWindows();
        RenderPlatformWindowsDefault();
        glfwMakeContextCurrent(backup_current_context);
    }
}

