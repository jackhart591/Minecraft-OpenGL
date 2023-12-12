#include "Chunk.h"

Chunk::Chunk() {
	this->blocks = new Block**[CHUNK_SIZE]; // blocks[x]

	for (int i = 0; i < CHUNK_SIZE; i++) {
		this->blocks[i] = new Block*[CHUNK_SIZE]; // blocks[x][y]

		for (int j = 0; j < CHUNK_SIZE; j++) {
			this->blocks[i][j] = new Block[CHUNK_SIZE]; // blocks[x][y][z]

			for (int k = 0; k < CHUNK_SIZE; k++) {
				Block none;
				none.type = Block::Type::none;
				this->blocks[i][j][k] = none;
			}
		}
	}
}

Chunk::~Chunk() {
	for (int i = 0; i < CHUNK_SIZE; i++) {
		for (int j = 0; j < CHUNK_SIZE; j++) {
			delete[] this->blocks[i][j];
		}

		delete[] this->blocks[i];
	}

	delete[] this->blocks;
}

void Chunk::SetBlock(int x, int y, int z, Block block)
{
	this->blocks[x][y][z] = block;
}

Block* Chunk::GetBlock(int x, int y, int z)
{
	Block* block;
	try {
		block = &this->blocks[x][y][z];
	}
	catch (void* e) {
		block = NULL;
	}

	return block;
}
