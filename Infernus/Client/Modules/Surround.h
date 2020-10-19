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
	float range = 6.0f;
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
		if (Players != nullptr && !Players->empty()) {
			for (auto Entity : *Players) {
				Vec3 entPos = *Entity->getPos();
				if (Utils::distanceVec3(entPos, *Minecraft::GetLocalPlayer()->getPos()) <= range) {
					attemptTask(Vec3(entPos.x, entPos.y - ((LocalPlayer*)Entity)->Collision.y, entPos.z));
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
		for (int y = blockPos.y; y < blockPos.y + 3.0f; y++) {
			ScaffoldMod->tryBuild(Vec3(BlockPos.x, y, BlockPos.z));
		};

		if (index == (int)(blockPositions.size())) {
			ScaffoldMod->tryBuild(Vec3(blockPos.x, (blockPos.y + 3.0f), blockPos.z));
		};
	};
};