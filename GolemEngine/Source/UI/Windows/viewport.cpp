#include "UI/Windows/viewport.h"

#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"
#include "golemEngine.h"
//#include "vector2.h"

Viewport::Viewport() {}

Viewport::~Viewport() {}

void Viewport::Update(GolemEngine* golemEngine)
{
    glEnable(GL_DEPTH_TEST);

    ImGui::Begin("Viewport");
    ImGui::Image((ImTextureID)golemEngine->GetScene()->textureId, ImGui::GetContentRegionAvail());
    golemEngine->GetScene()->camera.ProcessInput(golemEngine->GetGLFWWindow(), golemEngine->GetDeltaTime());
    ImGui::End();
}