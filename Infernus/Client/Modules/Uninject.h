#pragma once
#include "../../Other/VComponent.h"

class Uninject : public VModule {
public:
	Uninject() : VModule::VModule("Uninject", "Removes the Client from the Game") {};
	void onEnable() {
		MH_DisableHook(MH_ALL_HOOKS);
		for (auto Module : ClientHandler::GetModules()) Module->onDisable();
		Sleep(20);
		MH_Uninitialize();
		FreeLibraryAndExitThread(Utils::hModule, 1);
	};
};