#include "ClientHandler.h"

std::string ClientHandler::commandPrefix = ".";

std::vector<VHook*> HooksList;
std::vector<VCategory*> CategoriesList;
std::vector<VCommand*> CommandsList;
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
#include "Hooks/BlockHooks.h"

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
		HooksList.push_back(new BlockHooks());

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

#include "Commands/TestCommand.h"
#include "Commands/SpamCommand.h"

void ClientHandler::InitCommands() {
	CommandsList.push_back(new TestCommand());
	CommandsList.push_back(new SpamCommand());
};

/* Combat */
#include "Modules/Killaura.h"
#include "Modules/Hitbox.h"
#include "Modules/Aimbot.h"
#include "Modules/Triggerbot.h"
#include "Modules/Criticals.h"
#include "Modules/CrystalAura.h"
#include "Modules/Surround.h"
#include "Modules/Misplace.h"
#include "Modules/BoostHit.h"
#include "Modules/HitTP.h"
#include "Modules/TPAura.h"
/* Movement */
#include "Modules/AirJump.h"
#include "Modules/Jetpack.h"
#include "Modules/AutoSprint.h"
#include "Modules/HighJump.h"
#include "Modules/Speed.h"
#include "Modules/NoWeb.h"
#include "Modules/NoSlowDown.h"
#include "Modules/BunnyHop.h"
#include "Modules/WarpSpeed.h"
#include "Modules/Jesus.h"
#include "Modules/Spider.h"
/* Player */
#include "Modules/Velocity.h"
#include "Modules/Phase.h"
#include "Modules/NoFall.h"
#include "Modules/Flight.h"
#include "Modules/AutoTotem.h"
#include "Modules/ClickTP.h"
#include "Modules/Spammer.h"
#include "Modules/StackableItems.h"
#include "Modules/FOV.h"
/* Visuals */
#include "Menus/TabGui.h"
#include "Menus/ClickGui.h"
#include "Menus/ModuleList.h"
#include "Menus/HUD.h"
#include "Modules/Xray.h"
#include "Modules/Fullbright.h"
#include "Modules/Nametags.h"
/* World */
#include "Modules/Scaffold.h"
#include "Modules/Nuker.h"
#include "Modules/Instabreak.h"
#include "Modules/ChestAura.h"
#include "Modules/PlayerWarning.h"
#include "Modules/TorchBreaker.h"
/* Other */
#include "Modules/Uninject.h"
#include "Modules/AntiBot.h"
#include "Modules/NoPacket.h"
#include "Modules/Freecam.h"
#include "Modules/DeathBack.h"
#include "Modules/TestModule.h"

void ClientHandler::InitModules() {
	/*Combat*/
	PushModule(_Combat, new Killaura());
	PushModule(_Combat, new Hitbox());
	PushModule(_Combat, new Aimbot());
	PushModule(_Combat, new Triggerbot());
	PushModule(_Combat, new Criticals());
	PushModule(_Combat, new CrystalAura());
	PushModule(_Combat, new Surround());
	PushModule(_Combat, new Misplace());
	PushModule(_Combat, new BoostHit());
	PushModule(_Combat, new HitTP());
	PushModule(_Combat, new TPAura());
	/*Movement*/
	PushModule(_Movement, new AirJump());
	PushModule(_Movement, new Jetpack());
	PushModule(_Movement, new AutoSprint());
	PushModule(_Movement, new HighJump());
	PushModule(_Movement, new Speed());
	PushModule(_Movement, new NoWeb());
	PushModule(_Movement, new NoSlowDown());
	PushModule(_Movement, new BunnyHop());
	PushModule(_Movement, new WarpSpeed());
	PushModule(_Movement, new Jesus());
	PushModule(_Movement, new Spider());
	/*Player*/
	PushModule(_Player, new Velocity());
	PushModule(_Player, new Phase());
	PushModule(_Player, new NoFall());
	PushModule(_Player, new Flight());
	PushModule(_Player, new AutoTotem());
	PushModule(_Player, new ClickTP());
	PushModule(_Player, new Spammer());
	PushModule(_Player, new StackableItems());
	PushModule(_Player, new FOV());
	/*Visuals*/
	PushModule(_Visuals, new TabGui());
	PushModule(_Visuals, new ClickGui());
	PushModule(_Visuals, new ModuleList());
	PushModule(_Visuals, new HUD());
	PushModule(_Visuals, new Xray());
	PushModule(_Visuals, new Fullbright());
	PushModule(_Visuals, new Nametags());
	/*World*/
	PushModule(_World, new Scaffold());
	PushModule(_World, new Nuker());
	PushModule(_World, new Instabreak());
	PushModule(_World, new ChestAura());
	PushModule(_World, new PlayerWarning());
	PushModule(_World, new TorchBreaker());
	/*Other*/
	PushModule(_Other, new Uninject());
	PushModule(_Other, new AntiBot());
	PushModule(_Other, new NoPacket());
	PushModule(_Other, new Freecam());
	PushModule(_Other, new DeathBack());
	PushModule(_Other, new TestModule());
};

void ClientHandler::ModuleBaseTick() {
	for (;;) {
		for (auto Category : CategoriesList) {
			for (auto Module : Category->modules) {
				Module->onBaseTick();
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

std::vector<VCommand*> ClientHandler::GetCommands() {
	return CommandsList;
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

bool ClientHandler::handleCommand(std::string input) {
	if (input.rfind(commandPrefix, 0) == 0) {
		std::string strInput = input;
		std::for_each(strInput.begin(), strInput.end(), [](char& c) {
			c = ::tolower(c);
		});

		strInput.erase(0, commandPrefix.length());

		std::istringstream iss(strInput);
		std::vector<std::string> wordsArr(std::istream_iterator<std::string>{iss}, std::istream_iterator<std::string>());

		bool wasFound = false;
		auto Commands = GetCommands();
		
		for (int I = 0; I < Commands.size(); I++) {
			if (Commands.at(I)->input == wordsArr.at(0)) {
				wasFound = true;
				Commands.at(I)->execute(input, wordsArr);
			}
			else {
				if (Commands.at(I) == Commands.back()) {
					if (!wasFound) Commands.back()->reply("Unknown Command!");
					wasFound = false;
				};
			};
		};
		return true;
	};
	return false;
};

void ClientHandler::InitModuleFiles() {
	for (auto Module : ModulesList) {
		bool enabledModule = GetModuleStateFromFile(Module);

		if (enabledModule) Module->onEnable();

		Module->wasEnabled = Module->isEnabled = enabledModule;
		Module->key = GetModuleKeyFromFile(Module);

		InitModuleData(Module);
	};
};

void ClientHandler::UpdateModuleFileData(VModule* Module) {
	std::string moduleFilePath = std::string(Utils::ModuleDir() + "\\" + Module->name);
	std::string keyFilePath = std::string(Utils::KeybindsDir() + "\\" + Module->name);
	
	CloseHandle(CreateFileA(moduleFilePath.c_str(), GENERIC_WRITE | GENERIC_READ, FILE_SHARE_READ | FILE_SHARE_WRITE, NULL, OPEN_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL));
	CloseHandle(CreateFileA(keyFilePath.c_str(), GENERIC_WRITE | GENERIC_READ, FILE_SHARE_READ | FILE_SHARE_WRITE, NULL, OPEN_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL));

	std::ofstream moduleFile;
	moduleFile.open(moduleFilePath.c_str(), std::ofstream::trunc);
	moduleFile << Module->isEnabled;
	moduleFile.close();

	std::ofstream keyFile;
	keyFile.open(keyFilePath.c_str());
	keyFile << std::hex << Module->key;
	keyFile.close();
};

bool ClientHandler::GetModuleStateFromFile(VModule* Module) {
	std::string filePath = std::string(Utils::ModuleDir() + "\\" + Module->name);
	if (Utils::DoesFileExists(filePath)) {
		std::ifstream file;
		file.open(filePath);
		std::string str;
		std::getline(file, str);

		std::istringstream iss(str);
		std::vector<std::string> split(std::istream_iterator<std::string>{iss}, std::istream_iterator<std::string>());

		return split.at(0) == "1";
		file.close();
	}
	else {
		UpdateModuleFileData(Module);
		return Module->isEnabled;
	};
};

uint64_t ClientHandler::GetModuleKeyFromFile(VModule* Module) {
	std::string filePath = std::string(Utils::KeybindsDir() + "\\" + Module->name);
	if (Utils::DoesFileExists(filePath)) {
		UINT64 value;
		std::ifstream file;
		file.open(filePath);
		file >> std::hex >> value;
		file.close();
		return value;
	}
	else {
		UpdateModuleFileData(Module);
	};
	return Module->key;
};

std::string ClientHandler::ModuleDataDir(VModule* Module) {
	std::string filePath = Utils::ModuleDataDir();
	if (filePath.length()) {
		filePath += "\\" + Module->name;
		if (CreateDirectoryA(filePath.c_str(), NULL) || ERROR_ALREADY_EXISTS == GetLastError()) {
			return filePath;
		};
	};
	return NULL;
};

void ClientHandler::InitModuleData(VModule* Module) {
	auto Objects = Module->WindowObjects;
	if (!Objects.empty()) {
		std::string filePath;

		if (!(Objects.size() == 1 && Objects.at(0)->type == VObjectType::Key)) {
			filePath = ModuleDataDir(Module);
			for (auto Obj : Objects) {
				std::string path = filePath + "\\" + std::to_string(Obj->ID);
				if (Utils::DoesFileExists(path)) {
					std::ifstream File(path);
					JSON jsonData = JSON::parse(File);
					std::string fetchedID = jsonData.at("ID").dump();

					if (fetchedID == std::to_string(Obj->ID)) {
						if (Obj->type == VObjectType::Button) {
							*Obj->toggle = jsonData.at("state").dump() == "1" ? true : false;
						};
						if (Obj->type == VObjectType::Slider) {
							*Obj->value = std::atof(jsonData.at("value").dump().c_str());
						};
					}
					else {
						Utils::DebugFileLog("Incorrect ID, Recreating Data Save");
						UpdateModuleData(Module);
						break;
					};
				}
				else {
					Utils::DebugFileLog("Save does not exist");
					UpdateModuleData(Module);
					break;
				};
			};
		};
	};
};

void ClientHandler::UpdateModuleData(VModule* Module) {
	auto Objects = Module->WindowObjects;
	if (!Objects.empty()) {
		std::string filePath;
		if (!(Objects.size() == 1 && Objects.at(0)->type == VObjectType::Key)) {
			filePath = ModuleDataDir(Module);
			for (auto Obj : Objects) {
				std::string path = filePath + "\\" + std::to_string(Obj->ID);
				JSON jsonData;
				jsonData["type"] = Obj->type;
				jsonData["ID"] = Obj->ID;
				jsonData["state"] = Obj->toggle != nullptr ? *Obj->toggle : false;
				jsonData["value"] = Obj->value != nullptr ? *Obj->value : 0;
				std::ofstream File;
				File.open(path, std::ofstream::trunc);
				File << jsonData;
				File.close();
			};
		};
	};
};

void ClientHandler::DataFromJson(const JSON& json, VWindowObject& Obj) {
	json.at("type").get_to(Obj.type);
};