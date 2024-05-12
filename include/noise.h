#ifndef NOISE_H
#define NOISE_H

#include <stdint.h>

typedef struct noise_t {
	vec2i16_t chunk_pos;

	uint8_t type;
	float scale;
	float lacunarity;
	float persistance;
} noise_t;

enum noise_type {
	NOISE_VALUE,
	NOISE_PERLIN,
	NOISE_PERLIN_OCTAVES
};

double sample_noise(float x, float z);

#endif