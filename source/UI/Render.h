#pragma once
#include <cmath>
#include <vector>
#include <imgui.h>

struct ImFont;

#define SCALE(value) (value * Render::Size / 100.f)

enum Chanel : int
{
    AIMBOT = 0,
    VISUALS,
    MISC,
    SETTINGS,
    SEARCH
};

namespace Render
{
    void Fonts() noexcept;
    void Style() noexcept;
    void Menu() noexcept;

    inline ImFont* MenuFont = nullptr;

    inline float Size = 100.f;
    inline float tempSize = Size;

    inline int SelectedChanel = AIMBOT;

    inline std::vector<std::pair<Chanel, const char*>> channelButtons = {
    { AIMBOT, "Aimbot" },
    { VISUALS, "Visuals" },
    { MISC, "Misc" },
    { SETTINGS, "Settings" }
    };

    inline ImColor AccentColor = ImColor(0.878f, 0.067f, 0.373f, 1.0f); // .f
    inline static char searchBuffer[20] = "";
};
