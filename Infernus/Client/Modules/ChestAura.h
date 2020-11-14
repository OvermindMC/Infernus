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