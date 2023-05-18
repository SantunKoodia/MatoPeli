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
void Food::GenerateLocation(int windowSizeX, int windowSizeY)
{
	srand(time(NULL)); // randomize the seed to be used in rand()
	x = ((rand() % (windowSizeX / blockSize) + 1) * blockSize) - blockSize;

	srand(time(NULL)); // randomize the seed to be used in rand()
	y = ((rand() % (windowSizeY / blockSize) + 1) * blockSize) - blockSize;

}