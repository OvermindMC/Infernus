#pragma once
#include "../../Other/VComponent.h"

class DeathBack : public VModule {
public:
	DeathBack() : VModule::VModule("DeathBack", "Respawn at your death position when respawning") {};
	void onGmTick();
private:
	bool dead = false;
	Vec3 storedPos;
};