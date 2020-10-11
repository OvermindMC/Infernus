#pragma once
#include "../../Other/VComponent.h"

class Nuker : public VModule {
public:
	Nuker() : VModule::VModule("Nuker", "Destroy large amount of blocks simultaneously") {
		this->addWindowObj(new VWindowButton("Vein-Miner", &this->veinMiner));
		this->addWindowObj(new VWindowSlider(&this->radius, 0.0f, 10.0f, "Range: ", MC_Colour(255, 255, 255), 1.0f, 1.0f, MC_Colour(255, 110, 30), .7f));
	};
	void onLoop() { radius = roundf(radius); nukerRadius = (int)radius; };
	void onDestroyBlock(GameMode*, Vec3_i*, uint8_t);
public:
	float radius = 3.0f;
	int nukerRadius;
	bool veinMiner = false;
};

bool isOre(int ID) {
	std::vector<int> idFilter = { 14, 15, 16, 56, 73, 74, 153 };

	for (auto curr : idFilter) {
		if (ID == curr) return true;
	};
	return false;
};

void Nuker::onDestroyBlock(GameMode* GM, Vec3_i* blockPos, uint8_t face) {
	BlockSource* blockSource = Minecraft::GetLocalPlayer()->BlockSource;
	for (int rangeX = -nukerRadius; rangeX < nukerRadius; rangeX++) {
		for (int rangeY = -nukerRadius; rangeY < nukerRadius; rangeY++) {
			for (int rangeZ = -nukerRadius; rangeZ < nukerRadius; rangeZ++) {
				Vec3_i blockPosition;
				blockPosition.x = blockPos->x + rangeX;
				blockPosition.y = blockPos->y + rangeY;
				blockPosition.z = blockPos->z + rangeZ;
				if (veinMiner) {
					if (!isOre(blockSource->getBlock(blockPosition)->toLegacy()->blockID)) GM->destroyBlock(&blockPosition, face);
				}
				else {
					GM->destroyBlock(&blockPosition, face);
				};
			};
		};
	};
}