#pragma once
#include <vector>

class Mato
{
public:
	int x, y, direction, foodEaten;
	std::vector<int> color;
	Mato(int startX, int startY, int inputSize, std::vector<int> inputColor);
	void Move();
	int blockSize;
};