
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
#include <meshgen.h>
// terrain
#include <player.h>
// physics (using math and vectors)

// END OF INCLUDES


// Externs
extern player_t player;


// Main
int main() {
	// Window
	vec2u16_t window_size = { 1280, 720 };
	_Bool fullscreen = false;
	InitWindow(window_size.x, window_size.y, "Terralite");
	SetTargetFPS(144);
	DisableCursor();

	// Audio
	InitAudioDevice();


	// Player / Camera
	init_player();

	


	_Bool running = true;
	while (running) {
		// Draw!
		BeginDrawing();
		ClearBackground(BLACK);

		// Move player and update camera
		update_position();
		update_camera();

		// 3D
		BeginMode3D(player.camera);

		DrawGrid(16, 1.0f);
		//DrawModel(model, (Vector3) { 0.0f, 0.0f, 0.0f }, 1.0f, DARKPURPLE);

		EndMode3D();

		// Text
		DrawText("Terralite", 8, 8, 30, MAROON);
	
		char framerate_text[32];
		snprintf(framerate_text, 31, "Framerate: %d", GetFPS());
		DrawText(framerate_text, 8, 42, 20, DARKGREEN);

		EndDrawing();

		// Window
		if (WindowShouldClose())
			running = false;

		if (GetKeyPressed(KEY_F11)) {
			fullscreen = !fullscreen;
		}
	}

	//UnloadModel(model);
	CloseWindow();
}