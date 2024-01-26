#include "Time.h"
#include "Window.h"
#include <SDL.h>
#include <vector>
#include <cmath>

static uint32_t timeFrameStart;
static float timeRemainder = 0.F;

void Wait(uint32_t ms, uint32_t msDelayStep) {
	uint32_t endtime = SDL_GetTicks() + ms;
	for (uint32_t currentTicks = SDL_GetTicks(); currentTicks < endtime; currentTicks = SDL_GetTicks()) {
		if (SDL_GetTicks() < endtime - msDelayStep) {
			SDL_Delay(endtime - currentTicks);
		}
		else {
			SDL_Delay(msDelayStep);
		}

		HandleWindowEvents();
	}
}

void LimitFramerate(uint32_t targetFPS) {
	// calculate constants
	const uint32_t TIME_FRAME_SHOULD_LAST = 1000 / targetFPS;
	const float TIME_FRAME_SHOULD_LAST_REMAINDER = (1000.F / (float)targetFPS) - (float)TIME_FRAME_SHOULD_LAST;

	// increment remainder
	timeRemainder += TIME_FRAME_SHOULD_LAST_REMAINDER;

	// set fame times
	uint32_t timeFrameEnd = SDL_GetTicks();
	Game::dtms = timeFrameEnd - timeFrameStart;
	timeFrameStart = timeFrameEnd;

	// calculate time to wait
	int timeToWait = TIME_FRAME_SHOULD_LAST - Game::dtms + (uint32_t)std::floor(timeRemainder);
	timeRemainder -= std::floor(timeRemainder);

	// wait time
	if (timeToWait >= 0) {
		Wait(timeToWait);

		timeFrameEnd += timeToWait;
		Game::dtms += timeToWait + (uint32_t)std::floor(timeRemainder);
		Game::currentFPS = targetFPS;
	}
	else {
		timeRemainder = 0;
		// TODO: check the logic of this, it feels sketchy
		Game::currentFPS = (int)std::ceil(1000.F / Game::dtms);
	}

	// update dt
	Game::dt = (float)Game::dtms / 1000.f;
}