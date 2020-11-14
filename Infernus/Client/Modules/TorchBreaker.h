#pragma once
#include "../../Other/VComponent.h"

class TorchBreaker : public VModule {
public:
	TorchBreaker() : VModule::VModule("TorchBreaker", "Break nearby torches automatically") {
		this->addWindowObj(new VWindowSlider("Range: ", &this->range));
	};
	void onGmTick();
private:
	float range = 7;
	std::chrono::time_point<std::chrono::steady_clock> savedTime = std::chrono::high_resolution_clock::now();
};