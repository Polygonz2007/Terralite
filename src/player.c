#include <player.h>

int init_player() {
	printf("Init player.\n");
	player = (player_t*){ 0 };

	// Camera
	player->camera_sensitivity = 300.0f;
	player->look_vector = (Vector2) { 0.0f, 0.0f };
	player->camera.fovy = 70.0f;
	player->camera.projection = CAMERA_PERSPECTIVE;
	player->camera.up = (Vector3) { 0.0f, 1.0f, 0.0f };

	// Body
	player->height = 1.83f;
	player->walk_speed = 3.8f;
	player->position = (Vector3) { 0.0f, 0.0f, 0.0f };

	return &player;
}

int update_camera(Vector2 mouse_delta) {
	printf("Update camera.\n");

	// CAMERA
	//player->camera.position = (Vector3){ player->position.x, player->position.y + player->height, player->position.z };

	//player->look_vector.x += mouse_delta.x / player->camera_sensitivity;
	//player->look_vector.y += mouse_delta.y / player->camera_sensitivity;

	//player->look_vector.x = fmodf(player->look_vector.x, PI * 2);
	////player.look_vector.y = clamp(player.look_vector.y, -1.57f, 1.57f);

	//Vector3 cam_pos = player->camera.position;
	//player->camera.target = (Vector3){ 
	//	cam_pos.x + cos(player->look_vector.x),
	//	cam_pos.y - tan(player->look_vector.y),
	//	cam_pos.z + sin(player->look_vector.x)
	//};

	return 0;
}