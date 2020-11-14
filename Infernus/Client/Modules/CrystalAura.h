#pragma once
#include "../../Other/VComponent.h"

class CrystalAura : public VModule {
public:
	CrystalAura() : VModule::VModule("CrystalAura", "Automatically blow up ender crystals") {
		this->addWindowObj(new VWindowSlider("Range: ", &range));
		this->addWindowObj(new VWindowButton("AutoPlace", &autoPlace));
	};
	void onLoop();
	void onGmTick();
	void placeAround(Actor*);
	void onCrystal(Actor*);
	void initHook();

	void onEnable() { this->delay = 0; };

	int delay = 0;
	float range = 5.0;
	bool autoPlace = true;
private:
	bool hookRan = false;
};