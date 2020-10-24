#pragma once
#include "../../Other/VComponent.h"
#include "Scaffold.h"

class Surround : public VModule {
public:
	Surround() : VModule::VModule("Surround", "Surround players in blocks") {
		this->addWindowObj(new VWindowSlider(&range, 0.0f, 8.0, "Range: ", MC_Colour(255, 255, 255), 1.0f, 1.0f, MC_Colour(255, 110, 30), .7f));
		this->addWindowObj(new VWindowSlider(&boxSize, 0.0f, 4.0, "Box Size: ", MC_Colour(255, 255, 255), 1.0f, 1.0f, MC_Colour(255, 110, 30), .7f));
	};
	void onEnable();
	void onGmTick();
	void attemptTask(Vec3, float);
	void surroundPlace(std::vector<Vec3>);
private:
	int delay = 0;
	float range = 4.0f;
	float boxSize = 2.0f;
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
						attemptTask(Vec3(*Entity->getPos()), boxSize); //entPos.x, entPos.y - (((LocalPlayer*)Entity)->Collision.y + 0.5f), entPos.z), boxSize
						break;
					};
				};
			};
		};
	};
};

void Surround::attemptTask(Vec3 blockPos, float boxSize) {
	std::vector<Vec3> blockPositions;
	bool complete = false;
	if (blockPositions.empty()) {
		blockPositions.push_back(blockPos); //Block under - Entity digging down?
		
		for (int x = -boxSize; x <= boxSize; x++) {
			for (int y = -boxSize; y < boxSize; y++) {
				for (int z = -boxSize; z <= boxSize; z++) {
					blockPositions.push_back(Vec3(blockPos.x + x, blockPos.y + y, blockPos.z + z));
				};
			};
		};
	};

	for (auto BlockPos : blockPositions) {
		ScaffoldMod->tryBuild(BlockPos);
	};
};

void Surround::surroundPlace(std::vector<Vec3> blockPositions) {
	for (auto BlockPos : blockPositions) {
		ScaffoldMod->tryBuild(BlockPos);
	};
};