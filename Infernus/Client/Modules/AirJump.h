#pragma once

class AirJump : public VModule {
public:
	AirJump() : VModule::VModule("AirJump", "Tells the game that you're on the ground") {};
	void onTick();
};

#include "Jetpack.h"

void AirJump::onTick() {
	if (Minecraft::GetLocalPlayer() != nullptr) {
		if (Utils::usingKey(0x20)) Minecraft::GetLocalPlayer()->onGround = true;
	};
};