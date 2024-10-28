#include "global.hpp"
#include "drawfunctions.hpp"



//



int main() {
	InitWindow(WindowWidth, WindowHeight, "Test 30: CPU"); SetTargetFPS(60);

	// Camera setup
	Camera Cam{ 0 };
	Cam.fovy = 90.f;
	Cam.position = Vector3{ 0.f,1.f,-1.f };
	Cam.projection = CAMERA_PERSPECTIVE;
	Cam.target = Vector3{ 0.f,0.f,0.f };
	Cam.up = Vector3{ 0.f,1.f,0.f };


	while (!WindowShouldClose()) {
		// Update
		Cam.position.x = cos(GetTime() / 3.f) * 4.f;
		Cam.position.z = sin(GetTime() / 3.f) * 4.f;

		// Draw
		BeginDrawing(); ClearBackground(BLACK);
		BeginMode3D(Cam);


		DrawGrid3D({ 0,-1,0 }, 10, 10);


		EndMode3D();
		EndDrawing();
	}
}