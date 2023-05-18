#include "Mato.h"

enum DIRECTIONS { NONE = 0, LEFT = 1, RIGHT = 2, UP = 3, DOWN = 4 };

// initialize Mato class. Requires the starting X and Y positions for the snake and the size of block
Mato::Mato(int startX, int startY, int inputSize, std::vector<int> inputColor) {
	blockSize = inputSize;
	x = startX;
	y = startY;
	color = inputColor;
	direction = NONE;
}
void Mato::Move() {
	if (direction == LEFT) {
		x -= blockSize;
	}
	if (direction == RIGHT) {
		x += blockSize;
	}
	if (direction == UP) {
		y -= blockSize;
	}
	if (direction == DOWN) {
		y += blockSize;
	}
}