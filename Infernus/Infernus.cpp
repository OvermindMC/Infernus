#include <Windows.h>
#include "Client/ClientHandler.h"

void InitInfernus(LPVOID lpParam) {
	Utils::hModule = (HMODULE)lpParam;

	ClientHandler::InitCategories();
	ClientHandler::InitCommands();
	ClientHandler::InitModules();
	ClientHandler::InitHooks();
	ClientHandler::ModuleBaseTick();
};

BOOL APIENTRY DllMain(HMODULE hModule, DWORD  ul_reason_for_call, LPVOID lpReserved) {
	switch (ul_reason_for_call) {
	case DLL_PROCESS_ATTACH:
		CreateThread(0, 0, (LPTHREAD_START_ROUTINE)InitInfernus, hModule, 0, 0);
	break;
	};
	return TRUE;
};