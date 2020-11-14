#pragma once
#include "../../Other/VComponent.h"

class Misplace : public VModule {
public:
	Misplace() : VModule::VModule("Misplace", "Spoof Entity Positions for attacking") {
		this->addWindowObj(new VWindowSlider("Range: ", &range));
	};
	void onGmTick();
	void positionEntity(Actor*);
private:
	float range = 5.0f;
};