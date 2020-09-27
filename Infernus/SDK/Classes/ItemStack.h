#pragma once

class ItemStack
{
public:
	char pad_0000[8]; //0x0000
	class Item** Item; //0x0008
	char pad_0010[18]; //0x0010
	INT8 StackCount; //0x0022
	char pad_002A[226]; //0x002A
}; //Size: 0x010C

class Item
{
public:
	char pad_0008[98]; //0x0008
	uint16_t itemID; //0x006A
	char pad_006C[4]; //0x006C
	TextHolder tileName; //0x0070
	char pad_0078[132]; //0x0078
	int64_t duration; //0x00FC
	char pad_0104[20]; //0x0104

	virtual void Function0();
	virtual void Function1();
	virtual void Function2();
	virtual void Function3();
	virtual void Function4();
	virtual void Function5();
	virtual void setMaxStackSize(UCHAR);
	virtual void setCategory(int);
	virtual void setStackedByData(bool);
	virtual void Function9();
	virtual void setHandEquipped(void);
	virtual void Function11();
	virtual void setMaxUseDuration(int);
	virtual void Function13();
	virtual void Function14();
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
	virtual bool isHandEquipped(void);

public:

	bool isBlock() {
		auto val = *reinterpret_cast<__int64***>(reinterpret_cast<__int64>(this) + 0x170);
		return val != nullptr && *val != nullptr;
	};

}; //Size: 0x00E0