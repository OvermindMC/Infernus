#pragma once
#include "../../Other/VComponent.h"

class Velocity : public VModule {
public:
	Velocity() : VModule::VModule("Velocity", "Reduces knockback") {};
	void onLerpMotion(Vec3*);
};

void Velocity::onLerpMotion(Vec3* Vel) {
	Vel->x = 0.0f, Vel->y = 0.0f, Vel->z = 0.0f;
};