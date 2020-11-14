#include "Phase.h"
#include "../../SDK/Minecraft.h"

void Phase::onGmTick() {
	LocalPlayer* Player = Minecraft::GetLocalPlayer();
	if (Player != nullptr) {
		Player->Position.y = (float)(Player->DefaultPosition.y);
	};
};

void Phase::onDisable() {
	LocalPlayer* Player = Minecraft::GetLocalPlayer();
	if (Player != nullptr) {
		Player->Position.y = (float)(Player->DefaultPosition.y + Player->Collision.y);
	};
};