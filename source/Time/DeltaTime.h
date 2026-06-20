#pragma once

#include <ctime>

class DeltaTime {
	public:
		DeltaTime();

		// - Summary -----------------------------------------------------------------
		// Update and return the computed elapsed time since the last time the 
		// method was called.
		// ---------------------------------------------------------------------------
		float UpdateDeltaTime();

	private:
		std::clock_t lastTime;
};