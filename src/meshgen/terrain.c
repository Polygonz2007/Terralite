
#include <terrain.h>
#include <meshgen.h>
#include <noise.h>

// Noise
extern noise_t noise;

int init_terrain() {
	return 0; // :)
}

Model generate_chunk(vec2i16_t chunk_pos) {
	// Set up noise
	noise.chunk_pos = chunk_pos;
	noise.type = NOISE_PERLIN_OCTAVES;

	// Generate mesh for chunk
	meshgen_t meshgen = new_mesh(100);

	for (size_t i = 0; i < 10; ++i) {
		for (size_t j = 0; j < 10; ++j) {
			const h = sample_noise(i, j);
			add_vert(&meshgen, i + 0.0f, 0.0f, j + 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f);
			add_vert(&meshgen, i + 1.0f, 0.0f, j + 1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f);
			add_vert(&meshgen, i + 1.0f, 0.0f, j + 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f);
		}
	}

	Model model = generate_model(meshgen);
}
