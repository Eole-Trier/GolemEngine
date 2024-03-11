#include "Wrappers/interfaceWrapper.h"

#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"
#include "imgui_internal.h"
#include "Viewport/camera.h"

InterfaceWrapper* InterfaceWrapper::m_instancePtr = nullptr; // Instantiation InterfaceWrapper API

InterfaceWrapper::InterfaceWrapper() {}

InterfaceWrapper::~InterfaceWrapper() {}

InterfaceWrapper* InterfaceWrapper::GetInstance()
{
    if (!m_instancePtr) {
        m_instancePtr = new InterfaceWrapper();
    }
    return m_instancePtr;
}

bool InterfaceWrapper::SliderFloat(const char* _label, float* _v, float _vMin, float _vMax, const char* _format, ImGuiSliderFlags _flags)
{
    return ImGui::SliderFloat(_label, _v, _vMin, _vMax, _format, _flags);
}

bool InterfaceWrapper::SliderFloat2(const char* _label, float _v[2], float _vMin, float _vMax, const char* _format, ImGuiSliderFlags _flags)
{
    return ImGui::SliderFloat2(_label, _v, _vMin, _vMax, _format, _flags);
}

bool InterfaceWrapper::SliderFloat3(const char* _label, float _v[3], float _vMin, float _vMax, const char* _format, ImGuiSliderFlags _flags)
{
    return ImGui::SliderFloat3(_label, _v, _vMin, _vMax, _format, _flags);
}

bool InterfaceWrapper::SliderFloat4(const char* _label, float _v[4], float _vMin, float _vMax, const char* _format, ImGuiSliderFlags _flags)
{
    return ImGui::SliderFloat4(_label, _v, _vMin, _vMax, _format, _flags);
}

bool InterfaceWrapper::SliderAngle(const char* _label, float* _vRad, float _vDegreesMin, float _vDegreesMax, const char* _format, ImGuiSliderFlags _flags)
{
    return ImGui::SliderAngle(_label, _vRad, _vDegreesMin, _vDegreesMax, _format, _flags);
}

bool InterfaceWrapper::Button(const char* _label, const GolemVec2& _size)
{
    return ImGui::Button(_label, _size);
}

bool InterfaceWrapper::InputText(const char* _label, char* _buf, size_t _bufSize, ImGuiInputTextFlags _flags, ImGuiInputTextCallback _callback, void* _userData)
{
    return ImGui::InputText(_label, _buf, _bufSize, _flags, _callback, _userData);
}

void InterfaceWrapper::Image(GolemTextureID _textureId, const GolemVec2& _imageSize, const GolemVec2& _uv0, const GolemVec2& _uv1, const GolemVec4& _tintCol, const GolemVec4& _borderCol)
{
    ImGui::Image(_textureId, _imageSize, _uv0, _uv1, _tintCol, _borderCol);
}

void InterfaceWrapper::Text(const char* _fmt, ...)
{
    va_list args;
    va_start(args, _fmt);
    ImGui::TextV(_fmt, args);
    va_end(args);
}

void InterfaceWrapper::SameLine(float _offsetFromStartX, float _spacing)
{
    ImGui::SameLine(_offsetFromStartX, _spacing);
}

GolemVec2 InterfaceWrapper::GetContentRegionAvail()
{
    return ImGui::GetContentRegionAvail();
}

void InterfaceWrapper::Init(GLFWwindow* _window)
{
    // Setup Imgui context
    IMGUI_CHECKVERSION();
    CreateContext();
    GolemIO& io = GetIO(); (void)io;
    io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;
    io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;

    // Setup style
    StyleColorsDark();

    // When viewports are enabled we tweak WindowRounding/WindowBg so platform windows can look identical to regular ones
    GolemStyle& style = GetStyle();
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

void InterfaceWrapper::StyleColorsDark(GolemStyle* _dst)
{
    ImGui::StyleColorsDark(_dst);
}

GolemIO& InterfaceWrapper::GetIO()
{
    return(ImGui::GetIO());
}

ImGuiStyle& InterfaceWrapper::GetStyle()
{
    return(ImGui::GetStyle());
}

GolemID InterfaceWrapper::GetID(const char* _strId)
{
    return(ImGui::GetID(_strId));
}

GolemID InterfaceWrapper::GetID(const char* _strIdBegin, const char* _strIdEnd)
{
    return(ImGui::GetID(_strIdBegin, _strIdEnd));
}

GolemID InterfaceWrapper::GetID(const void* _ptrId)
{
    return(ImGui::GetID(_ptrId));
}

GolemViewport* InterfaceWrapper::GetMainViewport()
{
    GolemViewport* viewport = ImGui::GetMainViewport();
    return viewport;
}

GolemDrawData* InterfaceWrapper::GetDrawData()
{
    return(ImGui::GetDrawData());
}

GolemGuiContext* InterfaceWrapper::CreateContext(ImFontAtlas* _sharedFontAtlas)
{
    return(ImGui::CreateContext(_sharedFontAtlas));
}

void InterfaceWrapper::EditorStyle()
{
    GolemStyle& style = GetStyle();

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
    GolemIO& io = GetIO();

    ImGui::Render();

    ImGui_ImplOpenGL3_RenderDrawData(GetDrawData());

    if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
    {
        GLFWwindow* backup_current_context = glfwGetCurrentContext();
        UpdatePlatformWindows();
        RenderPlatformWindowsDefault();
        glfwMakeContextCurrent(backup_current_context);
    }
}

void InterfaceWrapper::NewFrame()
{
    ImGui::NewFrame();
}

void InterfaceWrapper::Begin(const char* _name, bool* _open, ImGuiWindowFlags flags)
{
    ImGui::Begin(_name, _open, flags);
}

void InterfaceWrapper::SetNextWindowPos(const GolemVec2& _pos, ImGuiCond _cond, const GolemVec2& _pivot)
{
    ImGui::SetNextWindowPos(_pos, _cond, _pivot);
}

void InterfaceWrapper::SetNextWindowSize(const GolemVec2& _size, ImGuiCond _cond)
{
    ImGui::SetNextWindowSize(_size, _cond);
}

void InterfaceWrapper::SetNextWindowViewport(GolemID _viewportId)
{
    ImGui::SetNextWindowViewport(_viewportId);
}

void InterfaceWrapper::DockSpace(GolemID _id, const GolemVec2& _size, ImGuiDockNodeFlags _flags, const ImGuiWindowClass* _windowClass)
{
    ImGui::DockSpace(_id, _size, _flags, _windowClass);
}

void InterfaceWrapper::DockBuilderAddNode(GolemID _id, ImGuiDockNodeFlags _flags)
{
    ImGui::DockBuilderAddNode(_id, _flags);
}

void InterfaceWrapper::DockBuilderRemoveNode(GolemID _id)
{
    ImGui::DockBuilderRemoveNode(_id);
}

void InterfaceWrapper::DockBuilderSetNodeSize(GolemID _id, GolemVec2 _size)
{
    ImGui::DockBuilderSetNodeSize(_id, _size);
}

void InterfaceWrapper::DockBuilderSplitNode(GolemID _id, ImGuiDir _splitDir, float _sizeRatioForNodeAtDir, GolemID* _outIdAtDir, GolemID* _outIdAtOppositeDir)
{
    ImGui::DockBuilderSplitNode(_id, _splitDir, _sizeRatioForNodeAtDir, _outIdAtDir, _outIdAtOppositeDir);
}

void InterfaceWrapper::DockBuilderDockWindow(const char* _windowName, GolemID _id)
{
    ImGui::DockBuilderDockWindow(_windowName, _id);
}

void InterfaceWrapper::DockBuilderFinish(GolemID _id)
{
    ImGui::DockBuilderFinish(_id);
}

void InterfaceWrapper::PushStyleVar(ImGuiStyleVar _idx, float _val)
{
    ImGui::PushStyleVar(_idx, _val);
}

void InterfaceWrapper::PushStyleVar(ImGuiStyleVar _idx, const GolemVec2& _val)
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
