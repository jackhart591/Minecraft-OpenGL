#pragma once
#include <vector>
#include <math.h>
#include "Chunk.h"

class World {
	
private:
	Chunk*** chunks;
	std::vector<Block> blocks;


	typedef struct {
		float x, y;
	} vector2;

	float perlin(float, float);
	float dotGridGradient(int, int, float, float);
	vector2 randomGradient(int, int);
	float interpolate(float, float, float);

public:
	World();
	void Generate();
	Block* GetBlock(int, int, int);
};
