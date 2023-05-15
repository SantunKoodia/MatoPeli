#include <SDL.h>
#include <iostream>

//Screen dimension constants
const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

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
			// yes

			// render background 
			SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);

			// clear window
			SDL_RenderClear(renderer);

			// rectangle
			SDL_Rect r; 
			r.x = 50;
			r.y = 50;
			r.w = 50;
			r.h = 50;

			// initialize renderer color
			SDL_SetRenderDrawColor(renderer, 0, 0, 255, 255);

			// Render rectangle
			SDL_RenderFillRect(renderer, &r);

			// Render the rect to the screen
			SDL_RenderPresent(renderer);

			SDL_Delay(500);
		}

		//SDL_Event e; bool quit = false; while (quit == false) { while (SDL_PollEvent(&e)) { if (e.type == SDL_QUIT) quit = true; } }
	}

	// free memory
	Close(window, renderer);

	std::cout << "End program" << std::endl;
	return 0;
}




