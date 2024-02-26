#include "UI/Windows/viewport.h"

#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"
//#include "vector2.h"

Viewport::Viewport() {}

Viewport::~Viewport() {}

void Viewport::Update(Scene* _scene)
{
    glEnable(GL_DEPTH_TEST);

    ImGui::Begin("Viewport");
    ImGui::Image((ImTextureID)_scene->textureId, ImGui::GetContentRegionAvail());
    ImGui::End();
}