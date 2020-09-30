#pragma once
#include "../../Other/VComponent.h"

class Killaura : public VModule {
public:
	Killaura() : VModule::VModule("Killaura", "Automatically attack nearby entities") {};
	void onGmTick();
	void onEntityTick(std::vector<Actor*>*);
private:
	float disRange = 10.0f;
};

#include "AntiBot.h"

void Killaura::onGmTick() {
	if (Minecraft::GetLocalPlayer() != nullptr) {
		GameMode* GM = Minecraft::GetGameMode();
		LocalPlayer* Player = Minecraft::GetLocalPlayer();
		std::vector<Actor*>* Players = Minecraft::FetchPlayers();

		bool antiBot = ClientHandler::GetModule(AntiBot())->isEnabled;

		if (!Players->empty()) {
			for (auto Entity : *Players) {
				if (Utils::distanceVec3(*Entity->getPos(), *Player->getPos()) < disRange) {
					if (antiBot) {
						if (Minecraft::GetClientInstance()->isValidTarget(Entity) && Entity->movedTick > 1) {
							GM->attack(Entity);
							Player->swing();
						};
					}
					else {
						GM->attack(Entity);
						Player->swing();
					};
				};
			};
		};
	};
};

void Killaura::onEntityTick(std::vector<Actor*>* Entities) {
	if (isEnabled) {
		LocalPlayer* Player = Minecraft::GetLocalPlayer();
		for (auto Entity : *Entities) {
			if (Utils::distanceVec3(*Entity->getPos(), *Player->getPos()) < disRange) {
				Minecraft::GetGameMode()->attack(Entity);
				Player->swing();
			};
		};
	};
};