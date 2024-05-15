
#include <malloc.h>
#include <terrain.h>
#include <meshgen.h>
#include <noise.h>

// Noise
extern noise_t noise;

// Terain
terrain_t terrain;

int init_terrain() {
	terrain.chunk_size = (vec2u8_t) { 128, 128 };
	terrain.render_distance = 8;

	// Memory
	terrain.tot_chunks = terrain.render_distance * terrain.render_distance;
	//terrain.chunk_models = malloc(terrain.tot_chunks * sizeof(Model));
	//terrain.chunk_locs = malloc(terrain.tot_chunks * sizeof(vec2i16_t));
	//terrain.chunk_status = malloc(terrain.tot_chunks * sizeof(uint8_t));
	terrain.chunk_gen_buffer = malloc((terrain.chunk_size.x + 1) * (terrain.chunk_size.y + 1) * sizeof(float));

	// Texture
	terrain.texture = LoadTexture("./res/textures/grass.png");

	return 0;
}

int free_terrain() {
	// Free it
	//free(terrain.chunk_models);
	//free(terrain.chunk_locs);
	//free(terrain.chunk_status);
	free(terrain.chunk_gen_buffer);

	return 0;
}

Model generate_chunk(vec2i16_t chunk_pos) {
	// Set up noise
	noise.chunk_pos = chunk_pos;
	noise.type = NOISE_PERLIN_OCTAVES;

	// Load heighmap
	for (size_t x = 0; x < terrain.chunk_size.x + 1; ++x) {
		for (size_t y = 0; y < terrain.chunk_size.y + 1; ++y) {
			terrain.chunk_gen_buffer[x + (y * terrain.chunk_size.x)] = 6.0f - sample_perlin(x, y, 0.1f, 7) * 12.0f;
		}
	}

	// Generate mesh for chunk
	meshgen_t meshgen = new_mesh(terrain.chunk_size.x * terrain.chunk_size.y * 2);

	for (size_t x = 0; x < terrain.chunk_size.x; ++x) {
		for (size_t y = 0; y < terrain.chunk_size.y; ++y) {
			const float BL = terrain.chunk_gen_buffer[x + (y * terrain.chunk_size.x)];
			const float TL = terrain.chunk_gen_buffer[x + ((y + 1) * terrain.chunk_size.x)];
			const float BR = terrain.chunk_gen_buffer[(x + 1) + (y * terrain.chunk_size.x)];
			const float TR = terrain.chunk_gen_buffer[(x + 1) + ((y + 1) * terrain.chunk_size.x)];

			add_vert(&meshgen, x + 0.0f, BL, y + 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f);
			add_vert(&meshgen, x + 0.0f, TL, y + 1.0f, 0.0f, 1.0f, 1.0f, 1.0f, 0.0f);
			add_vert(&meshgen, x + 1.0f, BR, y + 0.0f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f);

			add_vert(&meshgen, x + 0.0f, TL, y + 1.0f, 0.0f, 1.0f, 1.0f, 1.0f, 0.0f);
			add_vert(&meshgen, x + 1.0f, TR, y + 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f);
			add_vert(&meshgen, x + 1.0f, BR, y + 0.0f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f);
		}
	}

	Model model = generate_model(meshgen);
	model.materials[0].maps[MATERIAL_MAP_DIFFUSE].texture = terrain.texture;

	return model;
}
