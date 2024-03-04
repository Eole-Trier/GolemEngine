#include "UI/Windows/viewport.h"

#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"
#include "imgui_internal.h"
#include "golemEngine.h"

Viewport::Viewport() {}

Viewport::~Viewport() {}

void Viewport::Update(GolemEngine* _golemEngine)
{
    glEnable(GL_DEPTH_TEST);

    ImGui::Begin("Viewport");

    ImGui::Image((ImTextureID)_golemEngine->GetScene()->textureId, ImGui::GetContentRegionAvail());
    _golemEngine->GetScene()->camera.ProcessInput(_golemEngine->GetGLFWWindow(), _golemEngine->GetDeltaTime());
    ImGui::End();
}