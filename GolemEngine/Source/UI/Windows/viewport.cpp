#include "UI/Windows/viewport.h"

#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"
#include "golemEngine.h"
#include "Wrappers/openglWrapper.h"

Viewport::Viewport() {}

Viewport::~Viewport() {}

void Viewport::Update(GolemEngine* _golemEngine)
{
    glEnable(GL_DEPTH_TEST);

    ImGui::Begin("Viewport");
    //ImGui::Image((ImTextureID)_golemEngine->GetScene()->textureId, ImGui::GetContentRegionAvail());
    ImGui::Image((ImTextureID)OpenglWrapper::GetInstance()->GetTextureId(), ImGui::GetContentRegionAvail());
    _golemEngine->GetScene()->camera.ProcessInput(_golemEngine->GetGlfwWindow(), _golemEngine->GetDeltaTime());
    ImGui::End();
}