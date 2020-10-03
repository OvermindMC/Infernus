#pragma once
#include "../../Other/VComponent.h"

class Hitbox : public VModule {
public:
	Hitbox() : VModule::VModule("Hitbox", "Enlarge the collision size of entities") {
		this->addWindowObj(new VWindowText("Width:"));
		this->addWindowObj(new VWindowSlider(&this->width));
		this->addWindowObj(new VWindowText("Height:"));
		this->addWindowObj(new VWindowSlider(&this->height));
	};
	void onGmTick();
	void onEnable() { revertMobs = true; };
	void onDisable();
	void onEntityTick(std::vector<Actor*>*);

	bool revertMobs = false;
	float width = 2.0f, height = 4.0f;
};

#include "AntiBot.h"

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