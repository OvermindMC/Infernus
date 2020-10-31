#pragma once
#include "../../Other/VComponent.h"

class TPAura : public VModule {
public:
	TPAura() : VModule::VModule("TPAura", "Teleports around the entity that you're attacking") {
		this->addWindowObj(new VWindowSlider("Range: ", &this->tpRange));
		this->addWindowObj(new VWindowSlider("Delay (MS): ", &this->delay_ms));
		this->addWindowObj(new VWindowButton("Send Move Packets", &this->sendPackets));
	};
	void onAttack(Actor*, Actor*);
	void onLoop() { delay_ms = roundf(delay_ms); };
private:
	bool sendPackets = false;
	float tpRange = 5.0f;
	int count = 0;
	float delay_ms = 100.0f;
	std::chrono::time_point<std::chrono::steady_clock> savedTime = std::chrono::high_resolution_clock::now();
};

void TPAura::onAttack(Actor* attacker, Actor* victim) {
	if (std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::high_resolution_clock::now() - savedTime) >= std::chrono::milliseconds((int)delay_ms)) {
		LocalPlayer* Player = Minecraft::GetLocalPlayer();
		if (Player != nullptr && Player->toActor() == attacker) {
			Vec3 entPos = *victim->getPos();
			float newX = entPos.x + Utils::randomFloat(-tpRange, tpRange);
			float newZ = entPos.z + Utils::randomFloat(-tpRange, tpRange);
			Vec3 teleportPos(newX, Player->getPos()->y, newZ);
			Block* block = Player->BlockSource->getBlock(teleportPos);
			if (block->toLegacy()->blockID == 0) {
				Player->setPos(&teleportPos);
				if (sendPackets) {
					MovePlayerPacket newPacket(Player->toActor(), teleportPos, Player->lookingVector, Player->onGround);
					Minecraft::GetClientInstance()->LoopbackPacketSender->sendToServer(&newPacket);
				};
			};
			/*else {
				if (count >= (int)(tpRange * 2)) {
					count = 0;
				}
				else {
					count++;
					this->onAttack(attacker, victim);
				};
			};*/
		};
		savedTime = std::chrono::high_resolution_clock::now();
	};
};