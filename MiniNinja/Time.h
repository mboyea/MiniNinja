#ifndef TIME_H
#define TIME_H
#pragma once

#include <cstdint>

namespace Game {
	inline unsigned int currentFPS = 0U;
	inline float dt = 0.F;
	inline uint32_t dtms = 0U;
}

void Wait(uint32_t ms, uint32_t msDelayStep = 10);
void LimitFramerate(uint32_t targetFPS = 60U);

#endif // !TIME_H