#pragma once
#include "../../Other/VComponent.h"

class HighJump : public VModule {
public:
	HighJump() : VModule::VModule("HighJump", "Jump Higher") {
		this->addWindowObj(new VWindowSlider(&this->jumpValue));
	};
	void onJump(float*);
private:
	float jumpValue = 0.6f;
};

void HighJump::onJump(float* jumpHeight) {
	*jumpHeight = jumpValue;
};