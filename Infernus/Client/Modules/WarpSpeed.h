#pragma once
#include "../../Other/VComponent.h"
#include "BunnyHop.h"

class WarpSpeed : public VModule {
public:
	WarpSpeed() : VModule::VModule("WarpSpeed", "Warp forward", 0x43) {
		this->addWindowObj(new VWindowSlider(&speed, 0, 5.0f, "Speed: ", MC_Colour(255, 255, 255), 1.0f, 1.0f, MC_Colour(255, 110, 30), .7f));
		this->addWindowObj(new VWindowButton("On Ground", &onGround));
		this->addWindowObj(new VWindowButton("Send Packets", &sendPackets));
	};
	void onGmTick();
	void onLoop();
	bool isColliding(Vec3);
	void sendPacket(Vec3);
	void runTask(LocalPlayer*, Vec3);
private:
	float speed = .25f;
	bool sendPackets = true;
	bool onGround = false;
	BunnyHop* Bhop;
};

void WarpSpeed::onGmTick() {
	LocalPlayer* Player = Minecraft::GetLocalPlayer();
	if (Bhop != nullptr && Player != nullptr && Minecraft::GetClientInstance()->MinecraftGame->canUseKeys) {
		float calcYaw = Bhop->calcYawFromKeys();
		if (calcYaw && Bhop->usingKeys()) {
			Vec3 playerVel = Vec3(cos((calcYaw) * (PI / 180.0f)) * speed, 0.f, sin((calcYaw) * (PI / 180.0f)) * speed);
			Vec3 currPos = *Player->getPos();
			Vec3 blockPos = Vec3(currPos.x + playerVel.x * 1.0f, currPos.y, currPos.z + playerVel.z * 1.0f);
			if (!isColliding(blockPos)) {
				if (onGround) {
					if (Player->onGround) {
						runTask(Player, blockPos);
					};
				}
				else {
					runTask(Player, blockPos);
				};
			};
		};
	};
};

void WarpSpeed::onLoop() {
	if (Bhop == nullptr) Bhop = (BunnyHop*)ClientHandler::GetModule(BunnyHop());
};

bool WarpSpeed::isColliding(Vec3 blockPos) {
	LocalPlayer* Player = Minecraft::GetLocalPlayer();
	if (Player != nullptr) {
		Vec3 currPos = *Player->getPos();
		Block* block = Player->BlockSource->getBlock(Vec3(blockPos.x, currPos.y - 1.0f, blockPos.z));
		if (block->toLegacy()->blockID > 0) {
			return true;
		}
		else {
			block = Player->BlockSource->getBlock(blockPos);
			return block->toLegacy()->blockID > 0;
		};
	};
	return false;
};

void WarpSpeed::sendPacket(Vec3 blockPos) {
	LocalPlayer* Player = Minecraft::GetLocalPlayer();
	if (Player != nullptr) {
		MovePlayerPacket newMovePacket = MovePlayerPacket(Player->toActor(), blockPos, Player->lookingVector, Player->onGround);
		PlayerAuthInputPacket newAuthPacket = PlayerAuthInputPacket(Player->lookingVector, blockPos);
		Minecraft::GetClientInstance()->LoopbackPacketSender->sendToServer(&newMovePacket);
		Minecraft::GetClientInstance()->LoopbackPacketSender->sendToServer(&newAuthPacket);
	};
};

void WarpSpeed::runTask(LocalPlayer* Player, Vec3 blockPos) {
	if (sendPackets) sendPacket(blockPos);
	Player->setPos(&blockPos);
};