#pragma once
#include "../../Other/VComponent.h"

class Killaura : public VModule {
public:
	Killaura() : VModule::VModule("Killaura", "Automatically attack nearby entities") {};
	void onGmTick();
private:
	float disRange = 10.0f;
};

#include "AntiBot.h"

void Killaura::onGmTick() {
	if (Minecraft::GetLocalPlayer() != nullptr) {
		GameMode* GM = Minecraft::GetGameMode();
		LocalPlayer* Player = Minecraft::GetLocalPlayer();
		std::vector<Actor*>* Entities = Minecraft::FetchPlayers();
		bool antiBot = ClientHandler::GetModule(AntiBot())->isEnabled;

		if (!Entities->empty()) {
			for (auto Entity : *Entities) {
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