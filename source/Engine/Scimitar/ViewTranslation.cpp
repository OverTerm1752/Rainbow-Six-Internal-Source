#pragma once
#include "ViewTranslation.h"

#include "../Engine.h"

#include "../../Core/Math/ubiVector3.h"
#include "../../Core/Math/ubiVector2.h"
#include "../../Core/Math/ubiViewMatrix.h"

#include "../../external/imgui/imgui.h"

namespace scimitar
{
	bool WorldToScreen(const ubiVector3& World, ubiVector2& screen)
	{
		const ubiViewMatrix& vm = *reinterpret_cast<ubiViewMatrix*>(*reinterpret_cast<ptrdiff_t*>(client + Update::ViewMatrix) + 0x250);

		float w = vm[0][3] * World.x + vm[1][3] * World.y + vm[2][3] * World.z + vm[3][3];

		if (w < 0.001f)
			return false;

		float x = World.x * vm[0][0] + World.y * vm[1][0] + World.z * vm[2][0] + vm[3][0];
		float y = World.x * vm[0][1] + World.y * vm[1][1] + World.z * vm[2][1] + vm[3][1];

		float nx = x / w;
		float ny = y / w;

		const ImVec2 size = ImGui::GetIO().DisplaySize;

		screen.x = (size.x * 0.5f * nx) + (nx + size.x * 0.5f);
		screen.y = -(size.y * 0.5f * ny) + (ny + size.y * 0.5f);

		return true;
	};
}