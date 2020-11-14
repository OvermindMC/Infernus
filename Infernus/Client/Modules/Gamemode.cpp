#include "Gamemode.h"
#include "../../SDK/Minecraft.h"

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