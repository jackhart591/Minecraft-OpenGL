#pragma once
#include <stdexcept>
#include "Vector.h"
#include "Block.h"

#define CHUNK_SIZE 16

class Chunk {

private:
	Block*** blocks;

public:
	Chunk();
	~Chunk();
	void SetBlock(Vector<int, 3>, Block);
	Block* GetBlock(Vector<int, 3>);
};
