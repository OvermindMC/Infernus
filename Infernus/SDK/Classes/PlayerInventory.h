#pragma once

class InventoryMenu
{
public:
	char pad_0008[56]; //0x0008

	virtual void Function0();
	virtual void Function1();
	virtual void Function2();
	virtual void Function3();
	virtual void Function4();
	virtual void Function5();
	virtual void Function6();
	virtual void setSlot(int, class ItemStack*, bool);
	virtual void Function8();
	virtual void Function9();

public:

}; //Size: 0x0040

class PlayerInventory
{
public:
	char pad_0000[16]; //0x0000
	int HotbarSlot; //0x0010
	char pad_0018[152]; //0x0018
	class Inventory* Inventory; //0x00B0
	char pad_00B8[24]; //0x00B8
}; //Size: 0x00D0

class Inventory
{
public:
	char pad_0008[64]; //0x0008

	virtual void Function0();
	virtual void Function1();
	virtual void Function2();
	virtual void Function3();
	virtual void Function4();
	virtual ItemStack* getItem(int);
	virtual void hasRoomForItem(class ItemStack*);
	virtual void addItem(class ItemStack*);
	virtual void addItemToFirstEmptySlot(class ItemStack*);
	virtual void Function9();
	virtual void Function10();
	virtual void removeItem(int, int);
	virtual void removeAllItems(void);
	virtual void Function13();
	virtual int getContainerSize(void);
	virtual void Function15();
	virtual void Function16();
	virtual void Function17();
	virtual void Function18();
	virtual void Function19();
	virtual int getItemCount(class ItemStack*);
	virtual int findFirstSlotForItem(class ItemStack*);
	virtual void Function22();
	virtual void Function23();
	virtual void Function24();
	virtual void Function25();
	virtual void Function26();
	virtual void Function27();
	virtual void Function28();
	virtual void Function29();
	virtual void CreateTransactionContext(class Inventory*, class ItemStack*);
}; //Size: 0x0048