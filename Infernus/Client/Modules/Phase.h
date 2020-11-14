#pragma once
#include "../../Other/VComponent.h"

class Phase : public VModule {
public:
	Phase() : VModule::VModule("Phase", "Walk through walls") {};
	void onGmTick();
	void onDisable();
};