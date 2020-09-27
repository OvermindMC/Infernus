#pragma once
#include "../../Other/VComponent.h"

class ClientInstanceHook : public VHook {
public:
	void Init();
};

typedef void(__fastcall* _ClientInstanceHook)(ClientInstance* ClientInstanceAddr, void* a2);
_ClientInstanceHook ClientInstanceH;

void ClientInstanceCallback(ClientInstance* ClientInstanceAddr, void* a2) {
	CachedClientInstance = ClientInstanceAddr;
	ClientInstanceH(ClientInstanceAddr, a2);
};

void ClientInstanceHook::Init() {
	Utils::DebugFileLog("Preparing ClientInstance Hook!");

	uintptr_t ClientInstanceHookAddr = Utils::FindSignature("40 57 48 83 EC 30 48 C7 44 24 ? ? ? ? ? 48 89 5C 24 ? 48 89 74 24 ? 48 8B FA 48 8B F1 48 8B 01 48 8D 54 24");

	if (MH_CreateHook((void*)ClientInstanceHookAddr, &ClientInstanceCallback, reinterpret_cast<LPVOID*>(&ClientInstanceH)) == MH_OK) {
		Utils::DebugFileLog("Successfully created ClientInstance Hook, Installing Hook...");
		MH_EnableHook((void*)ClientInstanceHookAddr);
	}
	else {
		Utils::DebugFileLog("Failed to create ClientInstance Hook!");
	};
};