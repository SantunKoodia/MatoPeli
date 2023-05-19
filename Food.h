#pragma once
#include <vector>

class Food
{
public:
	int x, y, blockSize;
	std::vector<int> color;
	Food(int blockSize, std::vector<int> color);
	void GenerateLocation(int windowSizeX, int windowSizeY, int extraInput);
};

