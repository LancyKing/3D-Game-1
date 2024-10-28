#include "drawfunctions.hpp"



void DrawGrid3D(Vector3 Origin, int Width, int Length) {
	for (int x = 0; x <= Width; x++) {
		Vector3 Start{ Origin + Vector3{x - float(Width) / 2.f,0.f,float(Length) / 2.f} };
		Vector3 End{ Origin + Vector3{x - float(Width) / 2.f,0.f,float(Length / -2.f) } };
		DrawLine3D(Start, End, SKYBLUE);
	}
	for (int z = 0; z <= Length; z++) {
		Vector3 Start{ Origin + Vector3{float(Width) / 2.f, 0.f, z - float(Length) / 2.f} };
		Vector3 End{ Origin + Vector3{float(Width) / -2.f, 0.f, z - float(Length) / 2.f} };
		DrawLine3D(Start, End, SKYBLUE);
	}
}