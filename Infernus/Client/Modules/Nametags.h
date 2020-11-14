#pragma once
#include "../../Other/VComponent.h"

class Nametags : public VModule {
public:
	Nametags() : VModule::VModule("Nametags", "Display entity nametags even when they're crouching") {};
	void onEnable();
	void onRender();
	bool canContinueRendering();
private:
	int count = 0;
};