#ifndef MESH_GEN_H
#define MESH_GEN_H

#include <stdint.h>
#include <raylib.h>

// Meshgen:
// Generate meshes for use in Raylib faster and easier than with raw functions raylib provide.

typedef struct meshgen_t {
	float *verts;
	float *uvs;
	float *normals;

	uint32_t num_tris;
	uint32_t current_index;
} meshgen_t;

meshgen_t new_mesh(uint16_t num_tris); // Mallocates memory for the mesh and sets up data for mesh
int add_vert(meshgen_t *meshgen, float x, float y, float z, float u, float v, float nx, float ny, float nz); // Add verticie to mesh
Mesh generate_mesh(meshgen_t src);
Model generate_model(meshgen_t src);

#endif