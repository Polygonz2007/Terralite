
#include <malloc.h>
#include <terrain.h>
#include <meshgen.h>
#include <noise.h>

// Noise
extern noise_t noise;

// Terain
terrain_t terrain;

// Player
#include <player.h>
extern player_t player;

int init_terrain() {
	terrain.chunk_size = (vec2u8_t) { 16, 16 };
	terrain.render_distance = 8;
	
	// Memory
	terrain.tot_chunks = terrain.render_distance * terrain.render_distance;
	terrain.chunk_models = malloc(terrain.tot_chunks * sizeof(Model));
	terrain.chunk_locs = malloc(terrain.tot_chunks * sizeof(vec2i16_t));
	terrain.chunk_status = malloc(terrain.tot_chunks * sizeof(uint8_t));
	terrain.chunk_gen_buffer = malloc((terrain.chunk_size.x + 1) * (terrain.chunk_size.y + 1) * sizeof(float));
	
	// Default
	for (size_t i = 0; i < terrain.tot_chunks; ++i) {
		terrain.chunk_status[i] = CHUNK_UNLOADED;
	}

	// Texture
	terrain.texture = LoadTexture("./res/textures/grass.png");

	return 0;
}

int free_terrain() {
	// Free it
	free(terrain.chunk_models);
	free(terrain.chunk_locs);
	free(terrain.chunk_status);
	free(terrain.chunk_gen_buffer);

	return 0;
}

int32_t get_chunk_index(vec2i16_t chunk_pos) {
	for (size_t i = 0; i < terrain.tot_chunks; ++i) {
		const vec2i16_t check_pos = terrain.chunk_locs[i];
		if (check_pos.x == chunk_pos.x && check_pos.y == chunk_pos.y)
			if (terrain.chunk_status[i] != CHUNK_UNLOADED)
				return i;
			else
				return -1;
	}

	return -1;
}

int32_t next_chunk_index() {
	for (size_t i = 0; i < terrain.tot_chunks; ++i) {
		if (terrain.chunk_status[i] == CHUNK_UNLOADED)
			return i;
	}

	return -1;
}

int load_chunk(vec2i16_t chunk_pos) {
	int32_t chunk_index = get_chunk_index(chunk_pos);
	if (chunk_index != -1)
		return -1; // already loaded so we cant double load it idot
	
	// Get available index
	chunk_index = next_chunk_index();
	if (chunk_index == -1)
		return -1; // no available slots

	// Start loading it
	terrain.chunk_status[chunk_index] = CHUNK_LOADING;
	terrain.chunk_locs[chunk_index] = chunk_pos;
	terrain.chunk_models[chunk_index] = generate_chunk(chunk_pos);

	terrain.chunk_status[chunk_index] = CHUNK_LOADED;
	terrain.chunks_loaded++;
	printf("\nLoaded a chunk");
	return 0;
}

int unload_chunk(vec2i16_t chunk_pos) {
	const int32_t chunk_index = get_chunk_index(chunk_pos);
	if (chunk_index == -1)
		return -1; // already unloaded so we cant double unload it idot

	// Unload (aka mark as empty)
	UnloadModel(terrain.chunk_models[chunk_index]);
	terrain.chunk_status[chunk_index] = CHUNK_UNLOADED;
	terrain.chunks_loaded--;
	return 0;
}

Model generate_chunk(vec2i16_t chunk_pos) {
	// Set up noise
	noise.chunk_pos = chunk_pos;
	noise.type = NOISE_PERLIN_OCTAVES;

	// Load heighmap
	for (size_t x = 0; x < terrain.chunk_size.x + 1; ++x) {
		for (size_t y = 0; y < terrain.chunk_size.y + 1; ++y) {
			terrain.chunk_gen_buffer[x + (y * terrain.chunk_size.x)] = 30.0f - sample_perlin(x, y, 0.02f, 3) * 42.0f;
		}
	}

	// Generate mesh for chunk
	meshgen_t meshgen = new_mesh(terrain.chunk_size.x * terrain.chunk_size.y * 2);

	for (size_t x = 0; x < terrain.chunk_size.x; ++x) {
		for (size_t y = 0; y < terrain.chunk_size.y; ++y) {
			const float bl = terrain.chunk_gen_buffer[x + (y * terrain.chunk_size.x)];
			const float tl = terrain.chunk_gen_buffer[x + ((y + 1) * terrain.chunk_size.x)];
			const float br = terrain.chunk_gen_buffer[(x + 1) + (y * terrain.chunk_size.x)];
			const float tr = terrain.chunk_gen_buffer[(x + 1) + ((y + 1) * terrain.chunk_size.x)];

			add_vert(&meshgen, x + 0.0f, bl, y + 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f);
			add_vert(&meshgen, x + 0.0f, tl, y + 1.0f, 0.0f, 1.0f, 1.0f, 1.0f, 0.0f);
			add_vert(&meshgen, x + 1.0f, br, y + 0.0f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f);

			add_vert(&meshgen, x + 0.0f, tl, y + 1.0f, 0.0f, 1.0f, 1.0f, 1.0f, 0.0f);
			add_vert(&meshgen, x + 1.0f, tr, y + 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f);
			add_vert(&meshgen, x + 1.0f, br, y + 0.0f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f);
		}
	}
	
	Model model = generate_model(meshgen);
	model.materials[0].maps[MATERIAL_MAP_DIFFUSE].texture = terrain.texture;

	return model;
}





int update_chunks() {
	// Unload old
	for (size_t i = 0; i < terrain.tot_chunks; ++i) {
		const vec2i16_t chunk_pos = terrain.chunk_locs[i];
		const vec2i16_t diff = {
			abs(chunk_pos.x - player.chunk_pos.x),
			abs(chunk_pos.y - player.chunk_pos.y)
		};

		if (terrain.chunk_status[i] == CHUNK_LOADED && (diff.x > terrain.render_distance || diff.y > terrain.render_distance))
			unload_chunk(chunk_pos);
	}

	// Load new ones
	const uint8_t rd = terrain.render_distance;

	for (int16_t chunk_x = player.chunk_pos.x - rd; chunk_x < player.chunk_pos.x + rd; ++chunk_x) {
		for (int16_t chunk_y = player.chunk_pos.y - rd; chunk_y < player.chunk_pos.y + rd; ++chunk_y) {
			const vec2i16_t chunk_pos = (vec2i16_t){ chunk_x, chunk_y };
			const int32_t chunk_index = get_chunk_index((vec2i16_t) { chunk_x, chunk_y });

			if (terrain.chunk_status[chunk_index] == CHUNK_UNLOADED)
				load_chunk(chunk_pos);
		}
	}
}