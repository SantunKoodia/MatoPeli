#include <SDL.h>
#include <iostream>
#include <vector>

//Screen dimension constants
const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;
const int BLOCK_SIZE = 10;

enum DIRECTIONS {NONE, LEFT, RIGHT, UP, DOWN};

class Mato{
public:
	int x, y, direction;
	std::vector<int> color;
	Mato();
	void Move();
};
Mato::Mato() {
	x = SCREEN_WIDTH / 2;
	y = SCREEN_HEIGHT / 2;
	color = {0, 0, 255};
	direction = NONE;
}
void Mato::Move() {
	if (direction == LEFT) {
		x -= BLOCK_SIZE;
	}
	if (direction == RIGHT) {
		x += BLOCK_SIZE;
	}
	if (direction == UP) {
		y -= BLOCK_SIZE;
	}
	if (direction == DOWN) {
		y += BLOCK_SIZE;
	}
}

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

	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

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
void DrawSnake(SDL_Renderer* renderer, Mato mato)
{
	SDL_Rect fillRect = { mato.x, mato.y, BLOCK_SIZE, BLOCK_SIZE}; // X location of upper left corner, Y location of upper left corner, W width of the rectangle, H height of the rectangle
	SDL_SetRenderDrawColor(renderer, mato.color[0], mato.color[1], mato.color[2], 255);
	SDL_RenderFillRect(renderer, &fillRect);
	//SDL_RenderDrawRect(renderer, &fillRect); // Outlines only
	//SDL_RenderDrawLine(renderer, 0, SCREEN_HEIGHT / 2, SCREEN_WIDTH, SCREEN_HEIGHT / 2); // render line
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

	// Check that it was succsefull
	if (renderer != NULL)
	{

		// Initialize loop flag and event variable
		bool run = true;
		SDL_Event e;

		// while application is running
		while (run)
		{
			// Handle events on queue
			while (SDL_PollEvent(&e) != 0)
			{
				// user requests to quit
				if (e.type == SDL_QUIT) // event type SDL_QUIT is generated when for an example, user clicks on the close button of the window
				{
					std::cout << "Quit event called!" << std::endl;
					run = false;
				}
			}

			// code here

			// render background 
			SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
			// clear window
			SDL_RenderClear(renderer);

			// Mato class here
			Mato mato;

			//DrawRectangle(renderer, rect);
			DrawSnake(renderer, mato);

			// Render to screen
			SDL_RenderPresent(renderer);
		}

		//SDL_Event e; bool quit = false; while (quit == false) { while (SDL_PollEvent(&e)) { if (e.type == SDL_QUIT) quit = true; } }
	}

	// free memory
	Close(window, renderer);

	std::cout << NONE << LEFT << RIGHT << UP << DOWN << "done" << std::endl;

	std::cout << "End program" << std::endl;
	return 0;
}




