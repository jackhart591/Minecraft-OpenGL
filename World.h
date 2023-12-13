#pragma once
#include <vector>
#include <map>
#include <math.h>
#include "Chunk.h"

class World {
	
private:
	std::map<Vector3, Chunk*> chunks;
	std::vector<Block> blocks;

	void defineChunk(int, int, int);

public:
	// Has to be multiples of 16
	const int WORLD_LENGTH = 96;
	const int WORLD_WIDTH = 96;
	const int WORLD_HEIGHT = 16;

	World();
	~World();
	void Generate();
	Block* GetBlock(Vector3);
	void SetBlock(Vector3, Block*);
};
