#pragma once
#include "../../Other/VComponent.h"

class Speed : public VModule {
public:
	Speed() : VModule::VModule("Speed", "Move faster than others") {};
	void onGmTick();
public:
	float speed = 0.6f;
};

void Speed::onGmTick() {
	LocalPlayer* Player = Minecraft::GetLocalPlayer();
	if (Player != nullptr && Minecraft::GetClientInstance()->MinecraftGame->canUseKeys) {
		float calcYaw = Player->lookingVector.y;
		bool wKey = Utils::usingKey(0x57), sKey = Utils::usingKey(0x53), aKey = Utils::usingKey(0x41), dKey = Utils::usingKey(0x44);

		if (wKey || sKey || aKey || dKey) {
			if (wKey) {
				if (!aKey && !dKey) {
					calcYaw += 90.0f;
				}
				else if (aKey) {
					calcYaw += 45.0f;
				}
				else if (dKey) {
					calcYaw += 135.0f;
				};
			}
			else if (sKey) {
				if (!aKey && !dKey) {
					calcYaw -= 90.0f;
				}
				else if (aKey) {
					calcYaw -= 45.0f;
				}
				else if (dKey) {
					calcYaw -= 135.0f;
				};
			}
			else if (!wKey && !sKey) {
				if (dKey) calcYaw -= 180.0f;
			};

			Player->Velocity.x = cos((calcYaw) * (PI / 180.0f)) * speed;
			Player->Velocity.z = sin((calcYaw) * (PI / 180.0f)) * speed;
		};
	};
};