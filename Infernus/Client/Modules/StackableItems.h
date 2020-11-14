#pragma once
#include "../../Other/VComponent.h"

class StackableItems : public VModule {
public:
	StackableItems() : VModule::VModule("StackableItems", "Stacks Items that you normally cannot stack", 0) {};
	void onGmTick();
private:
	std::chrono::time_point<std::chrono::steady_clock> savedTime = std::chrono::high_resolution_clock::now();
};