#pragma once
#include "../../Other/VComponent.h"

class Xray : public VModule {
public:
	Xray() : VModule::VModule("Xray", "See ores through solid blocks", 0x58) {};
	void onEnable();
	void onDisable();
	bool holdingToolOrBlock();
	void refreshChunks(Vec3*);
	std::vector<int> ores = { 129/*Emerald*/, 73/*Redstone*/, 56/*Diamond*/, 21/*Lapis*/, 16/*Coal*/, 15/*Iron*/, 14/*Gold*/, };
private:
	bool refreshed = false;
};