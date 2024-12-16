#include "Actor.h"

#include "../../Engine.h"
#include "../../../Core/Utils/SafeCall/SafeCall.h"
#include "../../../Core/Math/ubiVector3.h"

uintptr_t Actor::GetComponent(int id) noexcept
{
    constexpr int kValid{ 0xFF };
    const auto kEntry = *reinterpret_cast<uint8_t*>(this + id);
    if (kEntry != kValid)
    {
        const uintptr_t kComponentList = *reinterpret_cast<uintptr_t*>(*reinterpret_cast<uintptr_t*>(this + 0xD8) + 8 * kEntry);
        if (kComponentList)
            return kComponentList;
    }
    return 0;
}

uintptr_t Actor::GetMovement(uint64_t Hash) noexcept
{
    using Prototype = uintptr_t(*)(uintptr_t, uint64_t, uintptr_t*);
    const Prototype function = reinterpret_cast<Prototype>(client + Update::MovementFunction);

    uintptr_t zero = 0;
    uintptr_t Component = this->GetComponent(Update::MovementComponent);
    if (Component)
    {
        uintptr_t v6 = *reinterpret_cast<uintptr_t*>(Component + 0x48);
        if (v6)
        {
            if (*reinterpret_cast<BYTE*>(v6 + 0xDC))
            {
                uintptr_t* v7 = (uintptr_t*)FUNCTION(function, *(uintptr_t*)(v6 + 0x148), Hash, &zero);
                if (v7 && *v7)
                {
                    return *v7;
                }
            }
        }
    }
    return 0;
};

uint16_t Actor::GetID(uint32_t hash)
{
	uint64_t v33;

	auto v24 = *(uint8_t*)(this + Update::SkeletonComponent); //232
	if (v24 != 0xFF)
	{
		auto v25 = *(uint64_t*)(*(uint64_t*)(this + 0xD8) + 8 * v24);
		if (v25)
		{
			auto v27 = *(uint64_t*)(v25 + 0x248);
			if (v27)
			{
				auto v28 = *(uint64_t*)(v27 + 0x50);
				auto v29 = (unsigned int)(8 * *(uint32_t*)(v27 + 0x58));
				auto v30 = v28;
				if ((uint32_t)v29)
				{
					auto v31 = (unsigned int)v29 >> 3;
					v30 = v28;
					do
					{
						auto v32 = v31 >> 1;
						v33 = v31 + ~(v31 >> 1);
						auto v34 = *(uint32_t*)(v30 + 8 * (v31 >> 1)) < hash;
						auto v35 = v30 + 8 * (v31 >> 1) + 8;
						if (v34)
							v30 = v35;
						if (!v34)
							v33 = v32;
						v31 = v33;
					} while (v33 > 0);
				}
				if (v30 != v29 + v28 && *(uint32_t*)(v30) == hash)
				{
					uint16_t BoneID = *(uint16_t*)(v30 + 4);
					if (BoneID != 0xFFFF)
					{
						return BoneID;
					}
				}
			}
		}
	}
}