
// Two-dimensional vectors
#ifndef VEC2_H
#define VEC2_H

#include <stdint.h>

typedef struct vec2i8_t {
	int8_t x;
	int8_t y;
} vec2i8_t;

typedef struct vec2i16_t {
	int16_t x;
	int16_t y;
} vec2i16_t;

typedef struct vec2i32_t {
	int32_t x;
	int32_t y;
} vec2i32_t;

typedef struct vec2u8_t {
	uint8_t x;
	uint8_t y;
} vec2u8_t;

typedef struct vec2u16_t {
	uint16_t x;
	uint16_t y;
} vec2u16_t;

typedef struct vec2u32_t {
	uint32_t x;
	uint32_t y;
} vec2u32_t;

#endif