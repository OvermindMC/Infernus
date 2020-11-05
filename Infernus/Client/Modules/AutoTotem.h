#pragma once
#include "../../Other/VComponent.h"

class AutoTotem : public VModule {
public:
	AutoTotem() : VModule::VModule("AutoTotem", "Automatically equip totems in your second hand") {};
	void onGmTick();
private:
	int delay = 0;
};

void AutoTotem::onGmTick() {
	LocalPlayer* Player = Minecraft::GetLocalPlayer();
	if (Player != nullptr && Minecraft::GetClientInstance()->MinecraftGame->canUseKeys) {
		PlayerInventory* PlayerInv = Player->toActor()->GetInventory();
		Inventory* Inv = PlayerInv->Inventory;
		InventoryTransactionManager* manager = Player->toActor()->GetTransactionManager();
		ItemStack* current = Player->getEquippedTotem();
		if (current->Item == nullptr) {
			for (int I = 0; I < 36; I++) {
				ItemStack* totem = Inv->getItem(I);
				if (totem->Item != nullptr && (*totem->Item)->itemID == 450) {
					InventoryAction first(I, totem, nullptr);
					InventoryAction second(37, nullptr, totem);
					Player->setOffHandSlot(totem);
					Inv->removeItem(I, I);
					manager->addInventoryAction(first);
					manager->addInventoryAction(second);
					//I = 36; //Stop loop
				};
			};
		};
	};
};