#pragma once
#include "../../Other/VComponent.h"

class AirJump : public VModule {
public:
	AirJump() : VModule::VModule("AirJump", "Tells the game that you're on the ground") {};
	void onGmTick();
};