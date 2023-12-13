#include "World.h"

int defineSurfaceLevel(Vector2, float, float, int, int);
float perlin(float, float);

World::World() {
	Block dirt;
	dirt.type = Block::Type::dirt;
	dirt.setFileName("block");
	blocks.push_back(dirt);

	Chunk* new_chunk = new Chunk;
	// Define all chunks and assign them to all positions
	for (int i = -(WORLD_WIDTH / 2); i < (WORLD_WIDTH / 2); i++) {
		for (int j = 0; j < WORLD_HEIGHT; j++) {
			for (int k = -(WORLD_LENGTH / 2); k < (WORLD_LENGTH / 2); k++) {
				if ((i % 16) == 0 && (j % 16) == 0 && (k % 16) == 0)
					new_chunk = new Chunk;

				for (int addr = 0; addr < 16; addr++) {
					this->chunks[Vector3{ i + addr, j + addr, k + addr }] = new_chunk;
				}
			}
		}
	}
}

World::~World() {
	std::map<Vector3, Chunk*>::iterator it = this->chunks.begin();

	for (; it != this->chunks.end(); it++) {
		if (it->second != NULL) {
			delete it->second;
			it->second = NULL;
		}
	}
}

void World::Generate()
{

	float g_freq = 10;
	float g_amp = 2;
	int resolution = 12;

	const int GRID_SIZE = 1000;

	for (int x = -(WORLD_WIDTH / 2); x < (WORLD_WIDTH / 2); x++) {
		for (int z = -(WORLD_LENGTH / 2); z < (WORLD_LENGTH / 2); z++) {
			int y = defineSurfaceLevel(Vector2{ x, z }, g_freq, g_amp, GRID_SIZE, WORLD_HEIGHT);

			// Set surface
			this->SetBlock(Vector3{ x, y, z }, &blocks[0]);

			for (int i = y-1; i >= 0; i--) {
				this->SetBlock(Vector3{ x, i, z }, &blocks[0]);
			}
		}
	}
}

int defineSurfaceLevel(Vector2 pos, float freq, float amp, int gridSize, int maxHeight) {
	float val = 0;
	for (int k = 0; k < 12; k++) {
		val += perlin(pos.x() * freq / gridSize, pos.y() * freq / gridSize) * amp;

		freq *= 2;
		amp /= 2;
	}

	if (val >= maxHeight) {
		val = maxHeight-1;
	}
	else if (val < 0) { val = 0; }

	return (int)val;
}

void World::defineChunk(int i, int j, int k) {

}

Block* World::GetBlock(Vector3 pos)
{
	Chunk* chunk = this->chunks[pos];

	int x = pos.x() % 16;
	int y = pos.y() % 16;
	int z = pos.z() % 16;

	if (x < 0) { x += 16; }
	if (y < 0) { y += 16; }
	if (z < 0) { z += 16; }

	Block* block = chunk->GetBlock(Vector3{ x, y, z });
	return block;
}

void World::SetBlock(Vector3 pos, Block* block) {
	Chunk* chunk = this->chunks[pos];

	int x = pos.x() % 16;
	int y = pos.y() % 16;
	int z = pos.z() % 16;

	if (x < 0) { x += 16; }
	if (y < 0) { y += 16; }
	if (z < 0) { z += 16; }

	chunk->SetBlock(Vector3{ x, y, z }, *block);
}

Vector<float, 2> randomGradient(int ix, int iy) {
	// No precomputed gradients mean this works for any number of grid coordinates
	const unsigned w = 8 * sizeof(unsigned);
	const unsigned s = w / 2;
	unsigned a = ix, b = iy;
	a *= 3284157443;

	b ^= a << s | a >> w - s;
	b *= 1911520717;

	a ^= b << s | b >> w - s;
	a *= 2048419325;
	float random = a * (3.14159265 / ~(~0u >> 1)); // in [0, 2*Pi]

	// Create the vector from the angle
	Vector<float, 2> v;
	v[0] = sin(random);
	v[1] = cos(random);

	return v;
}

// Computes the dot product of the distance and gradient vectors
float dotGridGradient(int ix, int iy, float x, float y) {
	
	// Get gradient from integer coordinates
	Vector<float, 2> gradient = randomGradient(ix, iy);

	// Compute the distance vector
	float dx = x - (float)ix;
	float dy = y - (float)iy;

	// Compute the dot-product
	return (dx * gradient.x() + dy * gradient.y());
}

// Computes cubic interpolation
float interpolate(float a0, float a1, float w) {
	return (a1 - a0) * (3.f - w * 2.f) * w * w + a0;
}

float perlin(float x, float y) {

	// Determin grid cell corner coordinates
	int x0 = (int)x;
	int y0 = (int)y;
	int x1 = x0 + 1;
	int y1 = y0 + 1;

	// Compute Interpolation weights
	float sx = x - (float)x0;
	float sy = y - (float)y0;

	// Compute and interpolate top two corners
	float n0 = dotGridGradient(x0, y0, x, y);
	float n1 = dotGridGradient(x1, y0, x, y);
	float ix0 = interpolate(n0, n1, sx);

	// Compute and interpolate bottom two corners
	n0 = dotGridGradient(x0, y1, x, y);
	n1 = dotGridGradient(x1, y1, x, y);
	float ix1 = interpolate(n0, n1, sx);

	// Final step: interpolate between the two previously interpolated values, now in y
	return interpolate(ix0, ix1, sy);
}
