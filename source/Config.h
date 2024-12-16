#pragma once
#include <Windows.h>
#include <iostream>
#include <imgui.h>
#include "UI/Keybinds/Keybinds.h"

class Config
{
public:
    struct Aimbot {
        Keybinds key = Keybinds(ImGuiKey_MouseRight, HOLD);
        bool Enabled = false;
        bool VisibleOnly = false;
        float Fov = 150.f;
        int Speed = 20;
    } aimbot;

    struct Visuals {
        bool Enabled = false;
        std::pair<bool, ImColor> Box{ false,  ImColor(1.f, 1.f, 1.f) };
        std::pair<bool, std::pair<ImColor, ImColor>> Skeleton{ false,  { ImColor(0.f, 1.f, 0.f), ImColor(1.f, 0.f, 0.f)} };
        std::pair<bool, ImColor> Name{ false,  ImColor(1.f, 1.f, 1.f) };
        std::pair<bool, ImColor> OutOfViewArrow{ false,  ImColor(1.f, 0.f, 0.f) };

        bool Light, Model, Sky, HUD, Smoke, Paint, ColorMask, Shadows;
    } visuals;


    struct Misc
    {
        std::pair<bool, float> Recoil{ false, 0.f };
        std::pair<bool, float> Spread{ false, 0.f };
        std::pair<bool, float> Speed{ false, 2.f };
        bool NoPullOut = false;
        bool NoAnimation = false;
        std::pair<bool, Keybinds> noClipSettings = std::make_pair(false, Keybinds(ImGuiKey_X, HOLD));
        std::pair<bool, Keybinds> JumpingSettings = std::make_pair(false, Keybinds(ImGuiKey_Space, HOLD));
    } misc;


    struct Chat
    {
        bool All = true;
        const char* Message = "test";
        bool Animate = true;
        float delay = 250.f;
    };
};

inline std::unique_ptr<Config> config = std::make_unique<Config>();

inline Keybinds UIkey = Keybinds(ImGuiKey_Insert, TOGGLE);
