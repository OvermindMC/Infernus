#pragma once
#include "../../Other/VComponent.h"

class NoPacket : public VModule {
public:
	NoPacket() : VModule::VModule("NoPacket", "Disable packets being sent to the Server from the Client") {};
	void onPacket(void*, PacketType, bool*);
};

void NoPacket::onPacket(void* Packet, PacketType type, bool* cancel) {
	*cancel = true;
};