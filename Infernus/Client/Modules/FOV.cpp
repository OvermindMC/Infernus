#include "FOV.h"
#include "../../SDK/Minecraft.h"

void FOV::onGmTick() {
	LocalPlayer* Player = Minecraft::GetLocalPlayer();
	if (Player != nullptr) {
		Player->setFieldOfViewModifier(modifier);
		modified = true;
	};
};

void FOV::onDisable() {
	LocalPlayer* Player = Minecraft::GetLocalPlayer();
	if (Player != nullptr) {
		if (modified) {
			Player->setFieldOfViewModifier(1.0f);
			modified = false;
		};
	};
};