#ifndef TERRAIN_H
#define TERRAIN_H

// Terrain will handle chunks and generation of mesh for terrain.
// Objects will be done in objects.h
// Noise will noise.h

#include <raylib.h>
#include <vec2.h>

enum chunk_status {
	CHUNK_UNLOADED,
	CHUNK_LOADING,
	CHUNK_LOADED,
	CHUNK_LOADED_OBJECTS
};

typedef struct terrain_t {
	// Memory
	uint8_t *chunk_status;
	vec2i16_t *chunk_locs;
	Model *chunk_models;
	float *chunk_gen_buffer;

	// Settings
	vec2u8_t chunk_size;
	uint8_t render_distance;
	uint16_t tot_chunks;

	// Textures
	Texture texture;

	// Info
	uint32_t chunks_loaded;
} terrain_t;

int init_terrain();
int free_terrain();

int32_t get_chunk_index(vec2i16_t chunk_pos);
int load_chunk(vec2i16_t chunk_pos);
int unload_chunk(vec2i16_t chunk_pos);

Model generate_chunk(vec2i16_t chunk_pos);
int update_chunks();

#endif