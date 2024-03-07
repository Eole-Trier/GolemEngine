#pragma once
#include "dll.h"
#include <string>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "imgui.h"

// Rename the ImGuiAPI by Golem InterfaceWrapper
using GolemID = ImGuiID;
using GolemIO = ImGuiIO;
using GolemVec2 = ImVec2;
using GolemVec4 = ImVec4;
using GolemStyle = ImGuiStyle;
using GolemDrawData = ImDrawData;
using GolemViewport = ImGuiViewport;
using GolemGuiContext = ImGuiContext;
using GolemDockNodeFlags_ = ImGuiDockNodeFlags_;
using GolemTextureID = ImTextureID;

class GOLEM_ENGINE_API InterfaceWrapper
{
public:
	static InterfaceWrapper* GetInstance();

	void Init(GLFWwindow* _window);
	void NewFrameImGui();
	void StyleColorsDark(GolemStyle* _dst = NULL);

public:
	// For creating context
	GolemIO& GetIO();
	GolemStyle& GetStyle();

	GolemID GetID(const char* _strId);                                      
	GolemID GetID(const char* _strIdBegin, const char* _strIdEnd);
	GolemID GetID(const void* _ptrId);

	GolemViewport* GetMainViewport();
	GolemDrawData* GetDrawData();

	GolemGuiContext* CreateContext(ImFontAtlas* _sharedFontAtlas = NULL);

public:
	// For creating window and dock
	// Some settings of ui
	void NewFrame();

	void Begin(const char* _name, bool* _open = (bool*)0, ImGuiWindowFlags flags = 0);
	void End();
	void Render();
	void EditorStyle();

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


public:
	// Basic Functions
	bool SliderFloat(const char* _label, float* _v, float _vMin, float _vMax, const char* _format = "%.3f", ImGuiSliderFlags _flags = 0);
	bool SliderFloat2(const char* _label, float _v[2], float _vMin, float _vMax, const char* _format = "%.3f", ImGuiSliderFlags _flags = 0);
	bool SliderFloat3(const char* _label, float _v[3], float _vMin, float _vMax, const char* _format = "%.3f", ImGuiSliderFlags _flags = 0);
	bool SliderFloat4(const char* _label, float _v[4], float _vMin, float _vMax, const char* _format = "%.3f", ImGuiSliderFlags _flags = 0);

	bool Button(const char* _label, const GolemVec2& _size = GolemVec2(0, 0));
	void Image(GolemTextureID _textureId, 
		const GolemVec2& _imageSize, const GolemVec2& _uv0 = GolemVec2(0, 0), const GolemVec2& _uv1 = GolemVec2(1, 1), 
		const GolemVec4& _tintCol = GolemVec4(1, 1, 1, 1), const GolemVec4& _borderCol = GolemVec4(0, 0, 0, 0));

	void Text(const char* _fmt, ...);

public:
	GolemVec2 GetContentRegionAvail();

private:
	InterfaceWrapper();
	~InterfaceWrapper();

	static InterfaceWrapper* m_instancePtr;

	InterfaceWrapper(const InterfaceWrapper& imGuiWrapper) = delete;
	const InterfaceWrapper& operator=(const InterfaceWrapper& imGuiWrapper) = delete;
};