#pragma once
#include "../../Other/VComponent.h"

class Jetpack : public VModule {
public:
	Jetpack() : VModule::VModule("Jetpack", "Boost directly forward when holding the F key", 0x46) {};
	void onGmTick();

	float speed = 1.0f;
};

void Jetpack::onGmTick() {
	LocalPlayer* Player = Minecraft::GetLocalPlayer();

	if (Player != nullptr) {
		if (Minecraft::GetClientInstance()->MinecraftGame->canUseKeys) {
			if (Utils::usingKey(this->key)) {
				Vec2 looking = Player->lookingVector;
				Vec2 calcAngles((looking.x) * -(PI / 180.0f), (looking.y + 90.0f) * (PI / 180.0f));
				Player->Velocity = Vec3(cos(calcAngles.y) * cos(calcAngles.x) * speed, sin(calcAngles.x) * speed, sin(calcAngles.y) * cos(calcAngles.x) * speed);
			}
			else {
				this->isEnabled = false;
			};
		}
		else {
			this->isEnabled = false;
		};
	}
	else {
		this->isEnabled = false;
	};
};