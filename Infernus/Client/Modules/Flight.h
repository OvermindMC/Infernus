#pragma once
#include "../../Other/VComponent.h"

class Flight : public VModule {
public:
	Flight() : VModule::VModule("Flight", "Fly even in Survival Mode") {};
	void onGmTick();
	void onDisable();
private:
	bool modified = false;
};