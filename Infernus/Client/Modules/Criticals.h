#pragma once
#include "../../Other/VComponent.h"

class Criticals : public VModule {
public:
	Criticals() : VModule::VModule("Criticals", "Each hit is a critical hit") {};
	void onEnable();
	void onDisable();
private:
	bool modified = false;
	uintptr_t critsAddr = NULL;
};