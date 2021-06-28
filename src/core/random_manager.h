#pragma once
#include<stdlib.h>
#include<cmath>
#include<cassert>
#include"reviv/core/mat.h"
#include"reviv/physics/physics_manager.h"
#include"reviv/core/memory_manager.h"

class RandomManager {
public:
	RandomManager();
	void setUpPerlin(int perlinMapSize);
	float perlin(mat::vec2 position);
	float lerp(float a, float b, float weightA);
	int sizeOfPerlinMap;
	void shutDown() {};
	MemoryManager::Array2D<mat::vec2> gridGradient;
	MemoryManager::Array2D<float> gridPerlin;
};