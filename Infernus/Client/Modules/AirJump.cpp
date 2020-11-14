#pragma once
#include "AirJump.h"
#include "../../SDK/Minecraft.h"

void AirJump::onGmTick() {
	if (Minecraft::GetLocalPlayer() != nullptr) {
		if (Utils::usingKey(0x20)) Minecraft::GetLocalPlayer()->onGround = true;
	};
};