#pragma once
#include "../../Other/VComponent.h"

class Gamemode : public VModule {
public:
	Gamemode() : VModule::VModule("Gamemode", "Change your client-sided Gamemode") {
		this->addWindowObj(new VWindowSlider(&targetGamemodeF, 0.0f, 2.0f, "Gamemode: "));
	};
	void onLoop();
	void onEnable();
	void onGmTick();
	void onDisable();
private:
	int savedGamemode;
	int targetGamemode;
	float targetGamemodeF = 1.0;
};

void Gamemode::onLoop() {
	targetGamemodeF = roundf(targetGamemodeF);
	targetGamemode = (int)targetGamemodeF;
};

void Gamemode::onEnable() {
	if (Minecraft::GetLocalPlayer() != nullptr) {
		savedGamemode = Minecraft::GetLocalPlayer()->toActor()->currentGameMode();
	};
};

void Gamemode::onGmTick() {
	if (Minecraft::GetLocalPlayer() != nullptr) {
		Minecraft::GetLocalPlayer()->setPlayerGameType(targetGamemode);
	};
};

void Gamemode::onDisable() {
	if (Minecraft::GetLocalPlayer() != nullptr) {
		Minecraft::GetLocalPlayer()->setPlayerGameType(savedGamemode);
	};
};