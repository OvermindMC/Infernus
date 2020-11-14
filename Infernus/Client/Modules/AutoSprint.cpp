#include "AutoSprint.h"
#include "../../SDK/Minecraft.h"

void AutoSprint::onGmTick() {
	if (Minecraft::GetLocalPlayer() != nullptr) {
		LocalPlayer* Player = Minecraft::GetLocalPlayer();
		if (Player->Velocity.magnitudexz() > 0.05f) {
			Player->setSprinting(true);
		};
	};
};