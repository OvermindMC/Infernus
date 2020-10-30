#pragma once
#include "../../Other/VComponent.h"

class TorchBreaker : public VModule {
public:
	TorchBreaker() : VModule::VModule("TorchBreaker", "Break nearby torches automatically") {
		this->addWindowObj(new VWindowSlider(&range, 0.0f, 8.0, "Range: ", MC_Colour(255, 255, 255), 1.0f, 1.0f, MC_Colour(255, 110, 30), .7f));
	};
	void onGmTick();
private:
	float range = 7;
	std::chrono::time_point<std::chrono::steady_clock> savedTime = std::chrono::high_resolution_clock::now();
};

void TorchBreaker::onGmTick() {
	LocalPlayer* Player = Minecraft::GetLocalPlayer();
	GameMode* GM = Minecraft::GetGameMode();
	if (Player != nullptr && GM != nullptr && std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::high_resolution_clock::now() - savedTime) >= std::chrono::milliseconds(100)) {
		Vec3 currPos = *Player->getPos();
		for (int x = -range; x < range; x++) {
			for (int y = -range; y < range; y++) {
				for (int z = -range; z < range; z++) {
					Vec3 blockPos = Vec3(currPos.x + x, currPos.y + y, currPos.z + z);
					Block* block = Player->BlockSource->getBlock(blockPos);
					if (block->toLegacy()->blockID == 50) {
						GM->destroyBlock(&Vec3_i(blockPos), 0);
						x = range, y = range, z = range; //Stop loop
					};
				};
			};
		};
		savedTime = std::chrono::high_resolution_clock::now();
	};
};