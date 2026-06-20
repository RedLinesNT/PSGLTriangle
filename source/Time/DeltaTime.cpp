#include "deltatime.h"

DeltaTime::DeltaTime() {
	lastTime = std::clock();
}

float DeltaTime::UpdateDeltaTime() {
	std::clock_t currentTime = std::clock();
	float delta = static_cast<float>(currentTime - lastTime) / CLOCKS_PER_SEC;
	lastTime = currentTime;
	return delta;
}