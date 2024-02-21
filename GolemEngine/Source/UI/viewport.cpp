#include "UI/viewport.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"
#include "vector2.h"

Viewport::Viewport() {}

Viewport::~Viewport() {}

void Viewport::Render(Scene* _scene)
{
    ImGui::Begin("Viewport");
    ImGui::Image((ImTextureID)_scene->textureId, ImGui::GetContentRegionAvail());
    ImGui::End();
}