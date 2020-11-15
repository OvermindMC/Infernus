#pragma once
#include "../../Other/VComponent.h"

class Scaffold : public VModule {
public:
	Scaffold() : VModule::VModule("Scaffold", "Automatically place blocks below you") {};
	void onGmTick();
	bool tryBuild(Vec3);
};

void Scaffold::onGmTick() {
	if (Minecraft::GetLocalPlayer() == nullptr)
		return;
	if (!Minecraft::GetClientInstance()->MinecraftGame->canUseKeys)
		return;

	LocalPlayer* Player = Minecraft::GetLocalPlayer();
	ItemStack* heldItem = Player->getSelectedItem();

	if (heldItem == nullptr || heldItem->Item == nullptr || heldItem->StackCount == 0 || !(*heldItem->Item)->isBlock())
		return;

	Vec3 blockBelow = *Player->getPos();
	blockBelow.y -= Player->Collision.y;
	blockBelow.y -= 0.5f;

	float speed = Player->Velocity.magnitudexz();
	Vec3 vel = Player->Velocity;
	vel = vel.normalize();

	if (!tryBuild(blockBelow)) {
		if (speed > 0.05f) {
			blockBelow.z -= vel.z * 0.4f;
			if (!tryBuild(blockBelow)) {
				blockBelow.x -= vel.x * 0.4f;
				if (!tryBuild(blockBelow) && Player->isSprinting()) {
					blockBelow.z += vel.z;
					blockBelow.x += vel.x;
					tryBuild(blockBelow);
				};
			};
		};
	};
};

bool Scaffold::tryBuild(Vec3 blockPos) {
	LocalPlayer* Player = Minecraft::GetLocalPlayer();
	blockPos = blockPos.floor();

	Block* block = Player->BlockSource->getBlock(Vec3_i(blockPos));
	BlockLegacy* legacy = block->toLegacy();

	if (legacy->Material->isReplaceable) {
		Vec3_i blok(blockPos);

		static std::vector<Vec3_i*> checkList;
		if (checkList.empty()) {
			checkList.push_back(new Vec3_i(0, -1, 0));
			checkList.push_back(new Vec3_i(0, 1, 0));

			checkList.push_back(new Vec3_i(0, 0, -1));
			checkList.push_back(new Vec3_i(0, 0, 1));

			checkList.push_back(new Vec3_i(-1, 0, 0));
			checkList.push_back(new Vec3_i(1, 0, 0));
		};
		bool foundBlock = false;
		int I = 0;

		for (auto current : checkList) {
			Vec3_i calc = blok.sub(*current);
			if (!(*Player->BlockSource->getBlock(calc)->blockLegacy)->Material->isReplaceable) {
				foundBlock = true;
				blok = calc;
				break;
			};
			I++;
		};

		if (foundBlock) {
			Minecraft::GetGameMode()->buildBlock(&blok, I);
			Player->swing();
			return true;
		};
	};
	return false;
};