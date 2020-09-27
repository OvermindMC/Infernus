#pragma once

static uintptr_t addActionAddr = NULL;

class InventoryAction {
public:
	InventoryAction(int slot, class ItemStack* sourceItem, class ItemStack* targetItem, int sourceType = 0, int type = 0) {
		this->slot = slot;
		this->sourceType = 0;
		this->type = type;
		if (sourceItem != nullptr) this->sourceItem = *sourceItem;
		if (targetItem != nullptr) this->targetItem = *targetItem;
	};
public:
	int type;
	int sourceType;
	int unknown;
	int slot;
	ItemStack sourceItem;
	ItemStack targetItem;
};

class InventoryTransactionManager {
public:
	char pad_0000[0x20];

	void addInventoryAction(class InventoryAction const& action) {
		if (addActionAddr != NULL) {
			using _addAction = void(__fastcall*)(InventoryTransactionManager*, InventoryAction const&, bool);
			_addAction addAction = reinterpret_cast<_addAction>(addActionAddr);
			addAction(this, action, false);
		}
		else {
			uintptr_t addActionSigAddr = Utils::FindSignature("40 56 57 41 54 41 56 41 57 48 83 EC 30 48 C7 44 24 ? ? ? ? ? 48 89 5C 24 ? 48 89 6C 24 ? 45 0F B6 F8 4C 8B F2 48 8B F9 48 8B 01 48 8B 88 ? ? ? ?");
			if (addActionSigAddr) {
				addActionAddr = addActionSigAddr;
				using _addAction = void(__fastcall*)(InventoryTransactionManager*, InventoryAction const&, bool);
				_addAction addAction = reinterpret_cast<_addAction>(addActionAddr);
				addAction(this, action, false);
			}
		};
	};
};