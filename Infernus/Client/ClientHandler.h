#pragma once
#include "../Other/Utils.h"
#include "../Other/VComponent.h"
#include "../SDK/Minecraft.h"

#include "Categories/Combat.h"
#include "Categories/Movement.h"
#include "Categories/Player.h"
#include "Categories/Visuals.h"
#include "Categories/World.h"
#include "Categories/Other.h"

/* Categories enum for registering Modules */

enum Categories {
	_Combat,
	_Movement,
	_Player,
	_Visuals,
	_World,
	_Other
};

/* ClientHandler Class */

class ClientHandler {
public:
	static std::string commandPrefix;

	static void InitHooks();
	static void InitCategories();
	static void InitCommands();
	static void InitModules();
	static void ModuleBaseTick();

	/* Utility like Functions */

	static VModule* GetModule(VModule inputModule) {
		for (auto Module : GetModules()) {
			if (Module->name == inputModule.name && Module->description == inputModule.description) return Module;
		};
	};

	static VCategory* GetCategory(Categories Category);
	static void PushModule(Categories Category, VModule* Module);

	static std::vector<VCategory*> GetCategories();
	static std::vector<VCommand*> GetCommands();
	static std::vector<VModule*> GetModules();

	static std::vector<std::string> CategoriesToString(std::vector<VCategory*> CategoryArr);
	static std::vector<std::string> ModulesToString(std::vector<VModule*> ModulesArr);

	static bool handleCommand(std::string);
};