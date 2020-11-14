#pragma once
#include "../../Other/VComponent.h"

class Nuker : public VModule {
public:
	Nuker() : VModule::VModule("Nuker", "Destroy large amount of blocks simultaneously") {
		this->addWindowObj(new VWindowButton("Vein-Miner", &this->veinMiner));
		this->addWindowObj(new VWindowSlider("Range: ", &this->radius));
	};
	void onLoop() { radius = roundf(radius); nukerRadius = (int)radius; };
	void onDestroyBlock(GameMode*, Vec3_i*, uint8_t);
public:
	float radius = 3.0f;
	int nukerRadius;
	bool veinMiner = false;
};