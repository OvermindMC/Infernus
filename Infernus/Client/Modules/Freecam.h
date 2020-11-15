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

void Freecam::onPacket(void* Packet, PacketType type, bool* cancel) {
	if (type == PacketType::MovePlayerPacket || type == PacketType::PlayerAuthInput) {
		*cancel = true;
	};
};

void Freecam::onGmTick() {
	if (Minecraft::GetLocalPlayer() == nullptr) {
		savedPos = Vec3();
		modified = false, isEnabled = false;
	};
};

void Freecam::onEnable() {
	LocalPlayer* Player = Minecraft::GetLocalPlayer();
	if (Player != nullptr) {
		savedPos = *Player->getPos();
		modified = true;
	};
};

void Freecam::onDisable() {
	LocalPlayer* Player = Minecraft::GetLocalPlayer();
	if (Player != nullptr) {
		if (modified) {
			Player->setPos(&savedPos);
		};
		modified = false;
	};
};