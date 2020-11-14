#include "StackableItems.h"
#include "../../SDK/Minecraft.h"

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