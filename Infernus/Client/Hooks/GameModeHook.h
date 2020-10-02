#pragma once
#include "../../Other/VComponent.h"

class GameModeHook : public VHook {
public:
	void Init();
};

typedef void(__fastcall* GameMode_Tick)(GameMode* GM);
GameMode_Tick GMTick;
GameMode_Tick SMTick;

void GMTickCallback(GameMode* GM) {
	if (Minecraft::GetLocalPlayer() != nullptr && GM->Player == Minecraft::GetLocalPlayer()) {
		CachedGameMode = GM;
		for (auto Module : ClientHandler::GetModules()) {
			if (Module->isEnabled) Module->onGmTick();
		};
	};
	GMTick(GM);
};

void SMTickCallback(GameMode* GM) {
	if (Minecraft::GetLocalPlayer() != nullptr && GM->Player == Minecraft::GetLocalPlayer()) {
		CachedGameMode = GM;
		for (auto Module : ClientHandler::GetModules()) {
			if (Module->isEnabled) Module->onGmTick();
		};
	};
	SMTick(GM);
};

typedef void(__fastcall* _StartDestroyBlock)(GameMode*, Vec3_i*, uint8_t, void*, void*);
_StartDestroyBlock StartDestroyBlock;

void StartDestroyBlockCallback(GameMode* GM, Vec3_i* blockPos, uint8_t face, void* a4, void* a5) {
	for (auto Module : ClientHandler::GetModules()) {
		if (Module->isEnabled) Module->onDestroyBlock(GM, blockPos, face);
	};
	StartDestroyBlock(GM, blockPos, face, a4, a5);
};

void GameModeHook::Init() {

	/* GameMode */
	{
		uintptr_t GameModeAddr = Utils::FindSignature("48 8D 05 ? ? ? ? 48 89 01 33 D2 48 C7 41 ? ? ? ? ? C7 41 ? ? ? ? ? 48 89 51 1C 48 89 51 28 89 51 30 F2 0F 10 05 ? ? ? ? F2 0F 11 41 ? 8B 05 ? ? ? ? 89 41 3C");
		int offset = *reinterpret_cast<int*>(GameModeAddr + 3);
		uintptr_t** GameModeVTable = reinterpret_cast<uintptr_t**>(GameModeAddr + offset + 7);

		if (GameModeAddr != NULL) {
			Utils::DebugFileLog("Preparing GameMode Hooks...");

			void* GameModeTick = GameModeVTable[9];
			if (MH_CreateHook(GameModeTick, &GMTickCallback, reinterpret_cast<LPVOID*>(&GMTick)) == MH_OK) {
				Utils::DebugFileLog("Successfully created GameMode Tick Hook, Enabling Hook...");
				MH_EnableHook(GameModeTick);
			}
			else {
				Utils::DebugFileLog("Failed to create GameMode Tick Hook!");
			};

			void* startDestroyBlockAddr = GameModeVTable[1];
			if (MH_CreateHook(startDestroyBlockAddr, &StartDestroyBlockCallback, reinterpret_cast<LPVOID*>(&StartDestroyBlock)) == MH_OK) {
				Utils::DebugFileLog("Successfully created StartDestroyBlock Hook, Enabling Hook...");
				MH_EnableHook(startDestroyBlockAddr);
			}
			else {
				Utils::DebugFileLog("Failed to create hook for StartDestroyBlock");
			};
		}
		else {
			Utils::DebugFileLog("Failed to find GameMode VTable Address!");
		};
	}

	/* SurvivalMode */
	{
		uintptr_t SurvivalModeAddr = Utils::FindSignature("4C 8D 05 ? ? ? ? 4C 89 01 66 44 89 B9 ? ? ? ? 44 89 B9 ? ? ? ? 4C 89 B9 ? ? ? ? 4C 8B 87 ? ? ? ? 48 89 8F ? ? ? ?");
		int offset = *reinterpret_cast<int*>(SurvivalModeAddr + 3);
		uintptr_t** SurvivalModeVTable = reinterpret_cast<uintptr_t**>(SurvivalModeAddr + offset + 7);

		if (SurvivalModeAddr != NULL) {
			Utils::DebugFileLog("Preparing SurvivalMode Hooks...");

			void* SurvivalTick = SurvivalModeVTable[9];
			if (MH_CreateHook(SurvivalTick, &SMTickCallback, reinterpret_cast<LPVOID*>(&SMTick)) == MH_OK) {
				Utils::DebugFileLog("Successfully created SurvivalMode Tick Hook, Enabling Hook...");
				MH_EnableHook(SurvivalTick);
			}
			else {
				Utils::DebugFileLog("Failed to create SurvivalMode Tick Hook!");
			};
		}
		else {
			Utils::DebugFileLog("Failed to find SurvivalMode VTable Address!");
		};
	}
};