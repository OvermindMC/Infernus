#pragma once
#include "../../Other/VComponent.h"

class NoFall : public VModule {
public:
	NoFall() : VModule::VModule("NoFall", "Prevents Fall Damage") {};
	void onPacket(void*, PacketType, bool*);
};

void NoFall::onPacket(void* Packet, PacketType Type, bool* cancel) {
	if (Type == PacketType::ActorFallPacket) {
		*cancel = true;
	};
};