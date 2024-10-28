#include "entity.hpp"



// Entities
bool Entity::HasFlags(int CFlags) {
	if ((CFlags & Flags) == CFlags) {
		return true;
	}
	return false;
}

void Entity::Draw() {
	DrawCubeWires(Pos, Size.x, Size.y, Size.z, ORANGE);
}

void Entity::Update() {
	Pos = Pos + Vel;
}

Entity::Entity(int Flags) : Flags(Flags) {
	for (int i = 0; i < Entities.size(); i++) {
		if (Entities[i] == nullptr) {
			Entities[i] = this;
			return;
	}	}
	Entities.push_back(this);
}
Entity::Entity() : Entity{ 0 } {}
Entity::~Entity() {
	for (int i = 0; i < Entities.size(); i++) {
		if (Entities[i] == this) {
			Entities[i] = nullptr;
			return;
}	}	}

std::vector<Entity*>Entities;



// Handlers
void HandlePhysics() {
	for (int i = 0; i < Entities.size(); i++) {
		if (Entities[i] == nullptr) {
			continue;
		}
		if (Entities[i]->HasFlags(HasPos + HasVel)) {
			if (Entities[i]->HasFlags(HasGrav)) {
				Entities[i]->Vel.y -= GetFrameTime() * 3.f;
			}
			Entities[i]->Pos = Entities[i]->Pos + Entities[i]->Vel * GetFrameTime();
}	}	}

void HandleOutOfBounds() {
	for (int i = 0; i < Entities.size(); i++) {
		if (Entities[i] == nullptr) {
			continue;
		}
		if (Entities[i]->HasFlags(HasPos)) {
			if (Entities[i]->Pos.y < -5.f) {
				delete Entities[i];
}	}	}	}