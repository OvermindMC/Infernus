#pragma once
#include "../../Other/VComponent.h"
#include "Scaffold.h"

class Surround : public VModule {
public:
	Surround() : VModule::VModule("Surround", "Surround players in blocks") {
		this->addWindowObj(new VWindowSlider(&range, 0.0f, 8.0, "Range: ", MC_Colour(255, 255, 255), 1.0f, 1.0f, MC_Colour(255, 110, 30), .7f));
	};
	void onEnable();
	void onGmTick();
	void attemptTask(Vec3);
private:
	int delay = 0;
	float range = 4.0f;
	Scaffold* ScaffoldMod;
};

void Surround::onEnable() {
	if (ScaffoldMod == nullptr) {
		ScaffoldMod = (Scaffold*)ClientHandler::GetModule(Scaffold());
	};
};

void Surround::onGmTick() {
	if (Minecraft::GetLocalPlayer() != nullptr) {
		std::vector<Actor*>* Players = Minecraft::FetchPlayers();
		ItemStack* heldItem = Minecraft::GetLocalPlayer()->getSelectedItem();
		if (Players != nullptr && !Players->empty() && (heldItem != nullptr && heldItem->Item != nullptr && (*heldItem->Item)->isBlock())) {
			std::vector<float> distances;
			for (auto Entity : *Players) {
				Vec3 entPos = *Entity->getPos();
				float distance = Utils::distanceVec3(entPos, *Minecraft::GetLocalPlayer()->getPos());
				if (distance <= range) {
					distances.push_back(distance);
				};
			};
			std::sort(distances.begin(), distances.end());
			if (!distances.empty()) {
				for (auto Entity : *Players) {
					Vec3 entPos = *Entity->getPos();
					if (Utils::distanceVec3(entPos, *Minecraft::GetLocalPlayer()->getPos()) == distances.at(0)) {
						attemptTask(Vec3(entPos.x, entPos.y - (((LocalPlayer*)Entity)->Collision.y + 0.5f), entPos.z));
						break;
					};
				};
			};
		};
	};
};

void Surround::attemptTask(Vec3 blockPos) {
	std::vector<Vec3> blockPositions;
	bool complete = false;
	if (blockPositions.empty()) {
		blockPositions.push_back(Vec3(blockPos.x + 1, blockPos.y, blockPos.z));
		blockPositions.push_back(Vec3(blockPos.x - 1, blockPos.y, blockPos.z));
		blockPositions.push_back(Vec3(blockPos.x, blockPos.y, blockPos.z + 1));
		blockPositions.push_back(Vec3(blockPos.x, blockPos.y, blockPos.z - 1));
	};
	int index = 0;
	for (auto BlockPos : blockPositions) {
		index++;
		for (int y = BlockPos.y; y < BlockPos.y + 3.0f; y++) {
			ScaffoldMod->tryBuild(Vec3(BlockPos.x, y, BlockPos.z));
		};

		if (index == (int)(blockPositions.size())) {
			ScaffoldMod->tryBuild(Vec3(blockPos.x, (blockPos.y + 3.0f), blockPos.z));
		};
	};
};