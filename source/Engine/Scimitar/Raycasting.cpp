#include <iostream>
#include <xmmintrin.h>
#include <emmintrin.h>

#include "Raycasting.h"

#include "../../Core/Math/ubiVector3.h"
#include "../../Core/Utils/SafeCall/SafeCall.h"

#include "../Engine.h"

namespace scimitar
{
	struct Trace
	{
		DWORD tmp1;
		__m128 tmp2; // ubiQuaternion
		__m128 tmp3; // ubiQuaternion
	};

	using Prototype = uint64_t(*)(uint64_t, ubiVector3*, ubiVector3*, Trace*);

	bool isVisible(ubiVector3 src, ubiVector3 dst)
	{
		const Prototype function = reinterpret_cast<Prototype>(client + Update::RayCast);

		Trace trace;
		if (FUNCTION(
			function,
			0ui64,
			&src,
			&dst,
			&trace) == 2)
		{
			return true;
		}

		return false;
	};
}