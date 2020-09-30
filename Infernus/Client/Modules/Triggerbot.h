#pragma once
#include "../../Other/VComponent.h"

class Triggerbot : public VModule {
public:
	Triggerbot() : VModule::VModule("Triggerbot", "Automatically attack facing mobs") {};
	void onGmTick();
};

void Triggerbot::onGmTick() {
	LocalPlayer* Player = Minecraft::GetLocalPlayer();
	if (Player != nullptr) {
		Actor* facing = Player->MultiPlayerLevel->facingEnt;
		if (facing != nullptr) {
			Minecraft::GetGameMode()->attack(facing);
			Player->swing();
		};
	};
};