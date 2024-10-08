#include <player.h>

#include <raylib.h>
#include <math.h>

// Terrain
#include <terrain.h>
extern terrain_t terrain;

// Player struct
player_t player;

int init_player() {

	// Camera
	player.camera_sensitivity = 300.0f;
	player.look_vector = (Vector2) { 0.0f, 0.0f };
	player.camera.fovy = 70.0f;
	player.camera.projection = CAMERA_PERSPECTIVE;
	player.camera.up = (Vector3) { 0.0f, 1.0f, 0.0f };

	// Body
	player.height = 1.83f;
	player.walk_speed = 20.0f;
	player.sprint_multiplier = 2.4f;
	player.position = (Vector3) { 0.0f, 0.0f, 0.0f };

	return 0;
}

int update_position() {

	// Get speed after diagonal, sprint, etc
	float speed = player.walk_speed;

	// Get keys
	_Bool w, a, s, d;
	w = IsKeyDown(KEY_W);
	a = IsKeyDown(KEY_A);
	s = IsKeyDown(KEY_S);
	d = IsKeyDown(KEY_D);

	// sqrt(2) speed if diagonal
	if ((w && a) || (w && d) || (s && a) || (s && d))
		speed *= 0.707f;

	if (IsKeyDown(KEY_LEFT_CONTROL))
		speed *= player.sprint_multiplier;

	// Apply movement
	double xm = cos(player.look_vector.x);
	double ym = sin(player.look_vector.x);
	double dt = GetFrameTime();

	if (w) {
		player.position.x += speed * dt * xm; 
		player.position.z += speed * dt * ym;
	}

	if (s) {
		player.position.x += speed * dt * -xm;
		player.position.z += speed * dt * -ym;
	}

	if (a) { 
		player.position.x += speed * dt * ym; 
		player.position.z += speed * dt * -xm; 
	}

	if (d) { 
		player.position.x += speed * dt * -ym; 
		player.position.z += speed * dt * xm; 
	}

	// Flight
	if (IsKeyDown(KEY_SPACE))
		player.position.y += 2.0f * dt;

	if (IsKeyDown(KEY_LEFT_SHIFT))
		player.position.y -= 2.0f * dt;


	// If we moved into a new chunk call the YAHOO function
	const vec2i16_t new_chunk_pos = (vec2i16_t){
		floor(player.position.x / (float)terrain.chunk_size.x),
		floor(player.position.z / (float)terrain.chunk_size.y)
	};

	if (!(player.chunk_pos.x == new_chunk_pos.x && player.chunk_pos.y == new_chunk_pos.y)) {
		// Update chunks and chunk_pos
		update_chunks();
		printf("upadting chunkes");
		player.chunk_pos = new_chunk_pos;
	}

	return 0;
}

int update_camera() {

	// Update position
	player.camera.position.x = player.position.x;
	player.camera.position.y = player.position.y + player.height;
	player.camera.position.z = player.position.z;

	// Update look vector
	Vector2 delta = GetMouseDelta();
	player.look_vector.x += delta.x / player.camera_sensitivity;
	player.look_vector.y -= delta.y / player.camera_sensitivity;

	// Loop back x look vector
	if (player.look_vector.x < -PI * 2 || player.look_vector.x > PI * 2)
		player.look_vector.x = 0.0f;

	// Limit up/down range to 89 degrees
	if (player.look_vector.y < -1.56f)
		player.look_vector.y = -1.56f;

	if (player.look_vector.y > 1.56f)
		player.look_vector.y = 1.56f;

	// Update target
	player.camera.target.x = player.camera.position.x + cos(player.look_vector.x);
	player.camera.target.y = player.camera.position.y + tan(player.look_vector.y);
	player.camera.target.z = player.camera.position.z + sin(player.look_vector.x);

	return 0;
}