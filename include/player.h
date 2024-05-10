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
} player_t;

// Player struct
player_t *player;

// Prototypes
int init_player();
int update_camera(Vector2 mouse_delta);

#endif