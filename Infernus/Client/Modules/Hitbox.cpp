#include "Hitbox.h"
#include "AntiBot.h"
#include "../ClientHandler.h"
#include "../../SDK/Minecraft.h"

void Hitbox::onGmTick() {
	if (Minecraft::GetLocalPlayer() != nullptr) {
		LocalPlayer* Player = Minecraft::GetLocalPlayer();
		std::vector<Actor*>* Players = Minecraft::FetchPlayers();
		bool antiBot = ClientHandler::GetModule(AntiBot())->isEnabled;

		for (auto Entity : *Players) {
			if (antiBot) {
				if (Minecraft::GetClientInstance()->isValidTarget(Entity) && Entity->movedTick > 1) {
					Entity->setSize(width, height);
				};
			}
			else {
				Entity->setSize(width, height);
			};
		};
	};
};

void Hitbox::onDisable() {
	if (Minecraft::GetLocalPlayer() != nullptr) {
		LocalPlayer* Player = Minecraft::GetLocalPlayer();
		std::vector<Actor*>* Players = Minecraft::FetchPlayers();

		for (auto Entity : *Players) {
			Entity->setSize(0.6, 1.8);
		};
	};
};

void Hitbox::onEntityTick(std::vector<Actor*>* Entities) {
	if (isEnabled) {
		for (auto Entity : *Entities) {
			Entity->setSize(width, height);
		};
	}
	else {
		if (revertMobs) {
			for (auto Entity : *Entities) {
				Entity->setSize(0.6, 1.8);
			};
			revertMobs = false;
		};
	};
};