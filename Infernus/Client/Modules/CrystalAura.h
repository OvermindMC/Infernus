#pragma once
#include "../../Other/VComponent.h"

typedef void(__thiscall* _CrystalTick)(Actor*);
_CrystalTick CrystalTick;

class CrystalAura : public VModule {
public:
	CrystalAura() : VModule::VModule("CrystalAura", "Automatically blow up ender crystals") {
		this->addWindowObj(new VWindowSlider(&range, 0.0f, 5.0f, "Range: ", MC_Colour(255, 255, 255), 1.0f, 1.0f, MC_Colour(255, 110, 30), .7f));
		this->addWindowObj(new VWindowButton("AutoPlace", &autoPlace));
	};
	void onLoop();
	void onGmTick();
	void placeAround(Actor*);
	void onCrystal(Actor*);
	void initHook();

	void onEnable() { this->delay = 0; };

	int delay = 0;
	float range = 5.0;
	bool autoPlace = true;
private:
	bool hookRan = false;
};

int _delay = 0;

void CrystalCallback(Actor* C) {
	_delay++;
	if (_delay > 20) {
		CrystalAura* CrystalAuraMod = (CrystalAura*)ClientHandler::GetModule(CrystalAura());
		if (CrystalAuraMod->isEnabled) {
			CrystalAuraMod->onCrystal(C);
		};
		_delay = 0;
	};
	CrystalTick(C);
};

void CrystalAura::onLoop() {
	if (!this->hookRan) {
		this->initHook();
		this->hookRan = true;
	};
};

void CrystalAura::onGmTick() {
	delay++;
	if (delay >= 10) {
		LocalPlayer* Player = Minecraft::GetLocalPlayer();
		if (autoPlace && Player != nullptr) {
			ItemStack* heldItem = Player->getSelectedItem();
			if (heldItem->StackCount > 0 && (*heldItem->Item)->itemID == 426) {
				auto Entities = Minecraft::FetchPlayers();
				for (auto Entity : *Entities) {
					if (Utils::distanceVec3(*Entity->getPos(), *Player->getPos()) < range) {
						placeAround(Entity);
					};
				};
			};
		};
		delay = 0;
	};
};

void CrystalAura::placeAround(Actor* Entity) {
	LocalPlayer* Player = Minecraft::GetLocalPlayer();
	Vec3 targetPos = *Entity->getPos();
	for (int x = (int)targetPos.x - range; x < (int)targetPos.x + range; x++) {
		for (int y = (int)targetPos.y - range; y < (int)targetPos.y + range; y++) {
			for (int z = (int)targetPos.z - range; z < (int)targetPos.z + range; z++) {
				Vec3_i blockPos = Vec3_i(x, y, z);
				Vec3_i blockAbove = Vec3(x, y + 1, z);

				Block* block = Player->BlockSource->getBlock(blockPos);
				Block* blockB = Player->BlockSource->getBlock(blockAbove);

				if (block != nullptr) {
					int ID = block->toLegacy()->blockID;
					if ((ID == 49 || ID == 7) && blockB->toLegacy()->blockID == 0) {
						Minecraft::GetGameMode()->buildBlock(&blockPos, 0);
					};
				};
			};
		};
	};
};

void CrystalAura::onCrystal(Actor* C) {
	LocalPlayer* Player = Minecraft::GetLocalPlayer();
	GameMode* GM = Minecraft::GetGameMode();
	if (Player != nullptr) {
		if (Utils::distanceVec3(*C->getPos(), *Player->getPos()) <= range) {
			GM->attack(C);
			Player->swing();
		};
	};
};

void CrystalAura::initHook() {
	uintptr_t Crystal_normalTick = Utils::FindSignature("48 8B C4 55 41 56 41 57 48 8B EC 48 83 EC 70 48 C7 45 ? ? ? ? ? 48 89 58 10 48 89 70 18 48 89 78 20 48 8B 05 ? ? ? ? 48 33 C4 48 89 45 F8 48 8B D9");

	if (Crystal_normalTick != NULL) {
		if (MH_CreateHook((void*)Crystal_normalTick, &CrystalCallback, reinterpret_cast<LPVOID*>(&CrystalTick)) == MH_OK) {
			MH_EnableHook((void*)Crystal_normalTick);
		}
		else {
			Utils::DebugFileLog("Failed to create hook needed for Crystal Aura!");
		};
	}
	else {
		Utils::DebugFileLog("Unable to find address needed for Crystal Aura!");
	};
};