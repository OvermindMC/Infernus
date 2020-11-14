#pragma once
#include "../../Other/VComponent.h"

class AutoTotem : public VModule {
public:
	AutoTotem() : VModule::VModule("AutoTotem", "Automatically equip totems in your second hand") {};
	void onGmTick();
private:
	int delay = 0;
};