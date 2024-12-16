#include "Replication.h"

#include "../../Engine.h"
#include "../../../Core/Utils/SafeCall/SafeCall.h"

const char* Replication::GetName() noexcept
{
	return *reinterpret_cast<const char**>(this + Update::Name);
};