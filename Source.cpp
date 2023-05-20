#include <SDL.h>
#include <iostream>
#include <vector>
#include "Mato.h"
#include "TimerFPS.h"
#include "Food.h"

//Screen dimension constants
const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;
const int BLOCK_SIZE = 10;

enum DIRECTIONS {NONE = 0, LEFT = 1, RIGHT = 2, UP = 3, DOWN = 4};

SDL_Window* InitWindow()
{
	// initialize SDL window
	SDL_Window* window = NULL;

	// Initialize SDL
	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		std::cout << "SDL could not initialize. SDL_Error: " << SDL_GetError() << std::endl;
		return NULL;
	}
	else
	{
		// create SDL window
		window = SDL_CreateWindow("Mato peli", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);

		// Check that it was succesfull
		if (window == NULL)
		{
			std::cout << "Window could not be created. SDL_Error: " << SDL_GetError() << std::endl;
			return NULL;
		}
	}

	return window;
}


SDL_Renderer* InitRenderer(SDL_Window* window)
{

	// initialize variable
	SDL_Renderer* renderer = NULL;

	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED); // disables VSYNC

	if (renderer == NULL)
	{
		std::cout << "Renderer could not be created. SDL_Error: " << SDL_GetError() << std::endl;
		return NULL;
	}

	return renderer;
}


void Close(SDL_Window* window, SDL_Renderer* renderer)
{
	// Deallocate surface
	SDL_DestroyRenderer(renderer);
	renderer = NULL;

	// Destroy window
	SDL_DestroyWindow(window);
	window = NULL;

	// quit SDL subsystems
	SDL_Quit();

	std::cout << "Renderer and window freed" << std::endl;
}


// can render multiple renders
void DrawObjects(SDL_Renderer* renderer, Mato mato, Food food)
{
	SDL_Rect foodRectangle = { food.x, food.y, BLOCK_SIZE, BLOCK_SIZE };
	SDL_SetRenderDrawColor(renderer, food.color[0], food.color[1], food.color[2], 255);
	SDL_RenderFillRect(renderer, &foodRectangle);

	SDL_Rect matoRectangle = { mato.x, mato.y, BLOCK_SIZE, BLOCK_SIZE}; // X location of upper left corner, Y location of upper left corner, W width of the rectangle, H height of the rectangle
	SDL_SetRenderDrawColor(renderer, mato.color[0], mato.color[1], mato.color[2], 255);
	SDL_RenderFillRect(renderer, &matoRectangle);

	// TODO: Render tail
	for (int i = 0; i < mato.foodEaten; i++)
	{
		//std::cout << "x: " << mato.tailX[i] << ", y: " << mato.tailY[i] << std::endl;
		SDL_Rect tailPartRectangle = { mato.tailX[i], mato.tailY[i], BLOCK_SIZE, BLOCK_SIZE};
		SDL_SetRenderDrawColor(renderer, mato.color[0], mato.color[1], mato.color[2], 255);
		SDL_RenderFillRect(renderer, &tailPartRectangle);
	}
	
	//SDL_RenderDrawRect(renderer, &fillRect); // Outlines only
	//SDL_RenderDrawLine(renderer, 0, SCREEN_HEIGHT / 2, SCREEN_WIDTH, SCREEN_HEIGHT / 2); // render line
}

bool CheckIfColliding(int x1, int y1, int size1, int x2, int y2, int size2)
{
	// find center of first parameters (x1, y1 and size1)
	int centerX = (x1 + (size1 / 2));
	int centerY = (y1 + (size1 / 2));

	// check center is inside second parameters (x2, y2 and size2)
	if (centerX >= x2 and centerX <= x2+size2) 
	{
		if (centerY >= y2 and centerY <= y2 + size2)
		{
			return true;
		}
	}
	return false;
}

bool CheckIfOutsideWindow(int x, int y)
{
	int centerX = (x + (BLOCK_SIZE / 2));
	int centerY = (y + (BLOCK_SIZE / 2));

	if (centerX < 0 or centerX > SCREEN_WIDTH)
	{
		return true;
	}
	if (centerY < 0 or centerY > SCREEN_HEIGHT)
	{
		return true;
	}
	return false;
}


int main(int argc, char* args[])
{
	std::cout << "Start program" << std::endl;

	// SDL window that will do the rendering
	SDL_Window* window = NULL;  
	window = InitWindow();

	// window renderer
	SDL_Renderer* renderer = NULL;
	renderer = InitRenderer(window);

	// Frame rate variables
	int fps = 90;
	int ScreenTicsPerFrame = 2750 / fps; 

	// Timers to calculate and cap FPS
	TimerFPS fpsTimer;
	TimerFPS capTimer;

	// start counting fps
	int frameCount = 0;
	fpsTimer.Start();

	// Init Mato class 
	Mato mato(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, BLOCK_SIZE, { 0, 0, 255 });
	Food food(BLOCK_SIZE, { 255, 0, 0 });

	// Check that it was succsefull
	if (renderer != NULL)
	{

		// Initialize loop flag and event variable
		bool run = true;
		SDL_Event e;

		// Randomize location for food
		food.GenerateLocation(SCREEN_WIDTH, SCREEN_HEIGHT, 0);

		// while application is running
		while (run)
		{
			// start/reset cap timer
			capTimer.Start();

			// Handle events on queue
			while (SDL_PollEvent(&e) != 0)
			{
				// user requests to quit
				if (e.type == SDL_QUIT) // event type SDL_QUIT is generated when for an example, user clicks on the close button of the window
				{
					std::cout << "Quit event called!" << std::endl;
					run = false;
				}

				// user presses key
				else if (e.type == SDL_KEYDOWN)
				{
					switch (e.key.keysym.sym) 
					{
						case SDLK_UP:
							if (mato.direction != DOWN) {
								mato.direction = UP;
							}
							break;

						case SDLK_DOWN:
							if (mato.direction != UP) {
								mato.direction = DOWN;
							}
							break;

						case SDLK_LEFT:
							if (mato.direction != RIGHT) {
								mato.direction = LEFT;
							}
							break;

						case SDLK_RIGHT:
							if (mato.direction != LEFT) {
								mato.direction = RIGHT;
							}
							break;
					}
				}
			}

			// check if snake (head) is outside the window or touching food
			if (CheckIfColliding(mato.x, mato.y, mato.blockSize, food.x, food.y, food.blockSize))
			{
				food.GenerateLocation(SCREEN_WIDTH, SCREEN_HEIGHT, mato.foodEaten);
				mato.foodEaten += 1;
				//std::cout << mato.foodEaten << std::endl;
			}

			

			if (CheckIfOutsideWindow(mato.x, mato.y))
			{
				std::cout << "Hit wall!" << std::endl;
				run = false;
			}

			// add new tail piece
			if (mato.tailX.size() < mato.foodEaten)
			{
				std::cout << "adding new piece" << std::endl;
				mato.tailX.insert(mato.tailX.begin(), mato.x);
				mato.tailY.insert(mato.tailY.begin(), mato.y);
			}

			// get the coordinates for the tail parts
			for (int i = mato.tailX.size()-1; i >= 0; i--)
			{
				//std::cout << i << std::endl;
				if (i == 0) { // place the part closest to the head onto the head
					mato.tailX[i] = mato.x;
					mato.tailY[i] = mato.y;
				}
				else { // move tail parts up
					mato.tailX[i] = mato.tailX[i-1];
					mato.tailY[i] = mato.tailY[i-1];

					// check if snake (head) is touching its own tail
					if (CheckIfColliding(mato.x, mato.y, mato.blockSize, mato.tailX[i], mato.tailY[i], mato.blockSize) and i > 1)
					{
						std::cout << "Hit tail!" << std::endl;
						run = false;
					}
				}
			}

			// render background 
			SDL_SetRenderDrawColor(renderer, 45, 180, 0, 255);
			// clear window
			SDL_RenderClear(renderer);

			// Snake and Food stuff here
			mato.Move();

			//DrawRectangle(renderer, rect);
			DrawObjects(renderer, mato, food);

			// calculate and correct fps
			float avgFps = frameCount / (fpsTimer.GetTicks() / 1000.f);
			if (avgFps > 2000000) {
				avgFps = 0;
			}

			// Render to screen
			SDL_RenderPresent(renderer);

			frameCount++;
			int frameTicks = capTimer.GetTicks();
			if (frameTicks < ScreenTicsPerFrame) {
				// wait remaining time
				SDL_Delay(ScreenTicsPerFrame - frameTicks);
			}
		}

		//SDL_Event e; bool quit = false; while (quit == false) { while (SDL_PollEvent(&e)) { if (e.type == SDL_QUIT) quit = true; } }
	}

	// free memory
	Close(window, renderer);

	//std::cout << NONE << LEFT << RIGHT << UP << DOWN << "done" << std::endl;

	std::cout << "End program" << std::endl;
	return 0;
}




