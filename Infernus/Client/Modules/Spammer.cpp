#include "Spammer.h"
#include "../../SDK/Minecraft.h"

void Spammer::onGmTick() {
	if (std::chrono::duration_cast<std::chrono::seconds>(std::chrono::high_resolution_clock::now() - savedTime) >= std::chrono::milliseconds((int)(delay_ms))) {
		LocalPlayer* Player = Minecraft::GetLocalPlayer();
		if (Player != nullptr) {
			int randomInt = (int)Utils::randomFloat(0, 100);
			std::string brackets = std::string("[ " + std::to_string(randomInt) + " ]");
			std::string modifiedMsg = brackets + std::string(" " + this->message + " ") + brackets;

			TextPacket newPacket(Minecraft::GetLocalPlayer()->toActor(), modifiedMsg);
			Minecraft::GetClientInstance()->LoopbackPacketSender->sendToServer(&newPacket);
		};
		savedTime = std::chrono::high_resolution_clock::now();
	};
};