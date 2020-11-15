#pragma once
#include "../../Other/VComponent.h"

class Instabreak : public VModule {
public:
	Instabreak() : VModule::VModule("Instabreak", "Break blocks instantly") {};
	void onDestroyBlock(GameMode*, Vec3_i*, uint8_t);
};

void Instabreak::onDestroyBlock(GameMode* GM, Vec3_i* blockPos, uint8_t face) {
	GM->destroyBlock(blockPos, face);
};