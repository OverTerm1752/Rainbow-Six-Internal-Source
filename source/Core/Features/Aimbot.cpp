#include <windows.h>
#include <iostream>
#include <algorithm>
#include <cmath> 

#include "Aimbot.h"

#include "../../Engine/Scimitar/Main/World.h"
#include "../../Engine/Scimitar/Main/Entity.h"
#include "../../Engine/Scimitar/Main/Pawn.h"
#include "../../Engine/Scimitar/Main/Replication.h"
#include "../../Engine/Scimitar/Main/Actor.h"

#include "../Math/ubiVector3.h"
#include "../Math/ubiVector2.h"

#include "../../external/imgui/imgui.h"
#include "../../Engine/Scimitar/ViewTranslation.h"

#include "../../Config.h"

int Clamp(int value, int minVal, int maxVal)
{
    return max(minVal, min(value, maxVal));
}

float CalculateDistance(const ubiVector2& point1, const ubiVector2& point2)
{
    float dx = point1.x - point2.x;
    float dy = point1.y - point2.y;
    return sqrt(dx * dx + dy * dy);
}

void Aimbot::Run() noexcept
{
    if (!config->aimbot.Enabled)
        return;

    static const auto world = std::make_unique<World>();

    const auto GameManager = world->GetGameManager();
    if (!GameManager || GameManager == 0)
        return;

    const auto List = world->GetEntityList(GameManager);
    if (!List.first || List.second <= 1)
        return;

    const auto Local = world->GetLocal();
    if (!Local)
        return;

    int screenWidth = GetSystemMetrics(SM_CXSCREEN); // can use imgui size for future update
    int screenHeight = GetSystemMetrics(SM_CYSCREEN); 
    int centerX = screenWidth / 2;
    int centerY = screenHeight / 2;

    float fovRadius = config->aimbot.Fov;

    ImGui::GetBackgroundDrawList()->AddCircle(
        { (float)centerX, (float)centerY }, 
        fovRadius,
        ImColor(1.0f, 0.0f, 0.0f, 1.f),
        100,
        2.0f
    );

    Entity* closestPlayer = nullptr;
    float closestDistance = FLT_MAX;

    for (int i = 0; i <= List.second; ++i)
    {
        const auto Player = *reinterpret_cast<Entity**>(List.first + (0x8 * i));
        if (!Player || Player == Local)
            continue;

        const auto LocalReplication = Local->GetReplication();
        if (!LocalReplication)
            continue;

        const auto EntReplication = Player->GetReplication();
        if (!EntReplication)
            continue;

        if (Local->GetTeamID() == Player->GetTeamID())
            continue;

        const auto Pawn = Player->GetPawn();
        if (!Pawn)
            continue;

        const auto Actor = Pawn->GetActor();
        if (!Actor)
            continue;

        const auto LocalPawn = Local->GetPawn();
        if (!LocalPawn)
            continue;

        ubiVector3 EntHead = Pawn->GetPosition(ESkeleton::NECK);
        ubiVector2 Screen;

        if (scimitar::WorldToScreen(EntHead, Screen))
        {
            float distance = CalculateDistance({ static_cast<float>(centerX), static_cast<float>(centerY) }, Screen);

            if (distance <= fovRadius)
            {
                if (distance < closestDistance)
                {
                    closestDistance = distance;
                    closestPlayer = Player;
                }
            }
        }
    }

    if (config->aimbot.key.IsActive())
    {
        if (closestPlayer)
        {
            const auto Pawn = closestPlayer->GetPawn();
            if (Pawn)
            {
                const auto EntHead = Pawn->GetPosition(ESkeleton::NECK);
                ubiVector2 Screen;
                if (scimitar::WorldToScreen(EntHead, Screen))
                {
                    int deltaX = static_cast<int>(Screen.x - centerX);
                    int deltaY = static_cast<int>(Screen.y - centerY);

                    int maxMove = config->aimbot.Speed;
                    deltaX = Clamp(deltaX, -maxMove, maxMove);
                    deltaY = Clamp(deltaY, -maxMove, maxMove);

                    mouse_event(MOUSEEVENTF_MOVE, deltaX, deltaY, 0, 0); // just system call this shit
                }
            }
        };
    }
}



//void Aimbot::Silent() noexcept {};