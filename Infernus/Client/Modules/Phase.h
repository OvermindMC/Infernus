#pragma once
#include "../../Other/VComponent.h"

class Phase : public VModule {
public:
	Phase() : VModule::VModule("Phase", "Walk through walls") {};
	void onGmTick();
	void onDisable();
};

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