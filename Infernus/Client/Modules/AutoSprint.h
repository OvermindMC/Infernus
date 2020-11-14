#pragma once
#include "../../Other/VComponent.h"

class AutoSprint : public VModule {
public:
	AutoSprint() : VModule::VModule("AutoSprint", "Automatically sprint forward") {};
	void onGmTick();
};