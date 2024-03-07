#pragma once
#include "dll.h"
#include <string>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "imgui.h"

using GolemID = ImGuiID;
using GolemIO = ImGuiIO;
using GolemVec2 = ImVec2;
using GolemVec4 = ImVec4;
using GolemStyle = ImGuiStyle;

class GOLEM_ENGINE_API InterfaceWrapper
{
public:
	static InterfaceWrapper* GetInstance();

	void Init(GLFWwindow* _window);
	void NewFrameImGui();
	void StyleColorsDark(GolemStyle* _dst = NULL);
public:
	GolemIO& GetIO();
	GolemStyle& GetStyle();

	GolemID GetID(const char* _strId);                                      
	GolemID GetID(const char* _strIdBegin, const char* _strIdEnd);
	GolemID GetID(const void* _ptrId);

	ImGuiViewport* GetMainViewport();
	ImDrawData* GetDrawData();

	ImGuiContext* CreateContext(ImFontAtlas* _sharedFontAtlas = NULL);

public:
	void NewFrame();

	void Begin(const char* _name, bool* _open = (bool*)0, ImGuiWindowFlags flags = 0);

	void SetNextWindowPos(const GolemVec2& _pos, ImGuiCond _cond = 0, const GolemVec2& _pivot = GolemVec2(0, 0));
	void SetNextWindowSize(const GolemVec2& _size, ImGuiCond _cond = 0);
	void SetNextWindowViewport(GolemID _viewportId);

	void DockSpace(GolemID _id, const GolemVec2& _size = GolemVec2(0, 0), ImGuiDockNodeFlags _flags = 0, const ImGuiWindowClass* _windowClass = NULL);
	void DockBuilderAddNode(GolemID _id = 0U, ImGuiDockNodeFlags _flags = 0);
	void DockBuilderSetNodeSize(GolemID _id, GolemVec2 _size);
	void DockBuilderSplitNode(GolemID _id, ImGuiDir _splitDir, float _sizeRatioForNodeAtDir, GolemID* _outIdAtDir, GolemID* _outIdAtOppositeDir);
	void DockBuilderDockWindow(const char* _windowName, GolemID _id);
	void DockBuilderFinish(GolemID _id);

	void PushStyleVar(ImGuiStyleVar _idx, float _val);
	void PushStyleVar(ImGuiStyleVar _idx, const GolemVec2& _val);

	void PopStyleVar(int _count = 1);

	void UpdatePlatformWindows();
	void RenderPlatformWindowsDefault(void* _platformRenderArg = NULL, void* _rendererRenderArg = NULL);

	void Dock();
	void Loop();
	void EditorStyle();

	void End();

	void Render();

public:
	bool SliderFloat(const char* _label, float* _v, float _vMin, float _vMax, const char* _format = "%.3f", ImGuiSliderFlags _flags = 0);
	bool SliderFloat2(const char* _label, float _v[2], float _vMin, float _vMax, const char* _format = "%.3f", ImGuiSliderFlags _flags = 0);
	bool SliderFloat3(const char* _label, float _v[3], float _vMin, float _vMax, const char* _format = "%.3f", ImGuiSliderFlags _flags = 0);
	bool SliderFloat4(const char* _label, float _v[4], float _vMin, float _vMax, const char* _format = "%.3f", ImGuiSliderFlags _flags = 0);

private:
	InterfaceWrapper();
	~InterfaceWrapper();

	static InterfaceWrapper* m_instancePtr;

	InterfaceWrapper(const InterfaceWrapper& imGuiWrapper) = delete;
	const InterfaceWrapper& operator=(const InterfaceWrapper& imGuiWrapper) = delete;
};