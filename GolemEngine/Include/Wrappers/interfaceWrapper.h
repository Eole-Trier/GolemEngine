#pragma once
#include "dll.h"
#include <string>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "imgui.h"

class GOLEM_ENGINE_API InterfaceWrapper
{
public:
	static InterfaceWrapper* GetInstance();

	void Init(GLFWwindow* _window);
	void NewFrameImGui();
	void StyleColorsDark(ImGuiStyle* _dst = NULL);
public:
	ImGuiIO& GetIO();
	ImGuiStyle& GetStyle();

	ImGuiID GetID(const char* _strId);                                      
	ImGuiID GetID(const char* _strIdBegin, const char* _strIdEnd);
	ImGuiID GetID(const void* _ptrId);

	ImGuiViewport* GetMainViewport();
	ImDrawData* GetDrawData();

	ImGuiContext* CreateContext(ImFontAtlas* _sharedFontAtlas = NULL);

public:
	void NewFrame();

	void Begin(const char* _name, bool* _open = (bool*)0, ImGuiWindowFlags flags = 0);

	void SetNextWindowPos(const ImVec2& _pos, ImGuiCond _cond = 0, const ImVec2& _pivot = ImVec2(0, 0));
	void SetNextWindowSize(const ImVec2& _size, ImGuiCond _cond = 0);
	void SetNextWindowViewport(ImGuiID _viewportId);

	void DockSpace(ImGuiID _id, const ImVec2& _size = ImVec2(0, 0), ImGuiDockNodeFlags _flags = 0, const ImGuiWindowClass* _windowClass = NULL);
	void DockBuilderAddNode(ImGuiID _id = 0U, ImGuiDockNodeFlags _flags = 0);
	void DockBuilderSetNodeSize(ImGuiID _id, ImVec2 _size);
	void DockBuilderSplitNode(ImGuiID _id, ImGuiDir _splitDir, float _sizeRatioForNodeAtDir, ImGuiID* _outIdAtDir, ImGuiID* _outIdAtOppositeDir);
	void DockBuilderDockWindow(const char* _windowName, ImGuiID _id);
	void DockBuilderFinish(ImGuiID _id);

	void PushStyleVar(ImGuiStyleVar _idx, float _val);
	void PushStyleVar(ImGuiStyleVar _idx, const ImVec2& _val);

	void PopStyleVar(int _count = 1);

	void UpdatePlatformWindows();
	void RenderPlatformWindowsDefault(void* _platformRenderArg = NULL, void* _rendererRenderArg = NULL);

	void Dock();
	void Loop();
	void EditorStyle();

	void End();

	void Render();

public:
	void SliderFloat(const char* _label, float* _v, float _vMin, float _vMax, const char* _format = "%.3f", ImGuiSliderFlags _flags = 0);

private:
	InterfaceWrapper();
	~InterfaceWrapper();

	static InterfaceWrapper* m_instancePtr;

	InterfaceWrapper(const InterfaceWrapper& imGuiWrapper) = delete;
	const InterfaceWrapper& operator=(const InterfaceWrapper& imGuiWrapper) = delete;
};