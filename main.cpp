#include "global.hpp"
#include "drawfunctions.hpp"
#include "entity.hpp"



// Random functions
void SpawnParticle(Vector3 Pos) {
	Vector3 Vel{};
	Vel.x = GetRandomValue(-2, 2);
	Vel.y = GetRandomValue(2, 5);
	Vel.z = GetRandomValue(-2, 2);
	Entity* E{ new Entity{HasPos + HasVel + HasHitbox + HasGrav} };
	E->Vel = Vel;
	E->Size = Vector3{ .2f,.2f,.2f };
}



int main() {
	InitWindow(WindowWidth, WindowHeight, "Test 30: CPU"); SetTargetFPS(TargetFPS);

	// Camera setup
	Camera Cam{ 0 };
	Cam.fovy = 90.f;
	Cam.position = Vector3{ 0.f,3.f,0.f };
	Cam.projection = CAMERA_PERSPECTIVE;
	Cam.target = Vector3{ 0.f,0.f,0.f };
	Cam.up = Vector3{ 0.f,1.f,0.f };

	// World setup
	Entity E{ HasPos + HasHitbox };
	BouncePad BP{ {0.f,-1.f,0.f},{10.f,1.f,10.f} };


	while (!WindowShouldClose()) {
		// Update
		Cam.position.x = cos(GetTime() / -4.f) * 7.f;
		Cam.position.z = sin(GetTime() / -4.f) * 7.f;

		HandleOutOfBounds();
		HandlePhysics();
		HandleUpdates();
		if (FramesPassed % 12 == 0) {
			SpawnParticle(Vector3{});
		}

		// Draw
		BeginDrawing(); ClearBackground(BLACK);
		BeginMode3D(Cam);


		DrawGrid3D({ 0,-.5f,0 }, 10, 10);
		HandleDrawing();


		EndMode3D();
		
		// UI
		DrawText(TextFormat("FPS: %i / %i", int(ceil(1.f / GetFrameTime())), TargetFPS), 5, 5, 18, WHITE);
		DrawText(TextFormat("Entities: %i / %i", GetActiveEntities(), Entities.size()), 5, 23, 18, WHITE);


		EndDrawing();
		FramesPassed++;
	}
}