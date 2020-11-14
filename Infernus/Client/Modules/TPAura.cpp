#include "TPAura.h"
#include "../../SDK/Minecraft.h"

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
		};
		savedTime = std::chrono::high_resolution_clock::now();
	};
};