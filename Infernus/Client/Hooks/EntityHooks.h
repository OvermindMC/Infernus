#pragma once
#include "../../Other/VComponent.h"

class EntityHooks : public VHook {
public:
	void Init();
};

typedef void(__thiscall* _LerpMotion)(Actor*, Vec3*);
_LerpMotion LerpMotion;

typedef float(__thiscall* _GetJumpPower)(Actor*, Vec3);
_GetJumpPower GetJumpPower;

typedef void(__thiscall* _EntityTick)(Actor*);
_EntityTick EntityTick;

void LerpMotionCallback(Actor* Entity, Vec3* Velocity) {
	LocalPlayer* Player = Minecraft::GetLocalPlayer();
	if (Player != nullptr && Entity == Player->toActor()) {
		for (auto Module : ClientHandler::GetModules()) {
			Module->onLerpMotion(Velocity);
		};
	};
	LerpMotion(Entity, Velocity);
};

float GetJumpPowerCallback(Actor* Entity, Vec3 moveToPos) {
	LocalPlayer* Player = Minecraft::GetLocalPlayer();
	if (Entity == Player->toActor()) {
		for (auto Module : ClientHandler::GetModules()) {
			if (Module->isEnabled) {
				float retVal = 0.0f;
				Module->onJump(&retVal);
				if (retVal > 0.0f) return retVal;
			};
		};
	};
	return GetJumpPower(Entity, moveToPos);
};

std::vector<Actor*>* TickedEntities = new std::vector<Actor*>();

void EntityTickCallback(Actor* Entity) {
	LocalPlayer* Player = Minecraft::GetLocalPlayer();

	if (Player != nullptr) {
		if (Entity->GetRuntimeID() == Player->toActor()->GetRuntimeID()) {
			if (!TickedEntities->empty()) {
				for (auto Module : ClientHandler::GetModules()) {
					Module->onEntityTick(TickedEntities);
				};
				TickedEntities->clear();
			};
		}
		else {
			if (Entity->getEntityTypeId() != 63) {
				bool doesExist = false;
				for (auto Ent : *TickedEntities) {
					if (Ent->GetRuntimeID() == Entity->GetRuntimeID()) doesExist = true;
				};
				if (!doesExist && Entity->isAlive() && !Entity->isInvisible() && !Entity->outOfWorld()) TickedEntities->push_back(Entity);
			};
		};
	}
	else {
		if (!TickedEntities->empty()) TickedEntities->clear();
	};

	EntityTick(Entity);
};

void EntityHooks::Init() {
	uintptr_t signatureAddr = Utils::FindSignature("48 8D 05 ? ? ? ? 48 89 07 33 C9 48 89 8F ? ? ? ? 48 89 8F ? ? ? ? 48 89 8F ? ? ? ? 48 89 8F ? ? ? ? 48 89 8F ? ? ? ? C6 87 ? ? ? ? ? 48 89 8F ? ? ? ? 48 89 8F ? ? ? ? 48 89 8F ? ? ? ? 48 89 8F ? ? ? ");
	if (signatureAddr != NULL) {
		Utils::DebugFileLog("Found the address needed for the Entity Hooks, Preparing Hooks now...");
		int offset = *reinterpret_cast<int*>(signatureAddr + 3);
		uintptr_t** VTable = reinterpret_cast<uintptr_t**>(signatureAddr + offset + 7);

		void* lerpMotionAddr = (void*)VTable[37];
		if (MH_CreateHook(lerpMotionAddr, &LerpMotionCallback, reinterpret_cast<LPVOID*>(&LerpMotion)) == MH_OK) {
			Utils::DebugFileLog("Successfully created Lerp Motion Hook, Enabling Hook now...");
			MH_EnableHook(lerpMotionAddr);
		}
		else {
			Utils::DebugFileLog("Failed to create hook for Lerp Motion!");
		};

		void* getJumpPowerAddr = (void*)VTable[271];
		if (MH_CreateHook(getJumpPowerAddr, &GetJumpPowerCallback, reinterpret_cast<LPVOID*>(&GetJumpPower)) == MH_OK) {
			Utils::DebugFileLog("Successfully created GetJumpPower Hook, Enabling Hook now...");
			MH_EnableHook(getJumpPowerAddr);
		}
		else {
			Utils::DebugFileLog("Failed to create hook for GetJumpPower!");
		};

		void* entityTickAddr = (void*)VTable[39];
		if (MH_CreateHook(entityTickAddr, &EntityTickCallback, reinterpret_cast<LPVOID*>(&EntityTick)) == MH_OK) {
			Utils::DebugFileLog("Successfully created hook for Entity Base Tick, Enabling hook now...");
			MH_EnableHook(entityTickAddr);
		}
		else {
			Utils::DebugFileLog("Failed to create hook for Entity Base Tick!");
		};
	}
	else {
		Utils::DebugFileLog("Could not find the address needed for the Entity Hooks");
	};
};