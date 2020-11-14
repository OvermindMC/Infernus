#pragma once
#include "../../Other/VComponent.h"

class TestModule : public VModule {
public:
	TestModule() : VModule::VModule("Test Module", "For testing purposes") {};
	void onPacket(void*, PacketType, bool*);
private:
	int MovePacketsID;
	int PlayerAuthPacketsID;
	int ActorFallPacketsID;
	int MobEquipmentPacketsID;
	int TextPacketsID;

	int UnknownPacketsID;
};