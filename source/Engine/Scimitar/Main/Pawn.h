#pragma once
#include <iostream>
#include <xmmintrin.h>
#include <emmintrin.h>

struct Vftable;
class Actor;
class ubiVector3;

class Pawn
{
public:
	//Vftable* vtable;

	Actor* GetActor();
	ubiVector3 GetBonePos(int index);
	ubiVector3 TransformToVector(uintptr_t BoneArray, __m128 BoneInfo);
	ubiVector3 GetPosition(uint32_t Hash);
};