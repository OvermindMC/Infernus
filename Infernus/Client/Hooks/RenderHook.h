#pragma once
#include "../../Other/VComponent.h"
#include "../../Other/RenderUtils.h"

class RenderHook : public VHook {
public:
	void Init();
};

typedef void(__stdcall* _RenderUIContext)(__int64 a1, MinecraftUIRenderContext* Context);
_RenderUIContext RenderUIContext;

void RenderCallback(__int64 a1, MinecraftUIRenderContext* Context) {
	if (CachedClientInstance != nullptr) {
		RenderUtils::SetCtx(Context);
		for (auto Module : ClientHandler::GetModules()) {
			if (Module->isEnabled) Module->onRender();
		};
	};
	RenderUIContext(a1, Context);
};

void RenderHook::Init() {
	Utils::DebugFileLog("Preparing Render Hook!");
	
	uintptr_t RenderHookAddr = Utils::FindSignature("48 8B C4 55 56 57 41 54 41 55 41 56 41 57 48 8D A8 ? ? ? ? 48 81 EC ? ? ? ? 48 C7 45 ? ? ? ? ? 48 89 58 18 0F 29 70 B8 48 8B 05 ? ? ? ? 48 33 C4 48 89 85 ? ? ? ? 48 89 54 24 ? 4C 8B E1 48 89 4C 24 ?");

	if (MH_CreateHook((void*)RenderHookAddr, &RenderCallback, reinterpret_cast<LPVOID*>(&RenderUIContext)) == MH_OK) {
		Utils::DebugFileLog("Successfully created Render Hook, Installing Hook...");
		MH_EnableHook((void*)RenderHookAddr);
	}
	else {
		Utils::DebugFileLog("Failed to create Render Hook!");
	};
};