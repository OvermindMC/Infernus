#include "ClientHandler.h"

std::vector<VHook*> HooksList;
std::vector<VCategory*> CategoriesList;
std::vector<VModule*> ModulesList;

UINT64 Packet::PlayerAuthInputAddr = NULL;
UINT64 Packet::MovePlayerAddr = NULL;
UINT64 Packet::TextAddr = NULL;
UINT64 Packet::ActorFallAddr = NULL;
UINT64 Packet::MobEquipmentAddr = NULL;

#include "Hooks/ClientInstanceHook.h"
#include "Hooks/KeyHook.h"
#include "Hooks/MouseHook.h"
#include "Hooks/RenderHook.h"
#include "Hooks/GameModeHook.h"
#include "Hooks/MultiPlayerLevelHook.h"
#include "Hooks/EntityHooks.h"
#include "Hooks/NetworkHook.h"

void ClientHandler::InitHooks() {
	if (MH_Initialize() == MH_OK) {
		/* Include Hooks */
		HooksList.push_back(new ClientInstanceHook());
		HooksList.push_back(new KeyHook());
		HooksList.push_back(new MouseHook());
		HooksList.push_back(new RenderHook());
		HooksList.push_back(new GameModeHook());
		HooksList.push_back(new MultiPlayerLevelHook());
		HooksList.push_back(new EntityHooks());
		HooksList.push_back(new NetworkHook());

		/* Initialize each hooks functionality */
		for (auto Hook : HooksList) Hook->Init();
	}
	else {
		Utils::DebugFileLog("Failed to initialize MinHook!");
	}
};

void ClientHandler::InitCategories() {
	CategoriesList.push_back(new Combat());
	CategoriesList.push_back(new Movement());
	CategoriesList.push_back(new Player());
	CategoriesList.push_back(new Visuals());
	CategoriesList.push_back(new World());
	CategoriesList.push_back(new Other());
};

/* Combat */
#include "Modules/Killaura.h"
#include "Modules/Hitbox.h"
#include "Modules/Triggerbot.h"
#include "Modules/Criticals.h"
/* Movement */
#include "Modules/AirJump.h"
#include "Modules/Jetpack.h"
#include "Modules/AutoSprint.h"
#include "Modules/HighJump.h"
#include "Modules/Speed.h"
#include "Modules/NoWeb.h"
#include "Modules/NoSlowDown.h"
/* Player */
#include "Modules/Velocity.h"
#include "Modules/Phase.h"
#include "Modules/NoFall.h"
/* Visuals */
#include "Menus/TabGui.h"
#include "Menus/ClickGui.h"
#include "Menus/ModuleList.h"
#include "Menus/HUD.h"
#include "Menus/Radar.h"
/* World */
#include "Modules/Scaffold.h"
#include "Modules/Nuker.h"
/* Other */
#include "Modules/Uninject.h"
#include "Modules/AntiBot.h"

void ClientHandler::InitModules() {
	/*Combat*/
	PushModule(_Combat, new Killaura());
	PushModule(_Combat, new Hitbox());
	PushModule(_Combat, new Triggerbot());
	PushModule(_Combat, new Criticals());
	/*Movement*/
	PushModule(_Movement, new AirJump());
	PushModule(_Movement, new Jetpack());
	PushModule(_Movement, new AutoSprint());
	PushModule(_Movement, new HighJump());
	PushModule(_Movement, new Speed());
	PushModule(_Movement, new NoWeb());
	PushModule(_Movement, new NoSlowDown());
	/*Player*/
	PushModule(_Player, new Velocity());
	PushModule(_Player, new Phase());
	PushModule(_Player, new NoFall());
	/*Visuals*/
	PushModule(_Visuals, new TabGui());
	PushModule(_Visuals, new ClickGui());
	PushModule(_Visuals, new ModuleList());
	PushModule(_Visuals, new HUD());
	PushModule(_Visuals, new Radar());
	/*World*/
	PushModule(_World, new Scaffold());
	PushModule(_World, new Nuker());
	/*Other*/
	PushModule(_Other, new Uninject());
	PushModule(_Other, new AntiBot());
};

void ClientHandler::ModuleBaseTick() {
	while (true) {
		for (auto Category : CategoriesList) {
			for (auto Module : Category->modules) {
				Module->onLoop();
			};
		};
	};
};

/* Utility like Functions */

VCategory* ClientHandler::GetCategory(Categories Category) {
	for (int I = 0; I != Categories::_Other; I++) {
		Categories Current = static_cast<Categories>(I);
		if (Category == Current) {
			if (CategoriesList.at(Current) != CategoriesList.back()) return CategoriesList.at(Current);
			break;
		};
	};
	return CategoriesList.back();
};

void ClientHandler::PushModule(Categories Category, VModule* Module) {
	GetCategory(Category)->modules.push_back(Module);
	ModulesList.push_back(Module);
};

std::vector<VCategory*> ClientHandler::GetCategories() {
	return CategoriesList;
};

std::vector<VModule*> ClientHandler::GetModules() {
	return ModulesList;
};

std::vector<std::string> ClientHandler::CategoriesToString(std::vector<VCategory*> CategoryArr) {
	std::vector<std::string> tempArr;

	for (auto Category : CategoryArr) tempArr.push_back(Category->name);

	return tempArr;
};

std::vector<std::string> ClientHandler::ModulesToString(std::vector<VModule*> ModulesArr) {
	std::vector<std::string> tempArr;

	for (auto Module : ModulesArr) tempArr.push_back(Module->name);

	return tempArr;
};