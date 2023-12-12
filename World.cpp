#include "World.h"

World::World() {
	this->chunks = new Chunk**[5];

	Block dirt;
	dirt.type = Block::Type::dirt;
	dirt.setFileName("block");
	blocks.push_back(dirt);

	Block none;
	none.type = Block::Type::none;
	blocks.push_back(none);
}

void World::Generate()
{

	float val = 0;
	float freq = 1;
	float amp = 1;

	const int GRID_SIZE = 400;

	for (int i = 0; i < 5; i++) {
		this->chunks[i] = new Chunk*[5];
		for (int j = 0; j < 5; j++) {
			this->chunks[i][j] = new Chunk[1];
			for (int x = 0; x < 16; x++) {
				for (int y = 0; y < 16; y++) {

					float val = 0;
					float freq = 1;
					float amp = 1;
					for (int k = 0; k < 12; k++) {
						val += perlin(i * x * freq / GRID_SIZE, j * y * freq / GRID_SIZE) * amp;

						freq *= 2;
						amp /= 2;
					}

					val *= 102;

					if (val > 15) {
						val = 15;
					}

					this->chunks[i][j][0].SetBlock(x, y, (int)val, blocks[0]);
				}
			}
		}
	}
}

Block* World::GetBlock(int x, int y, int z)
{
	Chunk* chunk = &this->chunks[x / 16][y / 16][z / 16];
	Block* block = chunk->GetBlock(x % 16, y % 16, z % 16);
	return block;
}

World::vector2 World::randomGradient(int ix, int iy) {
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
	vector2 v;
	v.x = sin(random);
	v.y = cos(random);

	return v;
}

// Computes the dot product of the distance and gradient vectors
float World::dotGridGradient(int ix, int iy, float x, float y) {
	
	// Get gradient from integer coordinates
	World::vector2 gradient = randomGradient(ix, iy);

	// Compute the distance vector
	float dx = x - (float)ix;
	float dy = y - (float)iy;

	// Compute the dot-product
	return (dx * gradient.x + dy * gradient.y);
}

// Computes cubic interpolation
float World::interpolate(float a0, float a1, float w) {
	return (a1 - a0) * (3. - w * 2.) * w * w + a0;
}

float World::perlin(float x, float y) {

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
