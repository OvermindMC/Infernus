#pragma once
#include "../../Other/VComponent.h"
#include "../Modules/Xray.h"

class BlockHooks : public VHook {
public:
	void Init();
};

typedef __int8* (__thiscall* _LightEmission)(BlockLegacy*, __int8*);
_LightEmission LightEmission;

typedef int(__fastcall* _RenderLayer)(BlockLegacy*);
_RenderLayer RenderLayer;

__int8* LightEmissionCallback(BlockLegacy* a1, __int8* a2) {
	Xray* XrayMod = (Xray*)ClientHandler::GetModule(Xray());
	if (XrayMod->isEnabled) {
		*a2 = 15;
		return a2;
	};
	return LightEmission(a1, a2);
};

int RenderLayerCallback(BlockLegacy* a1) {
	Xray* XrayMod = (Xray*)ClientHandler::GetModule(Xray());
	if (XrayMod->isEnabled) {
		int currID = a1->blockID;
		bool found = false;
		for (auto ID : XrayMod->ores) {
			if (currID == ID) found = true;
		};
		if (found) {
			return RenderLayer(a1);
		}
		else {
			return 10; //Transparency;
		};
	}
	else {
		return RenderLayer(a1);
	};
};

void BlockHooks::Init() {
	uintptr_t blockLegacyAddr = Utils::FindSignature("48 8D 05 ? ? ? ? 48 89 01 4C 39 7A 10 75 1A 48 C7 45 ? ? ? ? ?");
	int offset = *reinterpret_cast<int*>(blockLegacyAddr + 3);
	uintptr_t** VTable = reinterpret_cast<uintptr_t**>(blockLegacyAddr + offset + 7);
	if (blockLegacyAddr != NULL || VTable != nullptr) {
		Utils::DebugFileLog("Preparing BlockLegacy Hooks...");

		void* lightEmissionAddr = (void*)VTable[16];
		if (MH_CreateHook(lightEmissionAddr, &LightEmissionCallback, reinterpret_cast<LPVOID*>(&LightEmission)) == MH_OK) {
			Utils::DebugFileLog("Successfully created hook for BlockLegacy LightEmission, Enabling hook now...");
			MH_EnableHook(lightEmissionAddr);
		}
		else {
			Utils::DebugFileLog("Failed to create hook for BlockLegacy LightEmission");
		};

		void* renderLayerAddr = (void*)VTable[125];
		if (MH_CreateHook(renderLayerAddr, RenderLayerCallback, reinterpret_cast<LPVOID*>(&RenderLayer)) == MH_OK) {
			Utils::DebugFileLog("Successfully created hook for BlockLegacy RenderLayer, Enabling hook now...");
			MH_EnableHook(renderLayerAddr);
		}
		else {
			Utils::DebugFileLog("Failed to create hook for BlockLegacy RenderLayer");
		};
	}
	else {
		Utils::FindSignature("Unable to find address needed for Block Legacy hooks!");
	};
};