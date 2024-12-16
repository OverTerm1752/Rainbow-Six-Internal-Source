#pragma once
#include <iostream>

struct Vftable;
class Entity;

class World
{
public:
	//Vftable* vtable;

	uintptr_t GetGameManager();
	std::pair<Entity*, uint32_t> GetEntityList(uintptr_t GameManager);
	Entity* GetLocal();
};