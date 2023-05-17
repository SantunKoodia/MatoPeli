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


//The application time based timer
class FPSTimer
{
	public:
		//Initializes and functions
		FPSTimer();
		void Start();
		void Stop();
		void Pause();
		void Unpause();

		//Gets the timer's time
		Uint32 getTicks();

		//The timer status
		bool mPaused;
		bool mStarted;

	private:
		//The clock time when the timer started
		Uint32 mStartTicks;

		//The ticks stored when the timer was paused
		Uint32 mPausedTicks;
};

		
FPSTimer::FPSTimer()
{
	//Initialize the variables
	mStartTicks = 0;
	mPausedTicks = 0;

	mPaused = false;
	mStarted = false;
}
void FPSTimer::Start()
{
	//Start the timer
	mStarted = true;

	//Unpause the timer
	mPaused = false;

	//Get the current clock time
	mStartTicks = SDL_GetTicks();
	mPausedTicks = 0;
}
void FPSTimer::Stop()
{
	//Stop the timer
	mStarted = false;

	//Unpause the timer
	mPaused = false;

	//Clear tick variables
	mStartTicks = 0;
	mPausedTicks = 0;
}
void FPSTimer::Pause()
{
	//If the timer is running and isn't already paused
	if (mStarted && !mPaused)
	{
		//Pause the timer
		mPaused = true;

		//Calculate the paused ticks
		mPausedTicks = SDL_GetTicks() - mStartTicks;
		mStartTicks = 0;
	}
}
void FPSTimer::Unpause()
{
	//If the timer is running and paused
	if (mStarted && mPaused)
	{
		//Unpause the timer
		mPaused = false;

		//Reset the starting ticks
		mStartTicks = SDL_GetTicks() - mPausedTicks;

		//Reset the paused ticks
		mPausedTicks = 0;
	}
}
Uint32 FPSTimer::getTicks()
{
	//The actual timer time
	Uint32 time = 0;

	//If the timer is running
	if (mStarted)
	{
		//If the timer is paused
		if (mPaused)
		{
			//Return the number of ticks when the timer was paused
			time = mPausedTicks;
		}
		else
		{
			//Return the current time minus the start time
			time = SDL_GetTicks() - mStartTicks;
		}
	}

	return time;
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

	// Frame rate variables
	int fps = 90;
	int ScreenTicsPerFrame = 2750 / fps; 

	// Timers to calculate and cap FPS
	FPSTimer fpsTimer;
	FPSTimer capTimer;

	// start counting fps
	int frameCount = 0;
	fpsTimer.Start();

	// Init Mato class 
	Mato mato;

	// Check that it was succsefull
	if (renderer != NULL)
	{

		// Initialize loop flag and event variable
		bool run = true;
		SDL_Event e;

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
							mato.direction = UP;
							break;

						case SDLK_DOWN:
							mato.direction = DOWN;
							break;

						case SDLK_LEFT:
							mato.direction = LEFT;
							break;

						case SDLK_RIGHT:
							mato.direction = RIGHT;
							break;

						//default:
						// code

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
			DrawSnake(renderer, mato);

			// calculate and correct fps
			float avgFps = frameCount / (fpsTimer.getTicks() / 1000.f);
			if (avgFps > 2000000) {
				avgFps = 0;
			}

			// Render to screen
			SDL_RenderPresent(renderer);

			frameCount++;
			int frameTicks = capTimer.getTicks();
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




