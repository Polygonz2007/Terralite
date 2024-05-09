
// Three-dimensional vectors
#ifndef VEC3_H
#define VEC3_H

#include <stdint.h>

typedef struct vec3i8_t {
	int8_t x;
	int8_t y;
	int8_t z;
} vec3i8_t;

typedef struct vec3i16_t {
	int16_t x;
	int16_t y;
	int16_t z;
} vec3i16_t;

typedef struct vec3i32_t {
	int32_t x;
	int32_t y;
	int32_t z;
} vec3i32_t;

typedef struct vec3u8_t {
	uint8_t x;
	uint8_t y;
	uint8_t z;
} vec3u8_t;

typedef struct vec3u16_t {
	uint16_t x;
	uint16_t y;
	uint16_t z;
} vec3u16_t;

typedef struct vec3u32_t {
	uint32_t x;
	uint32_t y;
	uint32_t z;
} vec3u32_t;

#endif