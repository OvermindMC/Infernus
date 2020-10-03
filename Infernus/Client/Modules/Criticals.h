#pragma once
#include "../../Other/VComponent.h"

class Criticals : public VModule {
public:
	Criticals() : VModule::VModule("Criticals", "Each hit is a critical hit") {};
	void onPacket(void*, PacketType, bool*);
};

void Criticals::onPacket(void* Packet, PacketType Type, bool* cancel) {
	if (Type == PacketType::MovePlayerPacket) {
		MovePlayerPacket* current = (MovePlayerPacket*)Packet;
		current->onGround = false;
	};
};