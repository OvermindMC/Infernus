#pragma once
#include "../../Other/VComponent.h"

class Freecam : public VModule {
public:
	Freecam() : VModule::VModule("Freecam", "Disable movement packets") {};
	void onPacket(void*, PacketType, bool*);
	void onGmTick();
	void onEnable();
	void onDisable();
private:
	Vec3 savedPos = Vec3();
	bool modified = false;
};