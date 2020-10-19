#pragma once
#include "../../Other/VComponent.h"

class Flight : public VModule {
public:
	Flight() : VModule::VModule("Flight", "Fly even in Survival Mode") {};
	void onGmTick();
	void onDisable();
};

void Flight::onGmTick() {
	LocalPlayer* Player = Minecraft::GetLocalPlayer();
	if (Player != nullptr) {
		Player->toActor()->setFlying(true);
	};
};

void Flight::onDisable() {
	LocalPlayer* Player = Minecraft::GetLocalPlayer();
	if (Player != nullptr) {
		Player->toActor()->setFlying(false);
	};
};