#pragma once
#include <SDL.h>

class TimerFPS
{
public:
	//Initializes and functions
	TimerFPS();
	void Start();
	void Stop();
	void Pause();
	void Unpause();

	//Gets the timer's time
	Uint32 GetTicks();

	//The timer status
	bool mPaused;
	bool mStarted;

private:
	//The clock time when the timer started
	Uint32 mStartTicks;

	//The ticks stored when the timer was paused
	Uint32 mPausedTicks;
};

