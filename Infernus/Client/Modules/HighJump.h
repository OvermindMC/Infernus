#pragma once
#include "../../Other/VComponent.h"

class HighJump : public VModule {
public:
	HighJump() : VModule::VModule("HighJump", "Jump Higher") {
		this->addWindowObj(new VWindowText("Height:"));
		this->addWindowObj(new VWindowSlider(&this->jumpValue, 0.0f, 10.0f, "Height: ", MC_Colour(255, 255, 255), 1.0f, 1.0f, MC_Colour(255, 110, 30), .7f));
	};
	void onJump(float*);
private:
	float jumpValue = 0.6f;
};

void HighJump::onJump(float* jumpHeight) {
	*jumpHeight = jumpValue;
};