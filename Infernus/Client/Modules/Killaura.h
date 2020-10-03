#pragma once
#include "../../Other/VComponent.h"
#include "AntiBot.h"

class Killaura : public VModule {
public:
	Killaura() : VModule::VModule("Killaura", "Automatically attack nearby entities") {
		this->addWindowObj(new VWindowButton("Multi Ents", &this->multiEnts));
		this->addWindowObj(new VWindowButton("Attack with UI open", &this->menuOpen));
		this->addWindowObj(new VWindowText("Range:"));
		this->addWindowObj(new VWindowSlider(&disRange));
	};
	void onGmTick();
	void onEntityTick(std::vector<Actor*>*);

	void attackPlayers();
	void attackMobs(std::vector<Actor*>*);
private:
	bool multiEnts = true;
	bool menuOpen = true;
	float disRange = 8.0f;
};

void Killaura::onGmTick() {
	if (Minecraft::GetLocalPlayer() != nullptr) {
		if (menuOpen) {
			attackPlayers();
		}
		else {
			if (Minecraft::GetClientInstance()->MinecraftGame->canUseKeys) attackPlayers();
		};
	};
};

void Killaura::onEntityTick(std::vector<Actor*>* Entities) {
	if (isEnabled && Minecraft::GetLocalPlayer() != nullptr) {
		if (menuOpen) {
			attackMobs(Entities);
		}
		else {
			if (Minecraft::GetClientInstance()->MinecraftGame->canUseKeys) attackMobs(Entities);
		};
	};
};

void Killaura::attackPlayers() {
	GameMode* GM = Minecraft::GetGameMode();
	LocalPlayer* Player = Minecraft::GetLocalPlayer();
	std::vector<Actor*>* Players = Minecraft::FetchPlayers();
	bool antiBot = ClientHandler::GetModule(AntiBot())->isEnabled;

	if (!Players->empty()) {
		if (multiEnts) {
			for (auto Entity : *Players) {
				if (Utils::distanceVec3(*Entity->getPos(), *Player->getPos()) <= disRange) {
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
		}
		else {
			std::vector<float> distances;

			for (auto Entity : *Players) {
				float distance = Utils::distanceVec3(*Entity->getPos(), *Player->getPos());
				if (antiBot) {
					if (Minecraft::GetClientInstance()->isValidTarget(Entity) && Entity->movedTick > 1 && distance <= disRange) {
						distances.push_back(distance);
					};
				}
				else {
					if (distance <= disRange) {
						distances.push_back(distance);
					};
				};
			};

			std::sort(distances.begin(), distances.end());

			if (multiEnts) {
				for (auto Entity : *Players) {
					float distance = Utils::distanceVec3(*Entity->getPos(), *Player->getPos());
					if (distance == distances[0]) {
						Minecraft::GetGameMode()->attack(Entity);
						Player->swing();
						break;
					};
				};
			};
		};
	};
};

void Killaura::attackMobs(std::vector<Actor*>* Entities) {
	LocalPlayer* Player = Minecraft::GetLocalPlayer();
	if (multiEnts) {
		for (auto Entity : *Entities) {
			if (Utils::distanceVec3(*Entity->getPos(), *Player->getPos()) <= disRange) {
				Minecraft::GetGameMode()->attack(Entity);
				Player->swing();
			};
		};
	}
	else {
		std::vector<float> distances;

		for (auto Entity : *Entities) {
			float distance = Utils::distanceVec3(*Entity->getPos(), *Player->getPos());
			if (distance <= disRange) {
				distances.push_back(distance);
			};
		};

		std::sort(distances.begin(), distances.end());

		for (auto Entity : *Entities) {
			float distance = Utils::distanceVec3(*Entity->getPos(), *Player->getPos());
			if (distance == distances[0]) {
				Minecraft::GetGameMode()->attack(Entity);
				Player->swing();
				break;
			};
		};
	};
};