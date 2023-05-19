#pragma once
#include <vector>

class Mato
{
public:
	int x, y, direction, foodEaten;
	std::vector<int> color;
	std::vector<int> tailX, tailY;
	Mato(int startX, int startY, int inputSize, std::vector<int> inputColor);
	void Move();
	int blockSize;
};