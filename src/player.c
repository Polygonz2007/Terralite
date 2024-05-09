#include <player.h>

struct player player = { 0 };

int init_player() {
	// Camera
	player.camera_sensitivity = 200.0f;
	player.look_vector = (Vector2) { 0.0f, 0.0f };
	player.camera.fovy = 70.0f;
	player.camera.projection = CAMERA_PERSPECTIVE;
	player.camera.up = (Vector3){ 0.0f, 1.0f, 0.0f };

	// Body
	player.height = 1.83f;
	player.walk_speed = 3.8f;
	player.position = (Vector3){ 0.0f, 0.0f, 0.0f };

	return &player;
}