#pragma once
#include "../../Other/VComponent.h"

class Velocity : public VModule {
public:
	Velocity() : VModule::VModule("Velocity", "Reduces knockback") {
		this->addWindowObj(new VWindowSlider("Knockback X: ", &modifyX));
		this->addWindowObj(new VWindowSlider("Knockback Y: ", &modifyY));
		this->addWindowObj(new VWindowSlider("Knockback Z: ", &modifyZ));
	};
	void onLerpMotion(Vec3*);
private:
	float modifyX, modifyY, modifyZ;
};