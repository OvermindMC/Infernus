#pragma once
#include "../../Other/VComponent.h"

class AutoSprint : public VModule {
public:
	AutoSprint() : VModule::VModule("AutoSprint", "Automatically sprint forward") {};
	void onGmTick();
};

void AutoSprint::onGmTick() {
	if (Minecraft::GetLocalPlayer() != nullptr) {
		LocalPlayer* Player = Minecraft::GetLocalPlayer();
		if (Player->Velocity.magnitudexz() > 0.05f) {
			Player->setSprinting(true);
		};
	};
};