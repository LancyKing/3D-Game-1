#pragma once
#include "global.hpp"



// Entities
extern enum Flag {
	HasPos = 1,
	HasVel = 2,
	HasHitbox = 4,
	HasGrav = 8
};

struct Entity {
	int Flags{};
	Vector3 Pos{};
	Vector3 Vel{};
	Vector3 Size{ 1.f,1.f,1.f };

	bool HasFlags(int Flags);

	virtual void Draw();
	virtual void Update();

	Entity(int Flags);
	Entity();
	~Entity();
};

extern std::vector<Entity*>Entities;



// Handlers
void HandlePhysics();
void HandleOutOfBounds(); // Despawns entities below the floor