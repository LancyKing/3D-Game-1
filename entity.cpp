#include "entity.hpp"



// Entities
bool Entity::HasFlags(int CFlags) {
	if ((CFlags & Flags) == CFlags) {
		return true;
	}
	return false;
}


bool Entity::IsCollidingWith(Entity* E) {
	if (E == nullptr) {
		return false;
	}
	if (!HasFlags(HasPos + HasHitbox) || !E->HasFlags(HasPos + HasHitbox)) {
		return false;
	}
	if (DoCubesOverlap(Pos, Size, E->Pos, E->Size)) {
		return true;
	}
	return false;
}

bool Entity::IsColliding() {
	for (int i = 0; i < Entities.size(); i++) {
		if (Entities[i] == this) {
			continue;
		}
		if (IsCollidingWith(Entities[i])) {
			return true;
	}	}
	return false;
}


std::vector<Entity*> Entity::GetOverlappingEntities() {
	std::vector<Entity*>Result;
	if (!HasFlags(HasPos + HasHitbox)) {
		return Result;
	}
	for (int i = 0; i < Entities.size(); i++) {
		if (Entities[i] == nullptr) {
			continue;
		}
		if (!Entities[i]->HasFlags(HasPos + HasHitbox)) {
			continue;
		}
		if (IsCollidingWith(Entities[i])) {
			Result.push_back(Entities[i]);
	}	}
	return Result;
}


void Entity::Draw() {
	DrawCubeWires(Pos, Size.x, Size.y, Size.z, ORANGE);
}

void Entity::Update() {}


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


void BouncePad::Draw() {
	DrawCubeWiresV(Pos, Size, GREEN);
}

void BouncePad::Update() {
	std::vector<Entity*>InRange{ GetOverlappingEntities() };
	for (int i = 0; i < InRange.size(); i++) {
		if (InRange[i]->HasFlags(HasVel)) {
			InRange[i]->Vel.y = abs(InRange[i]->Vel.y);
}	}	}

BouncePad::BouncePad(Vector3 Pos, Vector3 Size) : Entity{HasPos + HasHitbox} {
	this->Pos = Pos;
	this->Size = Size;
}



// Data
int GetActiveEntities() {
	int ActiveCount{ 0 };
	for (int i = 0; i < Entities.size(); i++) {
		if (Entities[i] == nullptr) {
			continue;
		}
		ActiveCount++;
	}
	return ActiveCount;
}



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

void HandleUpdates() {
	for (int i = 0; i < Entities.size(); i++) {
		if (Entities[i] == nullptr) {
			continue;
		}
		Entities[i]->Update();
}	}

void HandleDrawing() {
	for (int i = 0; i < Entities.size(); i++) {
		if (Entities[i] == nullptr) {
			continue;
		}
		Entities[i]->Draw();
}	}

void HandleOutOfBounds() {
	for (int i = 0; i < Entities.size(); i++) {
		if (Entities[i] == nullptr) {
			continue;
		}
		if (Entities[i]->HasFlags(HasPos)) {
			if (Entities[i]->Pos.y < -5.f) {
				delete Entities[i];
}	}	}	}

void DrawEntityDebug() {
	for (int i = 0; i < Entities.size(); i++) {
		if (Entities[i] == nullptr) {
			continue;
		}
		if (Entities[i]->HasFlags(HasPos)) {
			if (Entities[i]->HasFlags(HasVel)) {
				DrawLine3D(Entities[i]->Pos, Entities[i]->Pos + Normal(Entities[i]->Vel) * .2f, RED);
			}
			if (Entities[i]->HasFlags(HasHitbox)) {
				if (Entities[i]->IsColliding()) {
					DrawCubeWiresV(Entities[i]->Pos, Entities[i]->Size, RED);
				}
				else {
					DrawCubeWiresV(Entities[i]->Pos, Entities[i]->Size, ORANGE);
				}
}	}	}	}