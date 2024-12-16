#pragma once

class ubiVector3;
class ubiVector2;

namespace scimitar
{
	bool WorldToScreen(const ubiVector3& world, ubiVector2& screen);
}