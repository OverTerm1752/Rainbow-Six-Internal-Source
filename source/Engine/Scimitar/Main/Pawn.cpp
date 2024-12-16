#include "Pawn.h"
#include "Actor.h"

#include "../../Engine.h"

#include "../../../Core/Utils/Defs.h"
#include "../../../Core/Utils/Utils.h"
#include "../../../Core/Math/ubiVector3.h"

Actor* Pawn::GetActor()
{
    uint64_t v8, v9, v10, v98, v99, v112, v94, v92, Actorr;


    v8 = ((unsigned __int64)Utils::NtCurrentPeb() >> 0xC) ^ 0x87BD6612;
    v9 = v8 + (retaddr >> 0x21);
    LODWORD(v99) = 0x5CFF9DE1;
    if (HIDWORD(v9))
        v10 = (v8 + (retaddr >> 0x21)) % 6;
    else
        v10 = (unsigned int)v9 % 6;
    LODWORD(v99) = 0xCC74FB17;
    if (v10)
    {
        v98 = v10;
        LODWORD(v99) = 0x7DEB27AA;
        if (v10 != 1)
        {
            v112 = v98;
            LODWORD(v99) = 0x57014B2B;
            if (v98 == 2 || (v92 = v112, LODWORD(v99) = 0xA6F45AB7, v112 == 3))
            {
                Actorr = ((*(_QWORD*)(this + 0x18) << 0x20) & 0xFF00000000i64)
                    + ((*(_QWORD*)(this + 0x18) << 0x10) & 0xFF000000000000i64)
                    + ((*(_QWORD*)(this + 0x18) >> 0x18) & 0xFF0000i64)
                    + ((*(_QWORD*)(this + 0x18) << 8) & 0xFF00000000000000ui64)
                    + (*(_QWORD*)(this + 0x18) & 0xFF00FF00i64)
                    + ((*(_QWORD*)(this + 0x18) >> 0x10) & 0xFF00000000FFi64)
                    - 0x20;
                goto LABEL_12;
            }
            v94 = v92;
            LODWORD(v99) = 0x8EE3262B;
            if (v92 != 4)
            {
                *(_QWORD*)&v99 = v94;
                Actorr = (((*(_QWORD*)(this + 0x18) - 0x15i64) << 0x20) & 0xFF00000000i64)
                    + (((*(_QWORD*)(this + 0x18) - 0x15i64) << 0x10) & 0xFF000000000000i64)
                    + (((unsigned __int64)(*(_QWORD*)(this + 0x18) - 0x15i64) >> 0x18) & 0xFF0000)
                    + (((*(_QWORD*)(this + 0x18) - 0x15i64) << 8) & 0xFF00000000000000ui64)
                    + ((*(_DWORD*)(this + 0x18) - 0x15) & 0xFF00FF00)
                    + (((unsigned __int64)(*(_QWORD*)(this + 0x18) - 0x15i64) >> 0x10) & 0xFF00000000FFi64)
                    - 0xB;
                goto LABEL_12;
            }
        }
        Actorr = ((unsigned __int64)(*(_QWORD*)(this + 0x18) - 0x20i64) >> 0x18) & 0xFF0000 | ((*(_QWORD*)(this + 0x18)
            - 0x20i64) << 8) & 0xFF00000000000000ui64 | ((*(_QWORD*)(this + 0x18) - 0x20i64) << 0x20) & 0xFF00000000i64 | (*(_DWORD*)(this + 0x18) - 0x20) & 0xFF00FF00 | ((*(_QWORD*)(this + 0x18) - 0x20i64) << 0x10) & 0xFF000000000000i64 | ((unsigned __int64)(*(_QWORD*)(this + 0x18) - 0x20i64) >> 0x10) & 0xFF00000000FFi64;
    }
    else
    {
        Actorr = (((*(_QWORD*)(this + 0x18) - 0xBi64) << 0x20) & 0xFF00000000i64)
            + (((*(_QWORD*)(this + 0x18) - 0xBi64) << 0x10) & 0xFF000000000000i64)
            + (((unsigned __int64)(*(_QWORD*)(this + 0x18) - 0xBi64) >> 0x18) & 0xFF0000)
            + (((*(_QWORD*)(this + 0x18) - 0xBi64) << 8) & 0xFF00000000000000ui64)
            + ((*(_DWORD*)(this + 0x18) - 0xB) & 0xFF00FF00)
            + (((unsigned __int64)(*(_QWORD*)(this + 0x18) - 0xBi64) >> 0x10) & 0xFF00000000FFi64)
            - 0x15;
    }
LABEL_12:

    if (!Actorr)
        return nullptr;


	if (!Utils::IsValidPointer(Actorr))
		return nullptr;

    return reinterpret_cast<Actor*>(Actorr);
}

ubiVector3 Pawn::TransformToVector(uintptr_t BoneArray, __m128 BoneInfo)
{
	auto base_val_1 = *reinterpret_cast<__m128*>(BoneArray + 0x20);
	auto base_val_2 = *reinterpret_cast<__m128*>(BoneArray + 0x30);

	constexpr __m128 const_val_1 = { 0.5,0.5,0.5,0.5 };
	constexpr __m128 const_val_2 = { 2.0,2.0,2.0,0.0 };

	__m128 Out = {};

	auto v7 = base_val_1;
	auto v8 = _mm_mul_ps(BoneInfo, v7);
	auto v9 = _mm_shuffle_ps(v8, v8, 85);
	v9.m128_f32[0] = (float)(v9.m128_f32[0] + *(float*)_mm_unpackhi_ps(v8, v8).m128_i64) + v8.m128_f32[0];
	auto v10 = _mm_sub_ps(_mm_mul_ps(_mm_shuffle_ps(v7, v7, 210), BoneInfo),
		_mm_mul_ps(_mm_shuffle_ps(BoneInfo, BoneInfo, 210), v7));
	auto v11 = _mm_add_ps(_mm_mul_ps(_mm_shuffle_ps(v9, v9, 0), v7),
		_mm_mul_ps(_mm_shuffle_ps(v7, v7, 255), _mm_shuffle_ps(v10, v10, 210)));
	auto v12 = _mm_mul_ps(v7, v7);
	Out = _mm_add_ps(_mm_shuffle_ps(base_val_2, _mm_shuffle_ps({ 0,0,0,0 }, base_val_2, 32), 36),
		_mm_mul_ps(_mm_add_ps(_mm_mul_ps(_mm_sub_ps(_mm_shuffle_ps(v12, v12, 255), const_val_1), BoneInfo), v11),
			const_val_2));

	return { Out.m128_f32[0], Out.m128_f32[1], Out.m128_f32[2] };
}

ubiVector3 Pawn::GetBonePos(int index)
{
	__m128* v82; // rdx
	__m128 v83; // xmm15
	unsigned __int64 v84; // rdx
	unsigned __int64 Skeleton1; // rbp
	__int64 Boneinfo{}; // xmm15
	__int64 v87; // rcx
	__int64 v88; // rdx
	__m128 v89; // xmm2
	__m128 v90; // xmm0
	__m128 v91; // xmm2
	__m128 v92; // xmm0
	__m128 v93; // xmm2
	__m128 v94; // xmm12
	unsigned __int64 v95; // rcx
	unsigned __int64 v96; // rbp
	unsigned __int64 v97; // rcx
	unsigned __int64 v98; // rdx
	unsigned __int64 v99; // rcx
	unsigned __int64 v100; // rbp
	unsigned __int64 v101; // rdx
	__int64 v102; // rdx
	_QWORD* Tmp; // r11
	__int64 v104; // rdx
	__int64 v105; // rax
	__int64 v106; // rdx
	unsigned __int64 Bonearray; // r11
	unsigned __int64 v108; // rax
	__int64 v109; // rdx
	__int64 v110; // rdx
	unsigned __int64 v111; // rax
	unsigned __int64 v112; // rdx
	__int16 v113; // r8
	__int16 v114{}; // dx
	__int64 v132; // rdx
	__int64 v133; // rax
	__int64 v134; // rdx
	unsigned __int64 v135; // r11
	unsigned __int64 v136; // rdx	
	__m128 v180; // xmm2
	__m128 v181; // xmm4
	bool v182; // dl
	__m128 v183; // xmm2
	__m128 v184; // xmm4
	__m128 v185; // xmm2
	__m128 v186; // xmm4
	__m128 v187; // xmm2
	__m128 v188; // xmm4
	__int64 v197; // rdx
	__int64 v198; // rax
	unsigned __int64 v199; // rdx
	__int64 v200; // rcx
	__int64 v201; // rbp
	unsigned __int64 v202; // r8
	__int64 v203; // rcx
	__int64 v204; // rbp
	unsigned __int64 v205; // r8
	unsigned __int64 v206; // rdx
	unsigned __int64 v207; // rax
	__int64 v208; // rdx
	unsigned int v209; // r8d
	unsigned __int64 v210; // rdx
	unsigned __int64 v211; // rax
	__int64 v212; // rdx
	unsigned __int64 v223; // [rsp+40h] [rbp-218h]
	unsigned __int64 v224; // [rsp+40h] [rbp-218h]
	__m128 v225; // [rsp+50h] [rbp-208h] BYREF
	__m128 v226; // [rsp+60h] [rbp-1F8h] BYREF
	__m128 v227; // [rsp+70h] [rbp-1E8h]
	__m128 v228; // [rsp+80h] [rbp-1D8h]
	__m128 v229; // [rsp+90h] [rbp-1C8h]
	__m128 v230; // [rsp+A0h] [rbp-1B8h]
	float v231; // [rsp+BCh] [rbp-19Ch]
	__m128 v232; // [rsp+C0h] [rbp-198h]
	unsigned __int64 v233; // [rsp+D0h] [rbp-188h]
	__m128i v234; // [rsp+DCh] [rbp-17Ch]
	__m128 v236; // [rsp+FCh] [rbp-15Ch]
	__m128 v237; // [rsp+10Ch] [rbp-14Ch]
	__m128 v238; // [rsp+11Ch] [rbp-13Ch]
	__m128 v239; // [rsp+12Ch] [rbp-12Ch]
	_DWORD* v240; // [rsp+140h] [rbp-118h]
	unsigned __int64 v241; // [rsp+148h] [rbp-110h]
	unsigned __int64 v242; // [rsp+150h] [rbp-108h] BYREF
	__int64 v243; // [rsp+158h] [rbp-100h]
	unsigned __int64 v244; // [rsp+160h] [rbp-F8h]



	v244 = ((0xF0EA0581i64 - __ROR8__(Utils::NtCurrentPeb(), 0xC)) ^ (retaddr >> 0x21)) % 5;
	LODWORD(v233) = 0xA32C56DF;
	if (!v244)
	{
		v84 = __ROL8__(
			(*(_QWORD*)(this + 0x320) >> 8) & 0xFF0000000000i64 | (*(_QWORD*)(this + 0x320) << 0x20) & 0xFF000000000000i64 | (*(_QWORD*)(this + 0x320) >> 0x10) & 0xFF0000i64 | HIDWORD(*(_QWORD*)(this + 0x320)) & 0xFF00 | (*(_QWORD*)(this + 0x320) << 0x30) & 0xFF00000000000000ui64 | (*(_QWORD*)(this + 0x320) >> 0x18) & 0xFF00000000i64 | *(_QWORD*)(this + 0x320) & 0xFF0000FFi64,
			0x21);
		Skeleton1 = (v84 << 0x30) & 0xFF000000000000i64 | v84 & 0xFF0000000000i64 | (v84 << 0x18) & 0xFF00000000i64 | HIDWORD(v84) & 0xFF000000 | (v84 << 8) & 0xFF00000000000000ui64 | (v84 >> 0x10) & 0xFFFFFF;
		goto LABEL_126;
	}
	v241 = v244;
	LODWORD(v233) = 0xFD7EC90B;
	if (v244 == 1)
	{
		v95 = ((*(_QWORD*)(this + 0x320) >> 0x18) & 0xFF00000000i64 | (*(_QWORD*)(this + 0x320) >> 0x10) & 0xFF0000i64 | *(_QWORD*)(this + 0x320) & 0xFF000000ui64) >> 0x10;
		v96 = (*(_QWORD*)(this + 0x320) << 0x30) & 0xFF000000000000i64 | ((unsigned int)*(_QWORD*)(this + 0x320) << 0x10) & 0xFF000000 | (*(_QWORD*)(this + 0x320) << 0x28) & 0xFF00000000000000ui64 | (*(_QWORD*)(this + 0x320) >> 8) & 0xFFFF00000000i64;
		goto LABEL_116;
	}
	LODWORD(v233) = 0x6DECF070;
	if (v241 == 2)
	{
		v98 = __ROL8__(*(_QWORD*)(this + 0x320), 0x21);
		v99 = (v98 >> 0x10 << 0x20) & 0xFF000000000000i64;
		v100 = (v98 >> 0x10 << 0x30) & 0xFF00000000000000ui64 | (v98 << 0x28) & 0xFF0000000000i64 | ((_DWORD)v98 << 8) & 0xFF0000 | (unsigned __int64)(WORD2(v98) & 0xFF00) | HIDWORD(v98) & 0xFF000000 | (v98 >> 0x10) & 0xFF000000FFi64;
		goto LABEL_125;
	}
	LODWORD(v233) = 0xDA0336AD;
	if (v241 == 3)
	{
		v101 = __ROL8__(*(_QWORD*)(this + 0x320), 0x21);
		v99 = ((v101 >> 0x18) & 0xFF00000000i64 | (v101 >> 0x10) & 0xFF0000 | (unsigned int)v101 & 0xFF000000) >> 0x10;
		v100 = (v101 << 0x30) & 0xFF000000000000i64 | ((_DWORD)v101 << 0x10) & 0xFF000000 | (v101 << 0x28) & 0xFF00000000000000ui64 | (v101 >> 8) & 0xFFFF00000000i64;
	LABEL_125:
		Skeleton1 = v99 | v100;
	}
	else
	{
		v233 = v241;
		v200 = *(_QWORD*)(this + 0x320) >> 0x10;
		v201 = v200 & 0xFF000000FFi64;
		v202 = (v200 << 0x30) & 0xFF00000000000000ui64;
		v95 = (v200 << 0x20) & 0xFF000000000000i64;
		v96 = v202 | (*(_QWORD*)(this + 0x320) << 0x28) & 0xFF0000000000i64 | ((unsigned int)*(_QWORD*)(this + 0x320) << 8) & 0xFF0000 | HIDWORD(*(_QWORD*)(this + 0x320)) & 0xFF00 | (unsigned int)HIDWORD(*(_QWORD*)(this + 0x320)) & 0xFF000000 | (unsigned __int64)v201;
	LABEL_116:
		Skeleton1 = __ROL8__(v95 | v96, 0x21);
	}
LABEL_126:

	Tmp = *(_QWORD**)Skeleton1;

	v241 = ((0x8FA5D3F7E4F48D21ui64 - __ROR8__(Utils::NtCurrentPeb(), 0xC)) ^ (retaddr >> 0x21)) % 4;
	LODWORD(v233) = 0x4BA60D7A;

	LODWORD(v233) = 0x7AEBD9AB;
	if (v241 == 1)
	{
		if ((Tmp[0x15] ^ 0x5F7C523F102F6BB3i64) == 0x2F267E370B24196Ei64)
			goto LABEL_137;
	LABEL_143:
		v108 = __ROR8__(Utils::NtCurrentPeb(), 0xC) + 0x679C86E00F5386BAi64 - (retaddr >> 0x21) - 0xE;
		LODWORD(v233) = 0x359AF14B;
		if (HIDWORD(v108))
			v109 = v108 % 2;
		else
			v109 = (unsigned int)v108 % 2;
		LODWORD(v233) = 0x76D0FA20;
		if (v109)
		{
			v233 = v109;
			Bonearray = __ROL8__(Tmp[0xE] + 0x679C86E00F5386BAi64, 0x2A);
		}
		else
		{
			Bonearray = __ROL8__(Tmp[0xE], 0x2A) + 0x679C86E00F5386BAi64;
		}
	}
	else
	{
		LODWORD(v233) = 0xC4194449;
		if (v241 != 2)
			v233 = v241;
		v104 = Tmp[0x15] - 0x2F267E370B24196Ei64;
		v105 = 0x5F7C523F102F6BB3i64;
	LABEL_142:
		if (v105 != v104)
			goto LABEL_143;
	LABEL_137:
		v223 = ((0x8116445EB1803E89ui64 - ((unsigned __int64)Utils::NtCurrentPeb() >> 0xC) + 0x4E7C9FA2) ^ (retaddr >> 0x21))
			% 2;
		LODWORD(v233) = 0xF262FEB2;
		if (v223)
		{
			v233 = v223;
			v110 = __ROL8__(Tmp[0xB], 0x39);
			Bonearray = ((v110 << 0x10) & 0xFF000000000000i64 | WORD2(v110) & 0xFF00 | (v110 << 8) & 0xFF00000000000000ui64 | BYTE3(v110) | (v110 << 0x18) & 0xFF00000000i64 | (v110 << 0x28) & 0xFF0000000000i64 | v110 & 0xFF0000 | HIDWORD(v110) & 0xFF000000)
				- 0x7EE9BBA14E7FC177i64;
		}
		else
		{
			v106 = __ROL8__(Tmp[0xB], 0x39) - 0x7EE9BBA14E7FC177i64;
			Bonearray = (v106 << 0x10) & 0xFF000000000000i64 | WORD2(v106) & 0xFF00 | (v106 << 8) & 0xFF00000000000000ui64 | BYTE3(v106) | (v106 << 0x18) & 0xFF00000000i64 | (v106 << 0x28) & 0xFF0000000000i64 | v106 & 0xFF0000 | HIDWORD(v106) & 0xFF000000;
		}
	}

	Boneinfo = *(_QWORD*)(Bonearray + 0x10);
	const __m128 BoneInfo = *reinterpret_cast<__m128*>(Boneinfo + 0x20LL * index - 0x7A);

	if (!Utils::IsValidPointer(Bonearray))
		return ubiVector3(0.f, 0.f, 0.f);

	return TransformToVector(Bonearray, BoneInfo);
};

ubiVector3 Pawn::GetPosition(uint32_t Hash)
{
	const auto Actor = this->GetActor();
	if (!Actor)
		return { 0.f, 0.f, 0.f };

	uint16_t ID = Actor->GetID(Hash);

	return this->GetBonePos(ID);
}