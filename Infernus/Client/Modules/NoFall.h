#pragma once
#include "../../Other/VComponent.h"

class NoFall : public VModule {
public:
	NoFall() : VModule::VModule("NoFall", "Prevents Fall Damage") {};
	void onPacket(void*, PacketType, bool*);
};