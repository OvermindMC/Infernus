#pragma once
#include "../../Other/VComponent.h"

class Instabreak : public VModule {
public:
	Instabreak() : VModule::VModule("Instabreak", "Break blocks instantly") {};
	void onDestroyBlock(GameMode*, Vec3_i*, uint8_t);
};