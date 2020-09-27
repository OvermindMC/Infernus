#pragma once

enum class PacketType {
	PlayerAuthInput,
	MovePlayerPacket,
	TextPacket,
	ActorFallPacket,
	MobEquipmentPacket,
	Unknown
};

class Packet {
public:
	static UINT64 PlayerAuthInputAddr;
	static UINT64 MovePlayerAddr;
	static UINT64 TextAddr;
	static UINT64 ActorFallAddr;
	static UINT64 MobEquipmentAddr;
public:

	static UINT64 GetAuthVTable() {
		if (PlayerAuthInputAddr == NULL) {
			uintptr_t PlayerAuthInputPacketAddr = Utils::FindSignature("48 8D 05 ? ? ? ? 48 89 45 ? 48 89 4D ? 0F 57 C9 0F 29 4D");
			int PlayerAuthOff = *reinterpret_cast<int*>(PlayerAuthInputPacketAddr + 3);
			PlayerAuthInputAddr = (UINT64)reinterpret_cast<uintptr_t**>(PlayerAuthInputPacketAddr + PlayerAuthOff + 7);

			return PlayerAuthInputAddr;
		}
		else {
			return PlayerAuthInputAddr;
		}
	};

	static UINT64 GetMoveVTable() {
		if (MovePlayerAddr == NULL) {
			uintptr_t MovementPlayerPacketAddr = Utils::FindSignature("48 8D 15 ? ? ? ? 48 89 11 48 89 79 ? 48 89 79 ? 48 89 79 ? 48 89 79 ? 66 89 79 ? 48 89 79");
			int MovementOff = *reinterpret_cast<int*>(MovementPlayerPacketAddr + 3);
			MovePlayerAddr = (UINT64)reinterpret_cast<uintptr_t**>(MovementPlayerPacketAddr + MovementOff + 7);

			return MovePlayerAddr;
		}
		else {
			return MovePlayerAddr;
		}
	};

	static UINT64 GetTextVTable() {
		if (TextAddr == NULL) {
			uintptr_t TextPacketAddr = Utils::FindSignature("48 8D 05 ?? ?? ?? ?? 48 8B F9 48 89 01 48 83 C1 ?? E8 ?? ?? ?? ?? 48 8D 8F");
			int TextPacketOff = *reinterpret_cast<int*>(TextPacketAddr + 3);
			TextAddr = (UINT64)reinterpret_cast<uintptr_t**>(TextPacketAddr + TextPacketOff + 7);

			return TextAddr;
		}
		else {
			return TextAddr;
		}
	};

	static UINT64 GetActorFallVTable() {
		if (ActorFallAddr == NULL) {
			uintptr_t ActorFallPacketAddr = Utils::FindSignature("48 8D ? ? ? ? ? 48 89 ? E7 48 89 45 0F F3 0F 11 75 ?");
			int ActorFallOff = *reinterpret_cast<int*>(ActorFallPacketAddr + 3);
			ActorFallAddr = (UINT64)reinterpret_cast<uintptr_t**>(ActorFallPacketAddr + ActorFallOff + 7);

			return ActorFallAddr;
		}
		else {
			return ActorFallAddr;
		}
	};

	static UINT64 GetMobEquipmentVTable() {
		if (MobEquipmentAddr == NULL) {
			uintptr_t MobEquipmentPacketAddr = Utils::FindSignature("48 8D 05 ? ? ? ? 48 89 01 48 89 51 ? 48 8D 59 ? 48 89 5C 24 ? 49 8B D0");
			int MobEquipmentOff = *reinterpret_cast<int*>(MobEquipmentPacketAddr + 3);
			MobEquipmentAddr = (UINT64)reinterpret_cast<uintptr_t**>(MobEquipmentPacketAddr + MobEquipmentOff + 7);

			return MobEquipmentAddr;
		}
		else {
			return MobEquipmentAddr;
		};
	};
};

class PlayerAuthInputPacket
{
public:
	UINT64 VTable; //0x0000
	char pad_0008[32]; //0x0008
	Vec2 lookingVector; //0x0028
	Vec3 positionVector; //0x0030
	char pad_003C[8]; //0x003C

	PlayerAuthInputPacket(Vec2 looking, Vec3 position) {
		this->VTable = (UINT64)Packet::GetAuthVTable();
		this->lookingVector = looking;
		this->positionVector = position;
	}
}; //Size: 0x004B

class MovePlayerPacket
{
public:
	UINT64 VTable; //0x0000
	char pad_0008[32]; //0x0008
	uint64_t runtimeID; //0x0028
	Vec3 position; //0x0030
	Vec2 rotation; //0x003C
	char pad_0044[4]; //0x0044
	uint8_t mode; //0x0048
	bool onGround; //0x0049
	char pad_004A[70]; //0x004A

	MovePlayerPacket(class Actor* Entity, Vec3 position, Vec2 rotation, bool onGround) {
		this->VTable = (UINT64)Packet::GetMoveVTable();
		this->runtimeID = Entity->EntityID;
		this->position = position;
		this->rotation = rotation;
		this->mode = 0;
		this->onGround = onGround;
	};
}; //Size: 0x0089

class TextPacket {
public:

	UINT64 VTable; //0x0000
	char pad_0008[32]; //0x0008
	__int8 type; //0x0028
	char pad_0029[7]; //0x0029
	TextHolder author; //0x0030
	TextHolder message; //0x0038
	char pad_0040[72]; //0x0040
	bool needsTranslate = false; //0x0088
	char pad_0089[7]; //0x0089
	TextHolder xboxUserID; //0x0090
	TextHolder platformChatID; //0x0098


	TextPacket(class Actor* Entity, std::string text) {
		this->VTable = Packet::GetTextVTable();
		this->type = 1;
		this->message.setText(text);
		this->author.setText(Entity->getNameTag()->getText());
	};
};

class MobEquipmentPacket {
public:

	UINT64 VTable; //0x0000 
	char pad_0x0008[0x438]; //0x0008

	MobEquipmentPacket(__int64 entityRuntimeID, ItemStack& Item, int hotbarSlot, int inventorySlot) {
		memset(this, 0, sizeof(MobEquipmentPacket));
		this->VTable = Packet::GetMobEquipmentVTable();
		using _MobEquipmentC = void(__fastcall*)(MobEquipmentPacket*, __int64, ItemStack&, int, int, char);
		static _MobEquipmentC MobEquipmentC = reinterpret_cast<_MobEquipmentC>(Utils::FindSignature("48 89 4C 24 ? 56 57 41 56 48 83 EC ? 48 C7 44 24 ? ? ? ? ? 48 89 5C 24 ? 41 8B F1 49 8B F8 4C 8B F1"));
		if (MobEquipmentC != NULL) {
			MobEquipmentC(this, entityRuntimeID, Item, hotbarSlot, inventorySlot, 0);
		};
	};
};