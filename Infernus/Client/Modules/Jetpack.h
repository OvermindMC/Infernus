#pragma once
#include "../../Other/VComponent.h"

class Jetpack : public VModule {
public:
	Jetpack() : VModule::VModule("Jetpack", "Boost directly forward when holding the F key", 0x46) {
		this->addWindowObj(new VWindowSlider("Speed: ", &this->speed));
	};
	void onGmTick();

	float speed = 1.0f;
};