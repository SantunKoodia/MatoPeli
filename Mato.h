#pragma once
#include <vector>

class Mato
{
public:
	int x, y, direction;
	std::vector<int> color;
	Mato(int screenWidth, int screenHeight, int blockSize);
	void Move();
private:
	int blockSize;
};