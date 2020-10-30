#pragma once
#include "../../Other/VComponent.h"

class HitTP : public VModule {
public:
	HitTP() : VModule::VModule("HitTP", "Teleport to the entity you're attacking") {
		this->addWindowObj(new VWindowSlider(&this->yUp, 0, 10.0f, "Teleport Y: ", MC_Colour(255, 255, 255), 1.0f, 1.0f, MC_Colour(255, 110, 30), .7f));
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