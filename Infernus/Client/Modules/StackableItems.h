#pragma once
#include "../../Other/VComponent.h"

class StackableItems : public VModule {
public:
	StackableItems() : VModule::VModule("StackableItems", "Stacks Items that you normally cannot stack", 0) {};
	void onGmTick();
private:
	std::chrono::time_point<std::chrono::steady_clock> savedTime = std::chrono::high_resolution_clock::now();
};

void StackableItems::onGmTick() {
	if (std::chrono::duration_cast<std::chrono::seconds>(std::chrono::high_resolution_clock::now() - savedTime) >= std::chrono::milliseconds(500)) {
		if (Minecraft::GetLocalPlayer() != nullptr) {
			LocalPlayer* Player = Minecraft::GetLocalPlayer();
			PlayerInventory* PlayerInv = Player->toActor()->GetInventory();
			Inventory* Inv = PlayerInv->Inventory;

			for (int I = 0; I < 36; I++) {
				ItemStack* CurrStack = Inv->getItem(I);
				if (CurrStack->Item != nullptr) {
					Item* CurrItem = *CurrStack->Item;
					CurrItem->setStackedByData(true);
					CurrItem->setMaxStackSize(64);
				};
			};
		};
		savedTime = std::chrono::high_resolution_clock::now();
	};
};