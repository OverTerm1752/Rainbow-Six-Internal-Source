#pragma once

struct Vftable;
class Pawn;
class Replication;

class Entity
{
public:
	//Vftable* vtable;

	Pawn* GetPawn();
	Replication* GetReplication();
	int GetTeamID();
};