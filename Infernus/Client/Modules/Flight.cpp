#include "Flight.h"
#include "../../SDK/Minecraft.h"

void Flight::onGmTick() {
	LocalPlayer* Player = Minecraft::GetLocalPlayer();
	if (Player != nullptr) {
		Player->toActor()->setFlying(true);
		modified = true;
	};
};

void Flight::onDisable() {
	LocalPlayer* Player = Minecraft::GetLocalPlayer();
	if (Player != nullptr) {
		if (modified) {
			Player->toActor()->setFlying(false);
		};
		modified = false;
	};
};