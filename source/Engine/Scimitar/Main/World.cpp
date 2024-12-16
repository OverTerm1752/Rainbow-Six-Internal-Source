#include "World.h"

#include "Entity.h"

#include "../../Engine.h"
#include "../../../Core/Utils/SafeCall/SafeCall.h"
#include "../../../Core/Utils/Defs.h"

uintptr_t World::GetGameManager()
{
    unsigned __int64 v4; // rax
    unsigned __int64 v5; // rdx
    unsigned int v6; // r12d
    __int64 result; // rax
    __int64 v8; // r8
    unsigned __int64 v9; // r8
    unsigned int v10; // ebx
    __int64 v11; // r10
    __int64 v12; // rbp
    __int64 v13; // rbp
    __int64 v14; // r8
    char v15; // r11
    unsigned __int8 v16; // r11
    volatile signed __int32* v17; // r14
    unsigned __int64 v18; // r15
    unsigned __int64 v19; // rdx
    unsigned __int64 v20; // rdi
    unsigned __int64 v21; // rdi
    unsigned int v22; // ebp
    __int64 v23; // rcx
    unsigned __int64 v24[9]; // [rsp+40h] [rbp-48h] BYREF


    uint64_t qword_BA8BB50 = *(uint64_t*)(client + 0xBA8BB50);
    if (!qword_BA8BB50)
        return 0;


    v18 = (__ROR8__(Utils::NtCurrentPeb(), 0x64 - (unsigned __int8)0xD3758) ^ 0xDEA99BA33834E09Cui64)
        + (retaddr >> 0x21);
    LODWORD(v24[0]) = 0x84035C71;
    if (HIDWORD(v18))
        v19 = v18 % 4;
    else
        v19 = (unsigned int)v18 % 4;
    LODWORD(v24[0]) = 0xC172640D;
    if (v19)
    {
        LODWORD(v24[0]) = 0x262A4A69;
        if (v19 == 1)
        {
            v20 = __ROL8__((qword_BA8BB50 + 0x5BC676C774C8D2A4i64) ^ 0x856FED644CFC322Eui64, 0x2A);
        }
        else
        {
            LODWORD(v24[0]) = 0x1E9ED3D4;
            if (v19 == 2)
            {
                v20 = (__ROL8__(qword_BA8BB50, 0x2A) ^ 0x856FED644CFC322Eui64) + 0x5BC676C774C8D2A4i64;
            }
            else
            {
                v24[0] = v19;
                v20 = (__ROL8__(qword_BA8BB50, 0x2A) + 0x5BC676C774C8D2A4i64) ^ 0x856FED644CFC322Eui64;
            }
        }
    }
    else
    {
        v20 = __ROL8__(qword_BA8BB50 + 0x5BC676C774C8D2A4i64, 0x2A) ^ 0x856FED644CFC322Eui64;
    }
    if (!v20)
        return 0;
    auto GameManager = v20;

    return GameManager;
};

std::pair<Entity*, uint32_t> World::GetEntityList(uintptr_t GameManager)
{
    unsigned __int64(*sub_1605A0)(uint64_t* a1) = reinterpret_cast<decltype(sub_1605A0)>(client + 0x89BD780);
    unsigned __int64(*sub_160D00)(uint64_t* a1) = reinterpret_cast<decltype(sub_160D00)>(client + 0x89BDB50);

    __int64 List = FUNCTION(sub_1605A0, (uint64_t*)(GameManager + 0x728));
    __int64 Count = FUNCTION(sub_160D00, (uint64_t*)(GameManager + 0x728));

    if (!List || !Count)
        return { nullptr, 0 };

    return { reinterpret_cast<Entity*>(List), static_cast<uint32_t>((Count - List) / 0x8) };
}

Entity* World::GetLocal()
{
    uintptr_t GameManager = GetGameManager();
    if (!GameManager)
        return nullptr;

    return *reinterpret_cast<Entity**>(GetEntityList(GameManager).first);
}
