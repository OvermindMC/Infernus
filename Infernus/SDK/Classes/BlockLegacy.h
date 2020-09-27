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
	virtual Vec3* GetAABB(void);
	virtual void Function11();
	virtual void Function12();
	virtual void Function13();
	virtual void Function14();
	virtual void Function15();
	virtual void GetLightEmission();
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

	inline BlockLegacy* toLegacy() { return *blockLegacy; }
};

class BlockSource
{
public:
	Block* getBlock(const Vec3_i& block) {
		using getBlock_t = Block * (__fastcall*)(BlockSource*, const Vec3_i&);
		static getBlock_t getBlock = reinterpret_cast<getBlock_t>(Utils::FindSignature("40 53 48 83 EC ?? 48 8B DA 8B 52 ?? 85 D2 ?? ?? 0F BF 41 ?? 3B D0"));
		return getBlock(this, block);
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