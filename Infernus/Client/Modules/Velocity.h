#pragma once
#include "../../Other/VComponent.h"

class Velocity : public VModule {
public:
	Velocity() : VModule::VModule("Velocity", "Reduces knockback") {
		VWindowText* expandableText = new VWindowText("Velocity Modifiers");
		expandableText->addExpandedItem(new VWindowSlider(&modifyX, 0.0f, 5.0f, "X: "));
		expandableText->addExpandedItem(new VWindowSlider(&modifyY, 0.0f, 5.0f, "Y: "));
		expandableText->addExpandedItem(new VWindowSlider(&modifyZ, 0.0f, 5.0f, "Z: "));
		this->addWindowObj(expandableText);
	};
	void onLerpMotion(Vec3*);
private:
	float modifyX, modifyY, modifyZ;
};

void Velocity::onLerpMotion(Vec3* Vel) {
	Vel->x *= modifyX, Vel->y *= modifyY = modifyZ, Vel->z = 0.0f;
};