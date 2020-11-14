#include "BoostHit.h"
#include "../../SDK/Minecraft.h"

Vec2 BoostHit::getRotationsToEnt(LocalPlayer* Player, Actor* Target) {
	Vec3 currPos = *Player->getPos();
	Vec3 targetPos = *Target->getPos();
	float dX = currPos.x - targetPos.x;
	float dY = currPos.y - targetPos.y;
	float dZ = currPos.z - targetPos.z;
	float distance = sqrt(dX * dX + dY * dY + dZ * dZ);
	return Vec2(-(float)atan2(dY, distance) * (180.0f / PI), (float)atan2(dZ, dX) * (180.0f / PI) + 90.0f);
};

void BoostHit::onAttack(Actor* attacker, Actor* victim) {
	LocalPlayer* Player = Minecraft::GetLocalPlayer();
	if (Player != nullptr) {
		if (Player->toActor() == attacker) {
			float yaw = Player->getRotationsToEnt(victim).y + 90.0f; //getRotationsToEnt(Player, victim).y + 90.0f;
			Player->Velocity.x = cos((yaw) * (PI / 180.0f)) * boost;
			Player->Velocity.z = sin((yaw) * (PI / 180.0f)) * boost;
		};
	};
};