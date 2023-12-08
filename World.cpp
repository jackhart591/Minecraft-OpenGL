#include "World.h"

void World::Generate()
{
	this->chunks = new Chunk**[5];
	for (int i = 0; i < 5; i++) {
		this->chunks[i] = new Chunk*[5];
		for (int j = 0; j < 5; j++) {
			this->chunks[i][j] = new Chunk[1];
			for (int x = 0; x < 16; x++) {
				for (int y = 0; y < 16; y++) {
					this->chunks[i][j][0].SetBlock(x, y, 0);
				}
			}
		}
	}
}

Block World::GetBlock(int x, int y, int z)
{
	Chunk* chunk = &this->chunks[x / 16][y / 16][z / 16];
	return chunk->GetBlock(x % 16, y % 16, z % 16);
}
