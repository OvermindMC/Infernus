#include "Uninject.h"
#include "../ClientHandler.h"

void Uninject::onEnable() {
	MH_DisableHook(MH_ALL_HOOKS);
	for (auto Module : ClientHandler::GetModules()) Module->onDisable();
	Sleep(20);
	MH_Uninitialize();
	FreeLibraryAndExitThread(Utils::hModule, 1);
};