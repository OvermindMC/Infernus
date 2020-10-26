#pragma once
#include "../../Other/VComponent.h"

class BunnyHop : public VModule {
public:
	BunnyHop() : VModule::VModule("Bunny-Hop", "Automatically jump around like a bunny") {
		this->addWindowObj(new VWindowSlider(&this->speed, 0, 5.0f, "Speed: ", MC_Colour(255, 255, 255), 1.0f, 1.0f, MC_Colour(255, 110, 30), .7f));
	};
	void onGmTick();
	void updateKeys();
	float calcYawFromKeys();
	Vec2 yawToVelocity(float);
	void multiplyBy(Vec2*, float);
	bool usingKeys();
public:
	float speed = 0.4f;
	bool wKey = 0, sKey = 0, aKey = 0, dKey = 0;
};

void BunnyHop::onGmTick() {
	LocalPlayer* Player = Minecraft::GetLocalPlayer();
	if (Player != nullptr && Minecraft::GetClientInstance()->MinecraftGame->canUseKeys) {
		float velocity = calcYawFromKeys();
		if (velocity && usingKeys()) {
			Vec2 currVel = yawToVelocity(velocity);
			multiplyBy(&currVel, speed);
			Player->Velocity = Vec3(currVel.x, Player->Velocity.y, currVel.y);
			if (Player->onGround && !Player->isJumping()) {
				Player->jumpFromGround();
			};
		};
	};
};

void BunnyHop::updateKeys() {
	wKey = Utils::usingKey(0x57);
	sKey = Utils::usingKey(0x53);
	aKey = Utils::usingKey(0x41);
	dKey = Utils::usingKey(0x44);
};

float BunnyHop::calcYawFromKeys() {
	LocalPlayer* Player = Minecraft::GetLocalPlayer();
	if (Player != nullptr) {
		this->updateKeys();
		float calcYaw = Player->lookingVector.y;
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
		};
		return calcYaw;
	};
	return 0.0f;
};

Vec2 BunnyHop::yawToVelocity(float yaw) {
	return Vec2(cos((yaw) * (PI / 180.0f)), sin((yaw) * (PI / 180.0f)));
};

void BunnyHop::multiplyBy(Vec2* vec, float mult) {
	vec = &Vec2(vec->x *= mult, vec->y *= mult);
};

bool BunnyHop::usingKeys() {
	this->updateKeys();
	return (bool)(wKey || sKey || aKey || dKey);
};