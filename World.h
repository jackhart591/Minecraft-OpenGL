#pragma once
#include <vector>
#include <map>
#include <math.h>
#include "Chunk.h"

class World {
	
private:
	std::map<Vector<int, 3>, Chunk*> chunks;
	std::vector<Block> blocks;

	void defineChunk(int, int, int);
	float perlin(float, float);
	float dotGridGradient(int, int, float, float);
	Vector<float, 2> randomGradient(int, int);
	float interpolate(float, float, float);

public:
	World();
	~World();
	void Generate();
	Block* GetBlock(Vector3);
};
