#pragma once
#include "../../Other/VComponent.h"

class Hitbox : public VModule {
public:
	Hitbox() : VModule::VModule("Hitbox", "Enlarge the collision size of entities") {};
	void onGmTick();
	void onDisable();
};

#include "AntiBot.h"

void Hitbox::onGmTick() {
	if (Minecraft::GetLocalPlayer() != nullptr) {
		LocalPlayer* Player = Minecraft::GetLocalPlayer();
		std::vector<Actor*>* Entities = Minecraft::FetchPlayers();
		bool antiBot = ClientHandler::GetModule(AntiBot())->isEnabled;

		for (auto Entity : *Entities) {
			if (antiBot) {
				if (Minecraft::GetClientInstance()->isValidTarget(Entity) && Entity->movedTick > 1) {
					Entity->setSize(2.0, 4.0);
				};
			}
			else {
				Entity->setSize(2.0, 4.0);
			};
		};
	};
};

void Hitbox::onDisable() {
	if (Minecraft::GetLocalPlayer() != nullptr) {
		LocalPlayer* Player = Minecraft::GetLocalPlayer();
		std::vector<Actor*>* Entities = Minecraft::FetchPlayers();

		for (auto Entity : *Entities) {
			Entity->setSize(0.6, 1.8);
		};
	};
};