#include "Xray.h"
#include "../../SDK/Minecraft.h"

void Xray::onEnable() {
	LocalPlayer* Player = Minecraft::GetLocalPlayer();
	if (Player != nullptr && !refreshed) {
		refreshChunks(Player->getPos());
		refreshed = true;
	};
};

void Xray::onDisable() {
	LocalPlayer* Player = Minecraft::GetLocalPlayer();
	if (refreshed) {
		if (Player != nullptr) {
			refreshChunks(Player->getPos());
		};
		refreshed = false;
	};
};

bool Xray::holdingToolOrBlock() {
	LocalPlayer* Player = Minecraft::GetLocalPlayer();
	if (Player != nullptr) {
		ItemStack* heldItem = Player->getSelectedItem();
		if (heldItem != nullptr && heldItem->Item != nullptr) {
			Item* item = *heldItem->Item;
			if (item->itemID > 0) {
				if (item->isBlock() || item->isTool()) {
					return true;
				}
				else {
					return false;
				};
			}
			else {
				return false;
			};
		}
		else {
			return false;
		};
	}
	else {
		return false;
	};
};

void Xray::refreshChunks(Vec3* targetPos) {
	LocalPlayer* Player = Minecraft::GetLocalPlayer();
	GameMode* GM = Minecraft::GetGameMode();
	float range = 30;
	int count = 0;
	if (Player != nullptr && GM != nullptr) {
		for (int x = -range; x < range; x++) {
			for (int y = -range; y < range; y++) {
				for (int z = -range; z < range; z++) {
					Vec3_i blockPos = Vec3_i(targetPos->x + x, targetPos->y + y, targetPos->z + z);
					Block* block = Player->BlockSource->getBlock(blockPos);
					float distance = Utils::distanceVec3_i(blockPos, Vec3_i(*targetPos));
					if (block->toLegacy()->blockID > 0 && distance >= 12) {
						Block* blockAbove = Player->BlockSource->getBlock(Vec3_i(blockPos.x, blockPos.y + 1, blockPos.z));
						if (blockAbove->toLegacy()->blockID == 0) { //Refresh ground & caves
							if (count >= 5) {
								if (!holdingToolOrBlock()) {
									GM->destroyBlock(&blockPos, 0);
								}
								else {
									Player->displayTextObjectMessage(&TextHolder("Unable to refresh Chunks! Make sure you're holding nothing in your hand (Or at least not a tool/block)!"));
									x = range, y = range, z = range;
								};
								count = 0;
							};
							count++;
						};
					};
				};
			};
		};
		Player->displayTextObjectMessage(&TextHolder("Refreshed Chunks!"));
	};
};