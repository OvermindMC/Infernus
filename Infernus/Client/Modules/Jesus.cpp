#include "Jesus.h"
#include "../../SDK/Minecraft.h"

void Jesus::onGmTick() {
	LocalPlayer* Player = Minecraft::GetLocalPlayer();
	if (Player != nullptr) {
		if (Player->isInWater()) {
			if (Player->toActor()->isCollidedDir()) {
				Player->Velocity.y = 0.3f;
			}
			else {
				Player->Velocity.y = 0.15f;
			};
		};
	};
};