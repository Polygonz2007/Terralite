#ifndef PLAYER_H
#define PLAYER_H

#include <stdio.h>
#include <raylib.h>

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
} player_t;

// Prototypes
int init_player();
int update_position();
int update_camera();

#endif