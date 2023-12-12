#pragma once
#include <map>
#include <tuple>
#include <stdexcept>
#include "Block.h"

#define CHUNK_SIZE 16

class Chunk {

private:
	Block*** blocks;

public:
	Chunk();
	~Chunk();
	void SetBlock(int, int, int, Block);
	Block* GetBlock(int, int, int);
};
