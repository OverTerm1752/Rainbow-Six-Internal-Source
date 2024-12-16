#include "Visuals.h"

#include "../../Engine/Scimitar/ViewTranslation.h"
#include "../../Engine/Scimitar/Raycasting.h"

#include "../../Engine/Scimitar/Main/World.h"
#include "../../Engine/Scimitar/Main/Entity.h"
#include "../../Engine/Scimitar/Main/Pawn.h"
#include "../../Engine/Scimitar/Main/Replication.h"
#include "../../Engine/Scimitar/Main/Actor.h"

#include "../../Engine/Engine.h"

#include "../Math/ubiVector3.h"
#include "../Math/ubiVector2.h"
#include "../Math/ubiViewMatrix.h"
#include "../Utils/Utils.h"
#include "../Utils/Defs.h"
#include "../Utils/SafeCall/SafeCall.h"

#include "../../Config.h"
#include "../../external/imgui/imgui.h"

void Visuals::Renderables() noexcept
{
	if (!config->visuals.Enabled)
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

	for (int i = 0; i <= List.second; ++i)
	{
		const auto Player = *reinterpret_cast<Entity**>(List.first + (0x8 * i));
		if (!Player || Player == Local)
			continue;

		const auto Pawn = Player->GetPawn();
		if (!Pawn)
	 		continue;

		const auto Actor = Pawn->GetActor();
		if (!Actor)
			continue;

		if (config->visuals.Skeleton.first)
		{
			for (std::pair<ESkeleton, ESkeleton> Bones : BonesPair)
			{
				ubiVector2 Screen1, Screen2;
				if (scimitar::WorldToScreen(Pawn->GetPosition(Bones.first), Screen1) && scimitar::WorldToScreen(Pawn->GetPosition(Bones.second), Screen2))
				{
					ImGui::GetBackgroundDrawList()->AddLine({ Screen1.x, Screen1.y }, { Screen2.x, Screen2.y }, ImColor(0.f, 1.f, 0.f), 2.f);
				};
			};
		};
	};
}

void Visuals::Effects() noexcept
{
	const uintptr_t qword_AAB1400 = *reinterpret_cast<uintptr_t*>(client + Update::EffectClass);
	if (!qword_AAB1400)
		return;

	const uintptr_t Effect = *reinterpret_cast<uintptr_t*>(qword_AAB1400 + 0x8);
	if (!Effect)
		return;

	*reinterpret_cast<bool*>(Effect + 0x5C) = !config->visuals.Light;
	*reinterpret_cast<bool*>(Effect + 0x107) = config->visuals.Model;
	*reinterpret_cast<bool*>(Effect + 0x108) = config->visuals.Sky;
	*reinterpret_cast<bool*>(Effect + 0x109) = config->visuals.HUD;
	*reinterpret_cast<bool*>(Effect + 0x104) = config->visuals.Smoke;
	*reinterpret_cast<bool*>(Effect + 0x10C) = config->visuals.Paint;
	*reinterpret_cast<bool*>(Effect + 0x119) = config->visuals.ColorMask;
	*reinterpret_cast<bool*>(Effect + 0x103) = config->visuals.Shadows;
};
