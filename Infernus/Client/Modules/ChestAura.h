#pragma once
#include "../../Other/VComponent.h"

class ChestAura : public VModule {
public:
	ChestAura() : VModule::VModule("ChestAura", "Automatically open nearby Chests") {
		this->addWindowObj(new VWindowSlider("Range: ", &range));
		this->addWindowObj(new VWindowButton("Trapped Chests", &trappedChests));
		this->addWindowObj(new VWindowButton("Ender Chests", &enderChests));
	};
	void onGmTick();
	bool alreadyFound(Vec3_i);
	void onDisable();
private:
	std::vector<Vec3_i> chestList = std::vector<Vec3_i>();
	std::chrono::time_point<std::chrono::steady_clock> savedTime = std::chrono::high_resolution_clock::now();
	float range = 3.0f;
	bool trappedChests = false;
	bool enderChests = true;
};

void ChestAura::onGmTick() {
	LocalPlayer* Player = Minecraft::GetLocalPlayer();
	GameMode* GM = Minecraft::GetGameMode();
	if (Player != nullptr && GM != nullptr) {
		if (std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::high_resolution_clock::now() - savedTime) >= std::chrono::milliseconds(400)) {
			Vec3 currPos = *Player->getPos();
			for (int x = -range; x < range; x++) {
				for (int y = -range; y < range; y++) {
					for (int z = -range; z < range; z++) {
						Vec3_i blockPos((int)(floorf(currPos.x) + x), (int)(floorf(currPos.y) + y), (int)(floorf(currPos.z) + z));
						if (!alreadyFound(blockPos) && Minecraft::GetClientInstance()->MinecraftGame->canUseKeys) {
							std::vector<int> idList = std::vector<int>();
							idList.push_back(54); //Chest
							if (trappedChests) {
								idList.push_back(146);
							};
							if (enderChests) {
								idList.push_back(130);
							};
							BlockLegacy* block = Player->BlockSource->getBlock(blockPos)->toLegacy();
							int ID = block->blockID;
							for (auto currID : idList) {
								if (ID == currID) {
									GM->buildBlock(&blockPos, 0);
									chestList.push_back(blockPos);
									x = range, y = range, z = range;
								};
							};
						};
					};
				};
			};
			savedTime = std::chrono::high_resolution_clock::now();
		};
	}
	else {
		if (!chestList.empty()) chestList.clear();
	}
};

bool ChestAura::alreadyFound(Vec3_i blockPos) {
	for (auto chest : chestList) {
		if (chest == blockPos) {
			return true;
		};
	};
	return false;
};

void ChestAura::onDisable() {
	if (!chestList.empty()) chestList.clear();
};