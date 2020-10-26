#pragma once
#include "../../Other/VComponent.h"

class Jesus : public VModule {
public:
	Jesus() : VModule::VModule("Jesus", "Hover above water") {};
	void onGmTick();
};

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