
#include <stdio.h>
#include <malloc.h>
#include <stddef.h>
#include <meshgen.h>

meshgen_t new_mesh(uint16_t num_tris) {
	meshgen_t mg = { 0 };

	mg.num_tris = num_tris;
	mg.current_index = 0;

	const size_t size = mg.num_tris * sizeof(float);
	mg.verts = malloc(size * 3 * 3);
	mg.uvs = malloc(size * 2 * 3);
	mg.normals = malloc(size * 3 * 3);

	return mg;
}

int add_vert(meshgen_t *meshgen, float x, float y, float z, float u, float v, float nx, float ny, float nz) {
	const uint16_t index = meshgen->current_index;
	const uint32_t ind3 = index * 3;
	const uint32_t ind2 = index * 2;

	meshgen->verts[ind3 + 0] = x;
	meshgen->verts[ind3 + 1] = y;
	meshgen->verts[ind3 + 2] = z;

	meshgen->verts[ind2 + 0] = u;
	meshgen->verts[ind2 + 1] = v;

	meshgen->verts[ind3 + 0] = nx;
	meshgen->verts[ind3 + 1] = ny;
	meshgen->verts[ind3 + 2] = nz;

	meshgen->current_index++;

	printf("Added vert %d\n", meshgen->current_index);

	return 0;
}

Mesh generate_mesh(meshgen_t src) {
	Mesh mesh = { 0 };

	mesh.vertexCount = src.num_tris * 3;
	mesh.triangleCount = src.num_tris;

	mesh.vertices = src.verts;
	mesh.texcoords = src.uvs;
	mesh.normals = src.normals;

	UploadMesh(&mesh, false);
	printf("Mesh uploaded!\n");

	return mesh;
}
