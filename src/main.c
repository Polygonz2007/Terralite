
// INCLUDES

// Default
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <stdint.h>

// Raylib
#include <raylib.h>

// Vectors and math
#include <vec2.h>
#include <vec3.h>

// Gameplay
// terrain
#include <player.h>
// physics (using math and vectors)

// END OF INCLUDES


// Colors
#define NIGHTBLUE (Color){ 10, 20, 70, 255 }
#define MILDWHITE (Color){ 255, 255, 255, 200 }

// Keep the code clean, make sure to move all prototypes / global variables / structs etc. in includes.


// Main
int main() {
	// Window
	vec2u16_t window_size = { 1280, 720 };
	InitWindow(window_size.x, window_size.y, "Teralite");

	// Player / Camera
	init_player();

	_Bool running = true;
	while (running) {
		BeginDrawing();

		ClearBackground(NIGHTBLUE);
		DrawText("Terralite", 8, 8, 30, MILDWHITE);

		// 3D
		player.camera.position = (Vector3){ cos(GetTime()) * 20.0f, 10.0f, sin(GetTime()) * 20.0f};
		BeginMode3D(player.camera);

		DrawCube((Vector3) { 0, 0, 0 }, 10, 10, 10, WHITE);

		EndMode3D();
		EndDrawing();

		// Window
		if (WindowShouldClose())
			running = false;
	}

	CloseWindow();
}