#pragma once
#include "../../Other/VComponent.h"

class Gamemode : public VModule {
public:
	Gamemode() : VModule::VModule("Gamemode", "Change your client sided gamemode") {
		VWindowSlider* newSlider = new VWindowSlider("Gamemode: ", &targetGamemode);
		newSlider->max = 2.f;
		this->addWindowObj(newSlider);
	};
	void onLoop();
	void onEnable();
	void onDisable();
	void onGmTick();	
private:
	bool modified = false;
	float targetGamemode = 1;
	int storedGamemode = 0;
};