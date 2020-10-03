#pragma once
#include "TextHolder.h"
#include "LoopbackPacketSender.h"
#include "MinecraftUIRenderContext.h"
#include "Entity.h"
#include "GameMode.h"
#include "ItemStack.h"
#include "PlayerInventory.h"
#include "InventoryTransaction.h"
#include "Packet.h"

class GuiData
{
public:
	char pad_0000[40]; //0x0000
	Vec2 ScaledResolution; //0x0028
public:

	float GuiScale() {
		return *reinterpret_cast<float*>(reinterpret_cast<uintptr_t>(this) + 0x34);
	};

	uint16_t mouseX() {
		return *reinterpret_cast<uint16_t*>(reinterpret_cast<uintptr_t>(this) + 0x52);
	};

	uint16_t mouseY() {
		return *reinterpret_cast<uint16_t*>(reinterpret_cast<uintptr_t>(this) + 0x54);
	};
}; //Size: 0x0030

class MinecraftGame
{
public:
	char pad_0000[216]; //0x0000
	class BitmapFont* Font1; //0x00D8
	char pad_00E0[384]; //0x00E0
	bool canUseKeys; //0x0260
	char pad_0261[7]; //0x0261

public:

}; //Size: 0x0268

class BitmapFont
{
public:
	char pad_0000[16]; //0x0000
}; //Size: 0x0010

class ClientInstance
{
public:
	char pad_0000[152]; //0x0000
	class MinecraftGame* MinecraftGame; //0x0098
	char pad_00A0[56]; //0x00A0
	class LoopbackPacketSender* LoopbackPacketSender; //0x00D8
	char pad_00E0[16]; //0x00E0
	class MoveInputHandler* MoveInputHandler; //0x00F0

public:

	class LocalPlayer* LocalPlayer() {
		if (this != nullptr) {
			return *reinterpret_cast<class LocalPlayer**>(reinterpret_cast<__int64>(this) + 0x140);
		}
		else {
			return nullptr;
		}
	};

	class GuiData* GuiData() {
		uintptr_t** VTable = (uintptr_t**)this;
		return reinterpret_cast<class GuiData*>(VTable[155]);
	};

	class LoopbackPacketSender* GetLoopbackPacketSender() {
		return *reinterpret_cast<class LoopbackPacketSender**>(reinterpret_cast<__int64>(this) + 0xD8);
	};

	bool isValidTarget(class Actor* Entity) {
		if (Entity == nullptr) {
			return false;
		}
		if (Entity->isInvisible() || !Entity->isAlive() || Entity->isImmobile()) {
			return false;
		}
		if (Entity->getEntityTypeId() > 60 && Entity->getEntityTypeId() < 104 && Entity->getEntityTypeId() != 63) {
			return false;
		}
		if (Entity->getNameTag()->getTextLength() <= 1) {
			return false;
		}
		if (!(this->LocalPlayer()->canAttack(Entity, false))) {
			return false;
		}
		return true;
	};

	void clientMessage(std::string input) {
		if (this != nullptr && this->LocalPlayer() != nullptr) {
			this->LocalPlayer()->displayTextObjectMessage(&TextHolder(input));
		};
	};

}; //Size: 0x00F8