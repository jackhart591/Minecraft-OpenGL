#pragma once
#include "Chunk.h"

class World {
	
private:
	Chunk*** chunks;

public:
	void Generate();
	Block GetBlock(int, int, int);
};
