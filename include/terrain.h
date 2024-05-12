#ifndef TERRAIN_H
#define TERRAIN_H

// Terrain will handle chunks and generation of mesh for terrain.
// Objects will be done in objects.h
// Noise will noise.h

#include <raylib.h>
#include <vec2.h>

enum chunk_status {
	CHUNK_UNLOADED,
	CHUNK_LOADED,
	CHUNK_LOADED_MODEL
};

typedef struct terrain_h {
	uint8_t *chunk_status;
	vec2i16_t *chunk_locs;
	Model *chunk_models;
} terrain_h;

int init_terrain();
Model generate_chunk(vec2i16_t chunk_pos);

#endif