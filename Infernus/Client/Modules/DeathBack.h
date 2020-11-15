#pragma once
#include "../../Other/VComponent.h"

class DeathBack : public VModule {
public:
	DeathBack() : VModule::VModule("DeathBack", "Respawn at your death position when respawning") {};
	void onGmTick();
private:
	bool dead = false;
	Vec3 storedPos;
};

void DeathBack::onGmTick() {
	LocalPlayer* Player = Minecraft::GetLocalPlayer();
	if (Player != nullptr) {
		if (!Player->isAlive()) {
			if (!dead) {
				storedPos = *Player->getPos();
				dead = true;
			};
		};

		if (Player->isAlive()) {
			if (dead) {
				Player->setPos(&storedPos);
				MovePlayerPacket newPacket(Player->toActor(), storedPos, Player->lookingVector, Player->onGround);
				Minecraft::GetClientInstance()->LoopbackPacketSender->sendToServer(&newPacket);
				dead = false;
			};
		};
	}
	else {
		this->isEnabled = false;
	};
};