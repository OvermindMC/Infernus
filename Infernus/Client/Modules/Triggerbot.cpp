#include "Triggerbot.h"
#include "../../SDK/Minecraft.h"

void Triggerbot::onGmTick() {
	if (std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::high_resolution_clock::now() - savedTime) >= std::chrono::milliseconds((int)delay_ms)) {
		LocalPlayer* Player = Minecraft::GetLocalPlayer();
		if (Player != nullptr) {
			Actor* facing = Player->MultiPlayerLevel->facingEnt;
			if (facing != nullptr) {
				Minecraft::GetGameMode()->attack(facing);
				Player->swing();
			};
		};
		savedTime = std::chrono::high_resolution_clock::now();
	};
};