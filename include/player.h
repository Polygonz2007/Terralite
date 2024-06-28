#ifndef PLAYER_H
#define PLAYER_H

#include <stdio.h>
#include <raylib.h>
#include <vec2.h>

typedef struct player_t {
	// Camera
	Camera3D camera;
	Vector2 look_vector;
	float camera_sensitivity;

	// Body
	Vector3 position;
	float height;
	float walk_speed;
	float sprint_multiplier;

	// Chunks n' stuff
	vec2i16_t chunk_pos;
} player_t;

// Prototypes
int init_player();
int update_position();
int update_camera();

#endif