#pragma once
#include "../../Other/VComponent.h"

class BoostHit : public VModule {
public:
	BoostHit() : VModule::VModule("BoostHit", "Boost yourself forward when attacking entities") {
		this->addWindowObj(new VWindowSlider("Boost: ", &this->boost));
	};
	void onAttack(class Actor*, class Actor*);
	Vec2 getRotationsToEnt(class LocalPlayer*, Actor*);
private:
	float boost = 1.0f;
};