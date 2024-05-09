#ifndef PLAYER_H
#define PLAYER_H

#include <stdio.h>
#include <raylib.h>

struct player {
	// Camera
	Camera3D camera;
	Vector2 look_vector;
	float camera_sensitivity;

	// Body
	Vector3 position;
	float height;
	float walk_speed;
} player;

// Prototypes
int init_player();

#endif