#pragma once
#include "../../Other/VComponent.h"

class Gamemode : public VModule {
public:
	Gamemode() : VModule::VModule("Gamemode", "Change your client sided gamemode") {
		VWindowSlider* newSlider = new VWindowSlider("Gamemode: ", &targetGamemode);
		newSlider->max = 2.f;
		this->addWindowObj(newSlider);
	};
	void onLoop();
	void onEnable();
	void onDisable();
	void onGmTick();	
private:
	bool modified = false;
	float targetGamemode = 1;
	int storedGamemode = 0;
};

void Gamemode::onLoop() {
	targetGamemode = roundf(targetGamemode);
	if (Minecraft::GetLocalPlayer() == nullptr) {
		storedGamemode = 0;
		modified = false;
		this->isEnabled = false;
	};
};

void Gamemode::onEnable() {
	LocalPlayer* Player = Minecraft::GetLocalPlayer();
	if (Player != nullptr) {
		storedGamemode = Player->toActor()->currentGameMode();
		modified = true;
	};
};

void Gamemode::onDisable() {
	LocalPlayer* Player = Minecraft::GetLocalPlayer();
	if (Player != nullptr && modified) {
		Player->setPlayerGameType(storedGamemode);
	};
	modified = false;
};

void Gamemode::onGmTick() {
	if (Minecraft::GetLocalPlayer() != nullptr) {
		Minecraft::GetLocalPlayer()->setPlayerGameType((int)(targetGamemode));
	};
};