#include "ClientHandler.h"

std::vector<VHook*> HooksList;
std::vector<VCategory*> CategoriesList;
std::vector<VModule*> ModulesList;

#include "Hooks/ClientInstanceHook.h"
#include "Hooks/KeyHook.h"
#include "Hooks/MouseHook.h"
#include "Hooks/RenderHook.h"
#include "Hooks/GameModeHook.h"
#include "Hooks/MultiPlayerLevelHook.h"
#include "Hooks/EntityHooks.h"

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
/* Movement */
#include "Modules/AirJump.h"
#include "Modules/Jetpack.h"
#include "Modules/AutoSprint.h"
#include "Modules/HighJump.h"
/* Player */
#include "Modules/Velocity.h"
/* Visuals */
#include "Menus/TabGui.h"
#include "Menus/ClickGui.h"
#include "Menus/ModuleList.h"
/* World */
#include "Modules/Scaffold.h"
/* Other */
#include "Modules/Uninject.h"
#include "Modules/AntiBot.h"

void ClientHandler::InitModules() {
	/*Combat*/
	PushModule(_Combat, new Killaura());
	PushModule(_Combat, new Hitbox());
	/*Movement*/
	PushModule(_Movement, new AirJump());
	PushModule(_Movement, new Jetpack());
	PushModule(_Movement, new AutoSprint());
	PushModule(_Movement, new HighJump());
	/*Player*/
	PushModule(_Player, new Velocity());
	/*Visuals*/
	PushModule(_Visuals, new TabGui());
	PushModule(_Visuals, new ClickGui());
	PushModule(_Visuals, new ModuleList());
	/*World*/
	PushModule(_World, new Scaffold());
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


/* Hook Events */

void ClientHandler::TickRender() {
	for (auto Module : ModulesList) {
		if (Module->isEnabled) Module->onRender();
	};
};

void ClientHandler::TickGameMode() {
	for (auto Module : ModulesList) {
		if (Module->isEnabled) Module->onGmTick();
	};
};

void ClientHandler::TickOnLerp(Vec3* velocity) {
	for (auto Module : ModulesList) {
		if(Module->isEnabled) Module->onLerpMotion(velocity);
	};
};