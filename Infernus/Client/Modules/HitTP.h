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

void HitTP::onAttack(Actor* attacker, Actor* victim) {
	LocalPlayer* Player = Minecraft::GetLocalPlayer();
	if (Player != nullptr) {
		if (Player->toActor() == attacker) {
			Vec3 targetPos = *victim->getPos();
			targetPos.y += yUp;
			Player->setPos(&targetPos);
		};
	};
};