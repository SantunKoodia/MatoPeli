#include "Food.h"
#include <time.h>

Food::Food(int inputSize, std::vector<int> inputColor)
{
	x = 0;
	y = 0;
	blockSize = inputSize;
	color = inputColor;
}

/*
	positions are calculated in following way (from the inner parentheses to the outer ones)
	1. divide maximum window size by 10
	2. Generate random number from 0 to the result of step 1
	3. Multiply result of step 2 by 10. (steps 1 to 3 are done to get value divideable by block size
	4. remove value of blockSize from the result of step 3 to not render outside the window
*/
void Food::GenerateLocation(int windowSizeX, int windowSizeY, int extraInput) // extraInput will be foodEaten from snake
{
	// generate random seed for rand() function. Change time to long int, add extraInput and multiply to generate more random result
	srand(static_cast<long int>(time(NULL) + extraInput) * 7);
	x = ((rand() % (windowSizeX / blockSize) + 1) * blockSize) - blockSize;

	srand(static_cast<long int>(time(NULL) + extraInput) * 3);
	y = ((rand() % (windowSizeY / blockSize) + 1) * blockSize) - blockSize;
}