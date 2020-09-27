#pragma once
#include "../../Other/VComponent.h"

class HighJump : public VModule {
public:
	HighJump() : VModule::VModule("HighJump", "Jump Higher") {};
	void onJump(float*);
};

void HighJump::onJump(float* jumpHeight) {
	*jumpHeight = 0.6f;
};