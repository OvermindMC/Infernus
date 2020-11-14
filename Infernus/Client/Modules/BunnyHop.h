#pragma once
#include "../../Other/VComponent.h"

class BunnyHop : public VModule {
public:
	BunnyHop() : VModule::VModule("Bunny-Hop", "Automatically jump around like a bunny") {
		this->addWindowObj(new VWindowSlider("Speed: ", &this->speed));
	};
	void onGmTick();
	void updateKeys();
	float calcYawFromKeys();
	Vec2 yawToVelocity(float);
	void multiplyBy(Vec2*, float);
	bool usingKeys();
public:
	float speed = 0.4f;
	bool wKey = 0, sKey = 0, aKey = 0, dKey = 0;
};