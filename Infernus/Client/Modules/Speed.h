#pragma once
#include "../../Other/VComponent.h"

class Speed : public VModule {
public:
	Speed() : VModule::VModule("Speed", "Move faster than others") {
		this->addWindowObj(new VWindowSlider("Speed: ", &this->speed));
	};
	void onGmTick();
public:
	float speed = 0.6f;
};