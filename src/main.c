
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
#include <terrain.h>
#include <player.h>
// physics (using math and vectors)

// END OF INCLUDES

// Defenitions
#define WATER (Color) { 0, 121, 241, 196 }



// Externs
extern player_t player;
extern terrain_t terrain;


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

	// Initiation
	init_player();
	init_terrain();


	_Bool running = true;
	while (running) {
		// Draw!
		BeginDrawing();
		ClearBackground(SKYBLUE);

		// Move player and update camera
		update_position();
		update_camera();

		// 3D
		BeginMode3D(player.camera);

		DrawPlane((Vector3) { player.position.x, 0.0f, player.position.z }, (Vector2) { 256.0f, 256.0f }, WATER);
		
		for (size_t i = 0; i < terrain.tot_chunks; ++i) {
			if (terrain.chunk_status[i] == CHUNK_LOADED) {
				vec2i16_t chunk_pos = terrain.chunk_locs[i];
				Vector3 pos = { chunk_pos.x * 16.0f, 0.0f, chunk_pos.y * 16.0f };

				DrawModel(terrain.chunk_models[i], pos, 1.0f, WHITE);
			}
		}

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
	
	// Free
	free_terrain();

	CloseWindow();
}