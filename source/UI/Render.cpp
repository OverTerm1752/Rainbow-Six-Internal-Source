#include "Render.h"

#include "imgui.h"
#include "imgui_impl_win32.h"
#include "imgui_impl_dx11.h"
#include "imgui_internal.h"

#include "Keybinds/Keybinds.h"
#include "../Config.h"

void Render::Fonts() noexcept
{
    ImGuiIO& io = ImGui::GetIO(); (void)io;
    io.ConfigFlags &= ImGuiConfigFlags_NavEnableKeyboard;
    io.ConfigFlags &= ImGuiConfigFlags_NavEnableGamepad;
    MenuFont = io.Fonts->AddFontFromFileTTF("c:\\Windows\\Fonts\\Arial.ttf", 18.0f, nullptr, io.Fonts->GetGlyphRangesJapanese());
    IM_ASSERT(MenuFont != nullptr);
};

void Render::Style() noexcept
{
    ImGuiStyle& style = ImGui::GetStyle();

    style.WindowPadding = ImVec2(0, 0);
    style.FramePadding = ImVec2(0, 0);
    style.CellPadding = ImVec2(0, 0);

    style.WindowRounding = 15.f;
    style.FrameRounding = 5.f;
    style.ChildRounding = 5.f;
    style.GrabRounding = 5.f;

    style.WindowBorderSize = 0.0f; // Pas de bordure de fenêtre
    style.FrameBorderSize = 0.0f;  // Pas de bordure autour des frames

    style.Colors[ImGuiCol_WindowBg] = ImVec4(0.14f, 0.14f, 0.15f, 0.92f);
    style.Colors[ImGuiCol_ChildBg] = ImVec4(0.f, 0.f, 0.f, 0.f);

    style.Colors[ImGuiCol_Text] = ImVec4(1.f, 1.f, 1.f, 1.f);
    style.Colors[ImGuiCol_TextDisabled] = ImVec4(1.f, 1.f, 1.f, 0.5f);
    style.Colors[ImGuiCol_TextSelectedBg] = ImVec4(AccentColor.Value.x, AccentColor.Value.y, AccentColor.Value.z, 0.2f);

    style.Colors[ImGuiCol_Button] = ImVec4(AccentColor.Value.x, AccentColor.Value.y, AccentColor.Value.z, 0.4f);
    style.Colors[ImGuiCol_ButtonHovered] = ImVec4(AccentColor.Value.x, AccentColor.Value.y, AccentColor.Value.z, 0.45f);
    style.Colors[ImGuiCol_ButtonActive] = ImVec4(AccentColor.Value.x, AccentColor.Value.y, AccentColor.Value.z, 0.5f);

    style.Colors[ImGuiCol_FrameBg] = ImVec4(AccentColor.Value.x, AccentColor.Value.y, AccentColor.Value.z, 0.4f);
    style.Colors[ImGuiCol_FrameBgHovered] = ImVec4(AccentColor.Value.x, AccentColor.Value.y, AccentColor.Value.z, 0.45f);
    style.Colors[ImGuiCol_FrameBgActive] = ImVec4(AccentColor.Value.x, AccentColor.Value.y, AccentColor.Value.z, 0.5f);

    style.Colors[ImGuiCol_SliderGrab] = ImVec4(AccentColor.Value.x, AccentColor.Value.y, AccentColor.Value.z, 1.f);
    style.Colors[ImGuiCol_SliderGrabActive] = ImVec4(AccentColor.Value.x, AccentColor.Value.y, AccentColor.Value.z, 1.f);

    style.Colors[ImGuiCol_CheckMark] = ImVec4(AccentColor.Value.x, AccentColor.Value.y, AccentColor.Value.z, 1.f);

    style.Colors[ImGuiCol_Separator] = ImVec4(AccentColor.Value.x, AccentColor.Value.y, AccentColor.Value.z, 0.4f);
}

void Render::Menu() noexcept
{
    ImGui::GetIO().FontGlobalScale = Size / 100.f;
    ImGui::SetNextWindowSize(ImVec2(SCALE(700.f), SCALE(400.f)));
    ImGui::Begin("Main Window", nullptr, ImGuiWindowFlags_NoDecoration, true);
    {
        ImGui::SetCursorPos(ImVec2(SCALE(10.f), SCALE(10.f)));
        ImGui::BeginChild("ButtonsChild", ImVec2(SCALE(150.f), SCALE(380.f)));
        {
            for (const auto& button : channelButtons) {
                if (ImGui::Button(button.second, ImVec2(SCALE(150.f), SCALE(80.f)))) {
                    SelectedChanel = button.first;
                }
            };
        };
        ImGui::EndChild();

        ImGui::PushStyleColor(ImGuiCol_ChildBg, ImVec4(AccentColor.Value.x, AccentColor.Value.y, AccentColor.Value.z, 0.1f));
        ImGui::SetCursorPos(ImVec2(SCALE(170.f), SCALE(10.f)));
        ImGui::BeginChild("TopChild", ImVec2(SCALE(520.f), SCALE(30.f)));
        {
            ImGui::SetCursorPos(ImVec2(SCALE(10.f), SCALE(5.f)));
            ImGui::SetNextItemWidth(SCALE(500.f));
            ImGui::InputTextWithHint("##Search", "Search", searchBuffer, IM_ARRAYSIZE(searchBuffer));
            if (strlen(searchBuffer) > 0) {
                SelectedChanel = SEARCH;
            }
            else if (strlen(searchBuffer) == 0 && SelectedChanel == SEARCH) {
                SelectedChanel = AIMBOT;
            }
        }
        ImGui::EndChild();
        ImGui::PopStyleColor();


        ImGui::SetCursorPos(ImVec2(SCALE(170.f), SCALE(50.f)));
        ImGui::BeginChild("CenterChild", ImVec2(SCALE(520.f), SCALE(340.f)));
        {
            switch (SelectedChanel)
            {
            case AIMBOT:
                ImGui::Checkbox("Enabled", &config->aimbot.Enabled);
                //ImGui::Checkbox("Visible Only", &config->aimbot.VisibleOnly);
                ImGui::SliderFloat("Fov", &config->aimbot.Fov, 10.f, 300.f, "%1.f");
                ImGui::SliderInt("Speed", &config->aimbot.Speed, 1, 20);
                break;
            case VISUALS:
                ImGui::Checkbox("Enabled", &config->visuals.Enabled);
                ImGui::Checkbox("Box", &config->visuals.Box.first);
                ImGui::SameLine();
                ImGui::ColorEdit4("Box Color", (float*)&config->visuals.Box.second, ImGuiColorEditFlags_NoLabel | ImGuiColorEditFlags_NoInputs);
                ImGui::Checkbox("Skeleton", &config->visuals.Skeleton.first);
                ImGui::SameLine();
                ImGui::ColorEdit4("Skeleton Visible Color", (float*)&config->visuals.Skeleton.second.first, ImGuiColorEditFlags_NoLabel | ImGuiColorEditFlags_NoInputs);
                ImGui::SameLine();
                ImGui::ColorEdit4("Skeleton Invisible Color", (float*)&config->visuals.Skeleton.second.second, ImGuiColorEditFlags_NoLabel | ImGuiColorEditFlags_NoInputs);
                ImGui::Checkbox("Name", &config->visuals.Name.first);
                ImGui::SameLine();
                ImGui::ColorEdit4("Name Color", (float*)&config->visuals.Name.second, ImGuiColorEditFlags_NoLabel | ImGuiColorEditFlags_NoInputs);
                ImGui::Checkbox("Out Of View Arrow", &config->visuals.OutOfViewArrow.first);
                ImGui::SameLine();
                ImGui::ColorEdit4("Out Of View Arrow Color", (float*)&config->visuals.OutOfViewArrow.second, ImGuiColorEditFlags_NoLabel | ImGuiColorEditFlags_NoInputs);
                ImGui::Separator();
                ImGui::Checkbox("No Light", &config->visuals.Light);
                ImGui::Checkbox("No Model", &config->visuals.Model);
                ImGui::Checkbox("No Sky", &config->visuals.Sky);
                ImGui::Checkbox("No HUD", &config->visuals.HUD);
                ImGui::Checkbox("No Smoke", &config->visuals.Smoke);
                ImGui::Checkbox("No Paint", &config->visuals.Paint);
                ImGui::Checkbox("No ColorMask", &config->visuals.ColorMask);
                ImGui::Checkbox("No Shadows", &config->visuals.Shadows);


                break;
            case MISC:
                ImGui::Checkbox("Recoil", &config->misc.Recoil.first);
                ImGui::SliderFloat("Recoil Value", &config->misc.Recoil.second, 0.f, 100.f, "%1.f");
                ImGui::Separator();
                ImGui::Checkbox("Spread", &config->misc.Spread.first);
                ImGui::SliderFloat("Spread Value", &config->misc.Spread.second, 0.f, 100.f, "%1.f");
                ImGui::Separator();
                ImGui::Checkbox("No Pull out", &config->misc.NoPullOut);
                ImGui::Checkbox("No Animation", &config->misc.NoAnimation);
                ImGui::Checkbox("No Clip (X)", &config->misc.noClipSettings.first);
                ImGui::Separator();
                ImGui::Checkbox("Speed", &config->misc.Speed.first);
                ImGui::SliderFloat("Speed Value", &config->misc.Speed.second, 1.f, 2.3f, "%0.1f");
                ImGui::Separator();
                ImGui::Checkbox("Jumping (SPACE)", &config->misc.JumpingSettings.first);
                ImGui::Separator();


                


                break;
            case SETTINGS:
                ImGui::SliderFloat("DPI", &tempSize, 100.f, 200.f, "%.0f%%");
                if (ImGui::IsMouseReleased(ImGuiMouseButton_Left)) {
                    if (tempSize != Size) {
                        Size = tempSize;
                    }
                };
                ImGui::ColorEdit4("Menu Color", (float*)&AccentColor, ImGuiColorEditFlags_NoInputs);

                break;
            case SEARCH:

                break;
            default:
                break;
            }
        };
        ImGui::EndChild();
    }
    ImGui::End();
}
