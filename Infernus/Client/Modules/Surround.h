#pragma once
#include "../../Other/VComponent.h"
#include "Scaffold.h"

class Surround : public VModule {
public:
	Surround() : VModule::VModule("Surround", "Surround players in blocks") {
		this->addWindowObj(new VWindowSlider(&range, 0.0f, 8.0, "Range: ", MC_Colour(255, 255, 255), 1.0f, 1.0f, MC_Colour(255, 110, 30), .7f));
	};
	void onGmTick();
	void handlePlacing(Actor*);
private:
	int delay = 0;
	float range = 6.0f;
};

void Surround::onGmTick() {
	if (delay >= 5) {
		if (Minecraft::GetLocalPlayer() != nullptr) {
			std::vector<Actor*>* Players = Minecraft::FetchPlayers();
			if (Players != nullptr && !Players->empty()) {
				for (auto Entity : *Players) {
					if (Utils::distanceVec3(*Entity->getPos(), *Minecraft::GetLocalPlayer()->getPos()) <= range) {
						handlePlacing(Entity);
					};
				};
			};
		};
		delay = 0;
	};
	delay++;
};

void Surround::handlePlacing(Actor* Entity) {
	Scaffold* ScaffoldMod = (Scaffold*)ClientHandler::GetModule(Scaffold());
	if (Entity != nullptr) {
		LocalPlayer* Player = Minecraft::GetLocalPlayer();
		GameMode* GM = Minecraft::GetGameMode();
		ItemStack* heldItem = Player->getSelectedItem();
		if (heldItem->StackCount && heldItem->Item != nullptr && (*heldItem->Item)->isBlock()) {
			std::vector<Vec3> blockPositions;
			Vec3 entPos = *Entity->getPos();
			entPos.y -= ((LocalPlayer*)Entity)->Collision.y;
			entPos.y -= 0.5f;

			if (blockPositions.empty()) {
				blockPositions.push_back(Vec3(entPos.x + 1, entPos.y, entPos.z));
				blockPositions.push_back(Vec3(entPos.x, entPos.y, entPos.z - 1));
				blockPositions.push_back(Vec3(entPos.x - 1, entPos.y, entPos.z));
				blockPositions.push_back(Vec3(entPos.x, entPos.y, entPos.z + 1));
			};

			int index = 0;

			for (auto blockPos : blockPositions) {
				index++;

				for (int y = entPos.y; y < entPos.y + 3.0f; y++) {
					ScaffoldMod->tryBuild(Vec3(blockPos.x, y, blockPos.z));
				};

				if (index == (int)(blockPositions.size())) {
					ScaffoldMod->tryBuild(Vec3(entPos.x, (entPos.y + 3.0f), entPos.z));
					index = 0;
				};
			};
		};
	};
};