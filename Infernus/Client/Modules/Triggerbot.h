#pragma once
#include "../../Other/VComponent.h"

class Triggerbot : public VModule {
public:
	Triggerbot() : VModule::VModule("Triggerbot", "Automatically attack facing mobs") {
		this->addWindowObj(new VWindowSlider("Delay (MS): ", &delay_ms));
	};
	void onGmTick();
	void onLoop() { delay_ms = roundf(delay_ms); };

	float delay_ms = 0.0f;
	std::chrono::time_point<std::chrono::steady_clock> savedTime = std::chrono::high_resolution_clock::now();
};