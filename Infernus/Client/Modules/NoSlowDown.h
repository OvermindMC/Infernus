#pragma once
#include "../../Other/VComponent.h"

class NoSlowDown : public VModule {
public:
	NoSlowDown() : VModule::VModule("NoSlowDown", "Eat/use items whilst sprinting") {};
	void onEnable();
	void onDisable();
private:
	std::vector<uintptr_t> opCodeAddresses;
};