#pragma once

class BlockLegacy
{
public:
	class TextHolder* tileName; //0x0008
	char pad_0010[176]; //0x0010
	class Material* Material; //0x00C0
	char pad_00C8[68]; //0x00C8
	int blockID; //0x010C
	char pad_0110[12]; //0x0110

	virtual void Function0();
	virtual void Function1();
	virtual void Function2();
	virtual void Function3();
	virtual void Function4();
	virtual void Function5();
	virtual bool isObstructingChests(void);
	virtual void Function7();
	virtual void Function8();
	virtual void Function9();
	virtual AABB* GetAABB(void);
	virtual void Function11();
	virtual void Function12();
	virtual void Function13();
	virtual void Function14();
	virtual void Function15();
	virtual __int8* GetLightEmission();
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
	virtual void Function51();
	virtual void Function52();
	virtual void Function53();
	virtual void Function54();
	virtual void Function55();
	virtual void Function56();
	virtual void Function57();
	virtual void Function58();
	virtual void Function59();
	virtual void Function60();
	virtual void Function61();
	virtual void Function62();
	virtual void Function63();
	virtual void Function64();
	virtual void Function65();
	virtual void Function66();
	virtual void Function67();
	virtual void Function68();
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
	virtual void Function85();
	virtual void Function86();
	virtual void Function87();
	virtual void Function88();
	virtual void Function89();
	virtual void Function90();
	virtual void Function91();
	virtual void Function92();
	virtual void Function93();
	virtual void Function94();
	virtual void Function95();
	virtual void Function96();
	virtual void Function97();
	virtual void Function98();
	virtual void Function99();
	virtual void Function100();
	virtual void Function101();
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
	virtual void Function123();
	virtual void Function124();
	virtual int GetRenderLayer(void);
	virtual void Function126();
	virtual void Function127();
	virtual void Function128();
	virtual void Function129();
	virtual void Function130();
public:
	class TextHolder* name() {
		return *reinterpret_cast<class TextHolder**>(reinterpret_cast<__int64>(this) + 0x28);
	};

	void Init() {
		using InitBlock = void* (__fastcall*)(BlockLegacy*);
		static InitBlock _Init = reinterpret_cast<InitBlock>(Utils::FindSignature("0F 57 C0 0F 2F 81 ? ? ? ? 76 10 48 8B 81 ? ? ? ? 8B 50 0C 89 91 ? ? ? ? "));
		_Init(this);
	};

	AABB BlockAABB() {
		uintptr_t _this = reinterpret_cast<uintptr_t>(this);
		return *(AABB*)(_this + 0x118);
	};
}; //Size: 0x0011C

class Block
{
private:
	uintptr_t** vtable;
public:
	uint8_t data;
private:
	char pad[0x7];
public:
	BlockLegacy** blockLegacy;

	inline BlockLegacy* toLegacy() { return *blockLegacy; };
};

class BlockSource
{
public:
	Block* getBlock(const Vec3_i& block) {
		using getBlock_t = Block * (__fastcall*)(BlockSource*, const Vec3_i&);
		static getBlock_t getBlock = reinterpret_cast<getBlock_t>(Utils::FindSignature("40 53 48 83 EC ?? 48 8B DA 8B 52 ?? 85 D2 ?? ?? 0F BF 41 ?? 3B D0"));
		return getBlock(this, block);
	};

	void updateNeighboursAt(const Vec3_i& block) {
		using UpdateNeighbours = void* (__fastcall*)(BlockSource*, const Vec3_i&);
		static UpdateNeighbours updateNeighbours = reinterpret_cast<UpdateNeighbours>(Utils::FindSignature("48 89 5C 24 ? 48 89 7C 24 ? 55 48 8B EC 48 83 EC 30 8B 02 48 8B DA FF C8 4C 8B C2 89 45 F0 48 8B F9 8B 42 04 89 45 F4"));
		updateNeighbours(this, block);
	};
};

class Material
{
public:
	char pad[0x4];
	bool isFlammable;
	bool isNeverBuildable;
	bool isAlwaysDestroyable;
	bool isReplaceable;
};