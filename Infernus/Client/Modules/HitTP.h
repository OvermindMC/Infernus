#pragma once
#include "../../Other/VComponent.h"

class HitTP : public VModule {
public:
	HitTP() : VModule::VModule("HitTP", "Teleport to the entity you're attacking") {
		this->addWindowObj(new VWindowSlider("Teleport Y: ", &this->yUp));
	};
	void onAttack(Actor* attacker, Actor* victim);
private:
	float yUp = 1.0f;
};