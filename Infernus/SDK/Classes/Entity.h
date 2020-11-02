#pragma once
#include "BlockLegacy.h"
#include "MultiPlayerLevel.h"

class Actor
{
public:
	char pad_0008[224]; //0x0008
	uint64_t EntityID; //0x00E8
	char pad_00F0[16]; //0x00F0
	Vec2 lookingVector; //0x0100
	char pad_0108[152]; //0x0108
	bool onGround; //0x01A0
	char pad_01A1[359]; //0x01A1
	int movedTick; //0x0308
	char pad_0310[160]; //0x0310
	std::string type; //0x03B0
	char pad_03B8[172]; //0x03B8
	Vec3 Position; //0x0464
	char pad_0470[36]; //0x0470
	Vec3 Velocity; //0x0494
	char pad_04A0[888]; //0x04A0
	std::string username; //0x0818
	char pad_0820[104]; //0x0820

	virtual void Function0();
	virtual void Function1();
	virtual void Function2();
	virtual void Function3();
	virtual void Function4();
	virtual void Function5();
	virtual void Function6();
	virtual void Function7();
	virtual void Function8();
	virtual void Function9();
	virtual void Function10();
	virtual void Function11();
	virtual void setPos(Vec3*);
	virtual Vec3* getPos();
	virtual Vec3* getPosOld();
	virtual void Function15();
	virtual void Function16();
	virtual void Function17();
	virtual void Function18();
	virtual void Function19();
	virtual void Function20();
	virtual void Function21();
	virtual void Function22();
	virtual void Function23();
	virtual void Function24();
	virtual void Function25();
	virtual void Function26();
	virtual void Function27();
	virtual void Function28();
	virtual void Function29();
	virtual void Function30();
	virtual void Function31();
	virtual void Function32();
	virtual void Function33();
	virtual void Function34();
	virtual void Function35();
	virtual void Function36();
	virtual void Function37();
	virtual void Function38();
	virtual void Function39();
	virtual void Function40();
	virtual void Function41();
	virtual void Function42();
	virtual void Function43();
	virtual void Function44();
	virtual void Function45();
	virtual void Function46();
	virtual void Function47();
	virtual void Function48();
	virtual void Function49();
	virtual void Function50();
	virtual bool isInWall();
	virtual bool isInvisible();
	virtual void Function53();
	virtual void Function54();
	virtual void Function55();
	virtual class TextHolder* getNameTag();
	virtual void Function57();
	virtual void Function58();
	virtual void Function59();
	virtual void setnameTag();
	virtual void Function61();
	virtual void Function62();
	virtual void Function63();
	virtual bool isInWater();
	virtual void Function65();
	virtual void Function66();
	virtual void Function67();
	virtual bool isInLava();
	virtual void Function69();
	virtual void Function70();
	virtual void Function71();
	virtual void Function72();
	virtual void Function73();
	virtual void Function74();
	virtual void Function75();
	virtual void Function76();
	virtual void Function77();
	virtual void Function78();
	virtual void Function79();
	virtual void Function80();
	virtual void Function81();
	virtual void Function82();
	virtual void Function83();
	virtual void Function84();
	virtual bool isImmobile();
	virtual void Function86();
	virtual void Function87();
	virtual void Function88();
	virtual void Function89();
	virtual void Function90();
	virtual bool isSneaking();
	virtual void setSneaking(bool);
	virtual void Function93();
	virtual void Function94();
	virtual bool isAlive();
	virtual void Function96();
	virtual void Function97();
	virtual void Function98();
	virtual void Function99();
	virtual void Function100();
	virtual bool canAttack(class Actor*, bool);
	virtual void Function102();
	virtual void Function103();
	virtual void Function104();
	virtual void Function105();
	virtual void Function106();
	virtual void Function107();
	virtual void Function108();
	virtual void Function109();
	virtual void Function110();
	virtual void Function111();
	virtual void Function112();
	virtual void Function113();
	virtual void Function114();
	virtual void Function115();
	virtual void Function116();
	virtual void Function117();
	virtual void Function118();
	virtual void Function119();
	virtual void Function120();
	virtual void Function121();
	virtual void Function122();
	virtual bool shouldRender();
	virtual void Function124();
	virtual void Function125();
	virtual void Function126();
	virtual void Function127();
	virtual void Function128();
	virtual void Function129();
	virtual void Function130();
	virtual void Function131();
	virtual void Function132();
	virtual void Function133();
	virtual void Function134();
	virtual void Function135();
	virtual void Function136();
	virtual void Function137();
	virtual void Function138();
	virtual void Function139();
	virtual void Function140();
	virtual void Function141();
	virtual void Function142();
	virtual void Function143();
	virtual void Function144();
	virtual void Function145();
	virtual void Function146();
	virtual void Function147();
	virtual void Function148();
	virtual void Function149();
	virtual void Function150();
	virtual void Function151();
	virtual void Function152();
	virtual void Function153();
	virtual void Function154();
	virtual void Function155();
	virtual void Function156();
	virtual void Function157();
	virtual void Function158();
	virtual int getEntityTypeId(void);
	virtual void queryEntityRenderer(void);
	virtual void Function161();
	virtual void Function162();
	virtual void Function163();
	virtual void Function164();
	virtual void Function165();
	virtual void Function166();
	virtual void Function167();
	virtual void Function168();
	virtual void Function169();
	virtual void Function170();
	virtual void Function171();
	virtual void Function172();
	virtual void Function173();
	virtual void Function174();
	virtual void Function175();
	virtual void Function176();
	virtual void Function177();
	virtual void Function178();
	virtual void Function179();
	virtual void Function180();
	virtual void Function181();
	virtual void Function182();
	virtual void Function183();
	virtual void Function184();
	virtual void Function185();
	virtual void Function186();
	virtual void Function187();
	virtual void Function188();
	virtual void Function189();
	virtual void Function190();
	virtual void Function191();
	virtual void Function192();
	virtual void Function193();
	virtual void Function194();
	virtual void Function195();
	virtual void Function196();
	virtual void Function197();
	virtual void Function198();
	virtual void Function199();
	virtual void Function200();
	virtual void Function201();
	virtual void Function202();
	virtual void Function203();
	virtual void Function204();
	virtual void Function205();
	virtual void Function206();
	virtual void Function207();
	virtual void Function208();
	virtual void Function209();
	virtual void Function210();
	virtual void Function211();
	virtual void Function212();
	virtual bool isCreative();
	virtual bool isAdventure();
	virtual void Function215();
	virtual void Function216();
	virtual void Function217();
	virtual void Function218();
	virtual void Function219();
	virtual void setSize(float, float);
	virtual float getJumpPower();
	virtual void Function222();
	virtual void Function223();
	virtual bool wasHurt();
	virtual void Function225();
	virtual void Function226();
	virtual void Function227();
	virtual void Function228();
	virtual void Function229();
	virtual void Function230();
	virtual void Function231();
	virtual void Function232();
	virtual void Function233();
	virtual void Function234();
	virtual void Function235();
	virtual void Function236();
	virtual void Function237();
	virtual void Function238();
	virtual bool outOfWorld();

public:

	uint64_t GetRuntimeID() {
		using _GetRunTimeID = uint64_t * (__fastcall*)(Actor*);
		static _GetRunTimeID GetRunTimeID = reinterpret_cast<_GetRunTimeID>(Utils::FindSignature("48 8D 81 ? ? ? ? 48 83 38 FF 75 18 48 8B 89 ? ? ? ? 48 FF 81 ? ? ? ? 48 8B 89 ? ? ? ?"));
		return (uint64_t) * reinterpret_cast<uint64_t**>(reinterpret_cast<__int64>(GetRunTimeID(this)));
	};

	void _crit(Actor* Entity) {
		using _Crit = void* (__fastcall*)(Actor*, Actor*);
		static _Crit Crit = reinterpret_cast<_Crit>(Utils::FindSignature("4C 8B DC 48 83 EC 78 49 C7 43 ? ? ? ? ? 48 8B 05 ? ? ? ? 48 33 C4 48 89 44 24 ? 48 8B 81 ? ? ? ?"));
		Crit(this, Entity);
	};

	void applyTurnDelta(Vec2* angles) {
		using _ApplyTurn = void(__fastcall*)(Actor*, Vec2*);
		static _ApplyTurn ApplyTurn = reinterpret_cast<_ApplyTurn>(Utils::FindSignature("48 89 5C 24 ?? 57 48 83 EC ?? 48 8B D9 0F 29 74 24 ?? 48 8B 89 ?? ?? ?? ?? 48 8B ?? 0F 29 7C 24 ?? 44 0F"));
		ApplyTurn(this, angles);
	};

	int currentGameMode() {
		int currGM = 0;

		if (this->isCreative()) {
			currGM = 1;
		}
		else {
			if (this->isAdventure()) currGM = 2;
		}

		return currGM;
	};

	class PlayerInventory* GetInventory() {
		return *reinterpret_cast<class PlayerInventory**>(reinterpret_cast<__int64>(this) + 0xB70);
	};

	class InventoryMenu* GetInventoryMenu() {
		return *reinterpret_cast<class InventoryMenu**>(reinterpret_cast<__int64>(this) + 0x1F10);
	};

	class BlockSource* GetBlockSource() {
		return *reinterpret_cast<class BlockSource**>(reinterpret_cast<__int64>(this) + 0x320);
	};

	class MultiPlayerLevel* GetMultiPlayerLevel() {
		return *reinterpret_cast<class MultiPlayerLevel**>(reinterpret_cast<__int64>(this) + 0x330);
	};

	class InventoryTransactionManager* GetTransactionManager() {
		return reinterpret_cast<InventoryTransactionManager*>(reinterpret_cast<__int64>(this) + 0x1178); //Extends LocalPlayer?
	};

	void setFlying(bool value) {
		uintptr_t _this = reinterpret_cast<uintptr_t>(this);
		bool* flyingAddr = (bool*)(_this + 0x8B8);
		*flyingAddr = value;
	};

	bool isCollidedDir() {
		Vec3 currPos = *this->getPos();
		float calcYaw = this->lookingVector.y + 90.0f;
		Vec3 playerVel = Vec3(cos((calcYaw) * (PI / 180.0f)), 0.f, sin((calcYaw) * (PI / 180.0f)));
		Vec3 blockPos = Vec3(currPos.x + playerVel.x * 1.0f, currPos.y, currPos.z + playerVel.z * 1.0f);
		Block* block = this->GetBlockSource()->getBlock(blockPos);
		if (block->toLegacy()->blockID > 0) {
			return true;
		}
		else {
			block = this->GetBlockSource()->getBlock(Vec3(blockPos.x, blockPos.y - 1.4f, blockPos.z));
			return block->toLegacy()->blockID > 0;
		};
	};

	Vec3 getEyePos() {
		uintptr_t _this = reinterpret_cast<uintptr_t>(this);
		return *reinterpret_cast<Vec3*>(_this + 0x120);
	};

	void setFallDistance(float fallDistance) {
		*reinterpret_cast<float*>(reinterpret_cast<__int64>(this) + 0x19C) = fallDistance;
	};

}; //Size: 0x0608

class LocalPlayer
{
public:

	char pad_0008[224]; //0x0008
	uint64_t EntityID; //0x00E8
	char pad_00F0[16]; //0x00F0
	Vec2 lookingVector; //0x0100
	char pad_0108[148]; //0x0108
	float fallIncrementor; //0x019C
	bool onGround; //0x01A0
	char pad_01A1[115]; //0x01A1
	float webSlowSpeed; //0x0214
	char pad_0218[264]; //0x0218
	class BlockSource* BlockSource; //0x0320
	char pad_0328[8]; //0x0328
	class MultiPlayerLevel* MultiPlayerLevel; //0x0330
	char pad_0338[288]; //0x0338
	Vec3 DefaultPosition; //0x0458
	Vec3 Position; //0x0464
	char pad_0470[4]; //0x0470
	Vec2 Collision; //0x0474
	char pad_047C[24]; //0x047C
	Vec3 Velocity; //0x0494
	char pad_04A0[888]; //0x04A0
	std::string username; //0x0818
	char pad_0820[848]; //0x0820
	class PlayerInventory* PlayerInventory; //0x0B70
	char pad_0B78[1312]; //0x0B78
	BYTE* inventoryState; //0x1098
	/*char pad_10A0[16]; //0x10A0*/

	virtual void Function0();
	virtual void Function1();
	virtual void Function2();
	virtual void Function3();
	virtual void Function4();
	virtual void Function5();
	virtual void Function6();
	virtual void Function7();
	virtual void Function8();
	virtual void Function9();
	virtual void Function10();
	virtual void Function11();
	virtual void setPos(Vec3*);
	virtual Vec3* getPos();
	virtual Vec3* getPosOld();
	virtual void Function15();
	virtual void Function16();
	virtual void Function17();
	virtual void Function18();
	virtual void Function19();
	virtual void Function20();
	virtual void Function21();
	virtual void Function22();
	virtual void Function23();
	virtual void Function24();
	virtual void Function25();
	virtual void Function26();
	virtual void Function27();
	virtual void Function28();
	virtual void Function29();
	virtual void Function30();
	virtual void Function31();
	virtual void Function32();
	virtual void Function33();
	virtual void Function34();
	virtual void Function35();
	virtual void Function36();
	virtual void lerpMotion(Vec3*);
	virtual void Function38();
	virtual void Function39();
	virtual void Function40();
	virtual void Function41();
	virtual void Function42();
	virtual void Function43();
	virtual void Function44();
	virtual void Function45();
	virtual void Function46();
	virtual void Function47();
	virtual void Function48();
	virtual void Function49();
	virtual void Function50();
	virtual void Function51();
	virtual void Function52();
	virtual void Function53();
	virtual void Function54();
	virtual void Function55();
	virtual class TextHolder* getNameTag();
	virtual void Function57();
	virtual void Function58();
	virtual void Function59();
	virtual void Function60();
	virtual void Function61();
	virtual void Function62();
	virtual void Function63();
	virtual bool isInWater();
	virtual void Function65();
	virtual void Function66();
	virtual void Function67();
	virtual bool isInLava();
	virtual void Function69();
	virtual void Function70();
	virtual void Function71();
	virtual void Function72();
	virtual void Function73();
	virtual void Function74();
	virtual void Function75();
	virtual void startRiding(class Actor*);
	virtual void Function77();
	virtual void Function78();
	virtual void Function79();
	virtual void Function80();
	virtual void Function81();
	virtual void Function82();
	virtual void Function83();
	virtual void Function84();
	virtual bool isImmobile();
	virtual void Function86();
	virtual void Function87();
	virtual void Function88();
	virtual bool isSleeping();
	virtual void Function90();
	virtual bool isSneaking();
	virtual void setSneaking(bool);
	virtual bool isBlocking();
	virtual void Function94();
	virtual bool isAlive();
	virtual bool isOnFire();
	virtual bool isOnHotBlock();
	virtual void Function98();
	virtual void Function99();
	virtual void Function100();
	virtual bool canAttack(class Actor*, bool);
	virtual void Function102();
	virtual void Function103();
	virtual void Function104();
	virtual void attack(Actor*);
	virtual void Function106();
	virtual void Function107();
	virtual void Function108();
	virtual void Function109();
	virtual void Function110();
	virtual void Function111();
	virtual void Function112();
	virtual void Function113();
	virtual void Function114();
	virtual void Function115();
	virtual void Function116();
	virtual bool canPowerJump();
	virtual void setCanPowerJump(bool);
	virtual bool isJumping();
	virtual void Function120();
	virtual void Function121();
	virtual void Function122();
	virtual bool shouldRender();
	virtual void Function124();
	virtual void Function125();
	virtual void Function126();
	virtual void animateHurt(void);
	virtual void Function128();
	virtual void Function129();
	virtual void Function130();
	virtual void feed(int);
	virtual void Function132();
	virtual void Function133();
	virtual void getActorRendererId();
	virtual void Function135();
	virtual void Function136();
	virtual void Function137();
	virtual void Function138();
	virtual void Function139();
	virtual void Function140();
	virtual void Function141();
	virtual void Function142();
	virtual void Function143();
	virtual void Function144();
	virtual void Function145();
	virtual void Function146();
	virtual void Function147();
	virtual void Function148();
	virtual void Function149();
	virtual class ItemStack* getSelectedItem(void);
	virtual void setCarriedItem(class ItemStack*);
	virtual void setOffHandSlot(class ItemStack*);
	virtual class ItemStack* getEquippedTotem(void);
	virtual void consumeTotem(void);
	virtual void Function155();
	virtual void Function156();
	virtual void Function157();
	virtual void Function158();
	virtual int getEntityTypeId(void);
	virtual void queryEntityRenderer(void);
	virtual void Function161();
	virtual void Function162();
	virtual void Function163();
	virtual void Function164();
	virtual void Function165();
	virtual INT64 getPortalWaitTime();
	virtual void Function167();
	virtual void Function168();
	virtual void Function169();
	virtual void Function170();
	virtual void Function171();
	virtual void Function172();
	virtual void causeFallDamage(float);
	virtual void Function174();
	virtual void Function175();
	virtual void Function176();
	virtual void Function177();
	virtual bool canAddRider(class Actor*);
	virtual void Function179();
	virtual void Function180();
	virtual bool inCaravan();
	virtual void Function182();
	virtual void Function183();
	virtual void Function184();
	virtual void Function185();
	virtual void stopRiding(bool, bool, bool);
	virtual void startSwimming(void);
	virtual void stopSwimming(void);
	virtual void Function189();
	virtual void Function190();
	virtual void Function191();
	virtual void Function192();
	virtual void Function193();
	virtual void heal(int);
	virtual bool isInvertedHealAndHarm();
	virtual void Function196();
	virtual void Function197();
	virtual void Function198();
	virtual void Function199();
	virtual void Function200();
	virtual void Function201();
	virtual void Function202();
	virtual void Function203();
	virtual void swing(void);
	virtual void Function205();
	virtual void Function206();
	virtual void Function207();
	virtual void Function208();
	virtual void Function209();
	virtual void Function210();
	virtual void Function211();
	virtual void Function212();
	virtual bool isCreative();
	virtual bool isAdventure();
	virtual void add(class ItemStack*);
	virtual void drop(class ItemStack*, bool);
	virtual void Function217();
	virtual void Function218();
	virtual void Function219();
	virtual void setSize();
	virtual void Function221();
	virtual void Function222();
	virtual void wobble(void);
	virtual bool wasHurt();
	virtual void Function225();
	virtual void Function226();
	virtual void Function227();
	virtual void Function228();
	virtual void Function229();
	virtual void reloadLootTable(void);
	virtual void Function231();
	virtual void kill(void);
	virtual void Function233();
	virtual void shouldTick(void);
	virtual void Function235();
	virtual void shouldTryMakeStepSound(void);
	virtual void Function237();
	virtual void Function238();
	virtual bool outOfWorld();
	virtual void Function240();
	virtual void markHurt(void);
	virtual void Function242();
	virtual void Function243();
	virtual void Function244();
	virtual void Function245();
	virtual void Function246();
	virtual void Function247();
	virtual void Function248();
	virtual void updateWaterState(void);
	virtual void doWaterSplashEffect(void);
	virtual void spawnTrailBubbles(void);
	virtual void Function252();
	virtual void Function253();
	virtual void Function254();
	virtual void Function255();
	virtual void Function256();
	virtual void Function257();
	virtual void Function258();
	virtual void Function259();
	virtual void Function260();
	virtual void Function261();
	virtual bool isSprinting();
	virtual void setSprinting(bool);
	virtual void Function264();
	virtual void Function265();
	virtual void Function266();
	virtual void Function267();
	virtual void Function268();
	virtual float getSpeed();
	virtual void setSpeed(float);
	virtual float getJumpPower();
	virtual void Function272();
	virtual void Function273();
	virtual void Function274();
	virtual void Function275();
	virtual void Function276();
	virtual void Function277();
	virtual void Function278();
	virtual void pushActors();
	virtual void lookAt(class Actor*, float, float);
	virtual bool isLookingAtAnEntity();
	virtual void Function282();
	virtual void Function283();
	virtual void Function284();
	virtual void Function285();
	virtual void Function286();
	virtual void Function287();
	virtual void Function288();
	virtual void Function289();
	virtual void Function290();
	virtual void Function291();
	virtual void Function292();
	virtual void Function293();
	virtual void Function294();
	virtual void Function295();
	virtual void Function296();
	virtual void Function297();
	virtual void Function298();
	virtual void Function299();
	virtual void Function300();
	virtual void Function301();
	virtual void Function302();
	virtual void Function303();
	virtual void Function304();
	virtual void Function305();
	virtual void Function306();
	virtual void Function307();
	virtual void Function308();
	virtual void Function309();
	virtual void Function310();
	virtual void Function311();
	virtual void Function312();
	virtual void Function313();
	virtual void Function314();
	virtual void Function315();
	virtual void Function316();
	virtual void Function317();
	virtual void Function318();
	virtual void Function319();
	virtual void Function320();
	virtual void Function321();
	virtual void sendInventory(bool);
	virtual void Function323();
	virtual void Function324();
	virtual void Function325();
	virtual void Function326();
	virtual void Function327();
	virtual void Function328();
	virtual void Function329();
	virtual void Function330();
	virtual void Function331();
	virtual void Function332();
	virtual void ascendLadder(void);
	virtual void ascendScaffolding(void);
	virtual void descendScaffolding(void);
	virtual void Function336();
	virtual void jumpFromGround(void);
	virtual void Function338();
	virtual void Function339();
	virtual void Function340();
	virtual void Function341();
	virtual void Function342();
	virtual void Function343();
	virtual void Function344();
	virtual void Function345();
	virtual void Function346();
	virtual void Function347();
	virtual void Function348();
	virtual void Function349();
	virtual void Function350();
	virtual void Function351();
	virtual void Function352();
	virtual void Function353();
	virtual void Function354();
	virtual void Function355();
	virtual void Function356();
	virtual void Function357();
	virtual void Function358();
	virtual void Function359();
	virtual void Function360();
	virtual void Function361();
	virtual void Function362();
	virtual void Function363();
	virtual void Function364();
	virtual void Function365();
	virtual void Function366();
	virtual void Function367();
	virtual void Function368();
	virtual void setPermissions(int);
	virtual void startDestroying(void);
	virtual void stopDestroying(void);
	virtual void Function372();
	virtual void Function373();
	virtual void Function374();
	virtual void Function375();
	virtual void Function376();
	virtual void Function377();
	virtual void Function378();
	virtual void Function379();
	virtual void displayTextObjectMessage(class TextHolder*);
	virtual void Function381();
	virtual void Function382();
	virtual void Function383();
	virtual void Function384();
	virtual void Function385();
	virtual void Function386();
	virtual void Function387();
	virtual void Function388();
	virtual void Function389();
	virtual void Function390();
	virtual void Function391();
	virtual void Function392();
	virtual void Function393();
	virtual void Function394();
	virtual void Function395();
	virtual void Function396();
	virtual void Function397();
	virtual void setPlayerGameType(int);
	virtual void Function399();
	virtual void Function400();
	virtual void Function401();
	virtual void Function402();
	virtual void addExperience(int);
	virtual void addLevels(int);
	virtual void Function405();
	virtual void Function406();
	virtual void Function407();
	virtual void Function408();
	virtual void Function409();
	virtual void setFieldOfViewModifier(float);

public:

	Actor* toActor() { return (Actor*)this; };
};