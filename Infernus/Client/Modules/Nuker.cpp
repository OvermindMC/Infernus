#include "Nuker.h"
#include "../../SDK/Minecraft.h"

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