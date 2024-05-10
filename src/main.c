
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
	InitWindow(window_size.x, window_size.y, "Terralite");

	DisableCursor();
	SetTargetFPS(240);
	SetConfigFlags(FLAG_MSAA_4X_HINT);
	SetConfigFlags(FLAG_VSYNC_HINT);

	printf("%f", player->camera_sensitivity);

	// Player / Camera
	init_player();

	_Bool running = true;
	while (running) {
		// Get data
		Vector2 mouse_delta = GetMouseDelta();

		// Draw!
		BeginDrawing();

		ClearBackground(NIGHTBLUE);
		DrawText("Terralite", 8, 8, 30, MILDWHITE);

		// Move player and update camera
		// movement
		update_camera(mouse_delta);

		// 3D
		BeginMode3D(player->camera);

		DrawCapsuleWires((Vector3) { 0, 0, 0 }, (Vector3) { 0, 7, 0 }, 4, 12, 6, WHITE);

		EndMode3D();
		EndDrawing();

		// Window
		if (WindowShouldClose())
			running = false;
	}

	CloseWindow();
}