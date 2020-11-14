#pragma once
#include "../../Other/VComponent.h"

class ESP : public VModule {
public:
	ESP() : VModule::VModule("ESP", "Draw's boxes at the locations of other Players") {};
	void onLoop();
	void onGmTick();
	void onRender();
	bool canContinueRendering();
private:
	int count = 0;
	std::vector<Actor*> cachedPlayers = std::vector<Actor*>();
};