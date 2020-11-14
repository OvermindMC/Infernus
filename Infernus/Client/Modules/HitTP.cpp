#include "HitTP.h"
#include "../../SDK/Minecraft.h"

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