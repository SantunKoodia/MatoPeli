#include "Mato.h"

// enum values: {NONE = 0, LEFT = 1, RIGHT = 2, UP = 3, DOWN = 4};

// initialize Mato class. Requires the starting X and Y positions for the snake and the size of block
Mato::Mato(int startX, int startY, int size) {
	blockSize = size;
	x = startX;
	y = startY;
	color = { 0, 0, 255 };
	direction = 0;
}
void Mato::Move() {
	if (direction == 1) {
		x -= blockSize;
	}
	if (direction == 2) {
		x += blockSize;
	}
	if (direction == 3) {
		y -= blockSize;
	}
	if (direction == 4) {
		y += blockSize;
	}
}