#include "Entity.h"

#include "../../Engine.h"
#include "../../../Core/Utils/SafeCall/SafeCall.h"
#include "../../../Core/Utils/Utils.h"
#include "../../../Core/Utils/Defs.h"

Pawn* Entity::GetPawn()
{
	uint64_t pawn = *reinterpret_cast<uint64_t*>(this + 0x80) - 0x44i64;
	if (!pawn)
		return nullptr;

    if (!Utils::IsValidPointer(pawn))
        return nullptr;

	return reinterpret_cast<Pawn*>(pawn);
}

Replication* Entity::GetReplication()
{
    auto a2 = this;
    uint64_t v43, v30, v31, v32, v33;
    uint64_t Replicationn, v41, v35, v36, v37, v42, v38;



    v43 = ((0x995B3412FDDC1645ui64 - __ROR8__(Utils::NtCurrentPeb(), 0xC)) ^ (retaddr >> 0x21)) % 5;
    LODWORD(v41) = 0xC160E7F5;
    if (!v43)
    {
        v30 = (*(_QWORD*)(a2 + 0x58) + 0x4E9D957871B7F916i64) ^ 0xD7C6A16A686D99E6ui64;
        v31 = (v30 << 0x18) & 0xFF00000000000000ui64 | (v30 >> 8) & 0xFF00000000i64;
        v32 = (v30 >> 0x28) & 0xFF00;
        v33 = HIBYTE(v30) | (unsigned int)v30 & 0xFFFF0000 | (v30 << 0x28) & 0xFFFF0000000000i64;
    LABEL_61:
        Replicationn = v32 | v31 | v33;
        goto LABEL_70;
    }
    LODWORD(v41) = 0xFA3573C3;
    if (v43 == 1)
    {
        v35 = *(_QWORD*)(a2 + 0x58) + 0x4E9D957871B7F916i64;
        v36 = (v35 >> 0x28) & 0xFF00 | (v35 << 0x18) & 0xFF00000000000000ui64 | (v35 >> 8) & 0xFF00000000i64 | HIBYTE(v35) | (unsigned int)v35 & 0xFFFF0000 | (v35 << 0x28) & 0xFFFF0000000000i64;
    }
    else
    {
        LODWORD(v41) = 0x58B5BDDA;
        if (v43 == 2)
        {
            v37 = *(_QWORD*)(a2 + 0x58) ^ 0xD7C6A16A686D99E6ui64;
            Replicationn = ((v37 << 0x18) & 0xFF00000000000000ui64)
                + ((v37 << 0x28) & 0xFFFF0000000000i64)
                + ((v37 >> 8) & 0xFF00000000i64)
                + ((v37 >> 0x28) & 0xFF00)
                + ((unsigned int)v37 & 0xFFFF0000)
                + HIBYTE(v37)
                + 0x4E9D957871B7F916i64;
            goto LABEL_70;
        }
        v42 = v43;
        LODWORD(v41) = 0x6B1D650D;
        if (v43 == 3)
        {
            v38 = (*(_QWORD*)(a2 + 0x58) ^ 0xD7C6A16A686D99E6ui64) + 0x4E9D957871B7F916i64;
            v31 = (v38 << 0x18) & 0xFF00000000000000ui64 | (v38 >> 8) & 0xFF00000000i64;
            v32 = (v38 >> 0x28) & 0xFF00;
            v33 = HIBYTE(v38) | (unsigned int)v38 & 0xFFFF0000 | (v38 << 0x28) & 0xFFFF0000000000i64;
            goto LABEL_61;
        }
        v41 = v42;
        v36 = ((*(_QWORD*)(a2 + 0x58) << 0x18) & 0xFF00000000000000ui64)
            + ((*(_QWORD*)(a2 + 0x58) << 0x28) & 0xFFFF0000000000i64)
            + ((*(_QWORD*)(a2 + 0x58) >> 8) & 0xFF00000000i64)
            + ((*(_QWORD*)(a2 + 0x58) >> 0x28) & 0xFF00i64)
            + (*(_QWORD*)(a2 + 0x58) & 0xFFFF0000i64)
            + HIBYTE(*(_QWORD*)(a2 + 0x58))
            + 0x4E9D957871B7F916i64;
    }
    Replicationn = v36 ^ 0xD7C6A16A686D99E6ui64;
LABEL_70:
    if (!Replicationn)
        return nullptr;

	return reinterpret_cast<Replication*>(Replicationn);
}

int Entity::GetTeamID()
{
    using Protype = uint64_t(*)(Entity*);
    const Protype function = reinterpret_cast<Protype>(client + Update::TeamID);

    int id = FUNCTION(function, this);
    if (!id)
        return 0;

    return id;
};