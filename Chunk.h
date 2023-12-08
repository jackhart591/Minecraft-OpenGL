#pragma once
#include "Block.h"

#define CHUNK_SIZE 16

class Chunk {

private:
	Block*** blocks;

public:
	Chunk();
	~Chunk();
	void SetBlock(int, int, int);
	Block GetBlock(int, int, int);
};
