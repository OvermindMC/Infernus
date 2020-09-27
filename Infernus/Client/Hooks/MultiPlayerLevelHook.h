#pragma once
#include "../../Other/VComponent.h"

class MultiPlayerLevelHook : public VHook {
public:
	void Init();
};

typedef void(__fastcall* _MultiPlayerLevelH)(MultiPlayerLevel* MultiPlayerLevel);
_MultiPlayerLevelH MultiPlayerLevelH;

std::vector<Actor*>* StoredEnts = new std::vector<Actor*>();

void MultiPlayerLevelCallback(MultiPlayerLevel* MultiPlayerLevel) {

	size_t listSize = MultiPlayerLevel->getListSize();
	StoredEnts->clear(); //Make sure it's empty before storing ents

	if (listSize < 5000 && listSize > 0) {
		for (size_t I = 0; I < listSize; I++) {
			Actor* CurrentEnt = MultiPlayerLevel->get(I);
			if (CurrentEnt != nullptr && CurrentEnt != Minecraft::GetLocalPlayer()->toActor()) StoredEnts->push_back(CurrentEnt);
		};
	};

	CachedPlayers = StoredEnts;
	MultiPlayerLevelH(MultiPlayerLevel);
};

void MultiPlayerLevelHook::Init() {
	uintptr_t signatureAddr = Utils::FindSignature("48 89 5C 24 ? 57 48 83 EC 20 48 8B F9 E8 ? ? ? ? FF 15 ? ? ? ? 48 8B D8 FF 15 ? ? ? ?");
	if (signatureAddr != NULL) {
		Utils::DebugFileLog("Found the address for the MultiPlayerLevel Tick Hook, Preparing now...");
		if (MH_CreateHook((void*)signatureAddr, &MultiPlayerLevelCallback, reinterpret_cast<LPVOID*>(&MultiPlayerLevelH)) == MH_OK) {
			Utils::DebugFileLog("Successfully created hook for MultiPlayerLevel Tick, Installing Hook...");
			MH_EnableHook((void*)signatureAddr);
		}
		else {
			Utils::DebugFileLog("Failed to create hook for MultiPlayerLevel Tick!");
		};
	}
	else {
		Utils::DebugFileLog("Failed to find address for the MultiPlayerLevel Tick Hook!");
	};
};