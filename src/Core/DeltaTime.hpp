#pragma once

#include <ctime>

class DeltaTime {
public:
	inline DeltaTime() { lastTime = std::clock(); }

	//-----------------------------------------------------------------------------
	// Calculate the difference between this "UpdateDeltaTime" call 
	// and the previous call.
	// Returns: 
	//      The deltaTime between each calls.
	//-----------------------------------------------------------------------------
	inline float UpdateDeltaTime(){
		std::clock_t currentTime = std::clock();
		float deltaTime = static_cast<float>(currentTime - lastTime) / CLOCKS_PER_SEC;
		lastTime = currentTime;

		return deltaTime;
	}

private:
	std::clock_t lastTime;
};