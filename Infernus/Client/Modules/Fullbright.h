#pragma once
#include "../../Other/VComponent.h"

class Fullbright : public VModule {
public:
	Fullbright() : VModule::VModule("Fullbright", "Lets you see in dark environments") {};
	void onGmTick();
	void onEnable();
	void onDisable();
private:
	float storedValue = 0.0f;
	uintptr_t gammaPtr = NULL;
};