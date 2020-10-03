#pragma once
#include "../../Other/VComponent.h"

class NetworkHook : public VHook {
public:
	void Init();
};

typedef void(__fastcall* _SendToServer)(LoopbackPacketSender*, void*);
_SendToServer SendToServer;

void SendToServerCallback(LoopbackPacketSender* a1, void* Packet) {
	bool cancel = false;
	PacketType Type = PacketType::Unknown;

	uint64_t currPacketAddr = *(UINT64*)Packet;

	if (currPacketAddr == (UINT64)Packet::GetAuthVTable()) {
		Type = PacketType::PlayerAuthInput;
	}
	else if (currPacketAddr == (UINT64)Packet::GetMoveVTable()) {
		Type = PacketType::MovePlayerPacket;
	}
	else if (currPacketAddr == (UINT64)Packet::GetTextVTable()) {
		Type = PacketType::TextPacket;
	}
	else if (currPacketAddr == (UINT64)Packet::GetActorFallVTable()) {
		Type = PacketType::ActorFallPacket;
	}
	else if (currPacketAddr == (UINT64)Packet::GetMobEquipmentVTable()) {
		Type = PacketType::MobEquipmentPacket;
	};

	for (auto Module : ClientHandler::GetModules()) {
		if (Module->isEnabled) Module->onPacket(Packet, Type, &cancel);
	};

	if (!cancel) SendToServer(a1, Packet);
};

void NetworkHook::Init() {
	Utils::DebugFileLog("Preparing Network Hook...");

	uintptr_t SendServerAddr = Utils::FindSignature("48 89 5C 24 ? 57 48 81 EC ? ? ? ? 0F B6 41 08 48 8B FA 88 42 10 48 8D 54 24 ? 48 8B 59 10 48 8B CB E8 ? ? ? ? 45 33 C9 4C 8B C7 48 8B D0 48 8B CB E8 ? ? ? ? 48 8B 9C 24 ? ? ? ? 48 81 C4 ? ? ? ? 5F C3");

	if (MH_CreateHook((void*)SendServerAddr, &SendToServerCallback, reinterpret_cast<LPVOID*>(&SendToServer)) == MH_OK) {
		Utils::DebugFileLog("Successfully created hook for SendToServer Function!");
		MH_EnableHook((void*)SendServerAddr);
	}
	else {
		Utils::DebugFileLog("Failed to create hook for SendToServer Function!");
	};
};