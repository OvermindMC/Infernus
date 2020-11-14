#include "WarpSpeed.h"
#include "../ClientHandler.h"
#include "../../SDK/Minecraft.h"

void WarpSpeed::onGmTick() {
	LocalPlayer* Player = Minecraft::GetLocalPlayer();
	if (Bhop != nullptr && Player != nullptr && Minecraft::GetClientInstance()->MinecraftGame->canUseKeys) {
		float calcYaw = Bhop->calcYawFromKeys();
		if (calcYaw && Bhop->usingKeys()) {
			Vec3 playerVel = Vec3(cos((calcYaw) * (PI / 180.0f)) * speed, 0.f, sin((calcYaw) * (PI / 180.0f)) * speed);
			Vec3 currPos = *Player->getPos();
			Vec3 blockPos = Vec3(currPos.x + playerVel.x * 1.0f, currPos.y, currPos.z + playerVel.z * 1.0f);
			if (!isColliding(blockPos)) {
				runTask(Player, blockPos);
			};
		};
	};
};

void WarpSpeed::onLoop() {
	if (Bhop == nullptr) {
		Bhop = (BunnyHop*)ClientHandler::GetModule(BunnyHop());
	};
};

bool WarpSpeed::isColliding(Vec3 blockPos) {
	LocalPlayer* Player = Minecraft::GetLocalPlayer();
	blockPos = blockPos.floor();
	std::vector<int> inFrontBlocks = { 0 /*Air*/, 30 /*Cobweb*/, 31 /*Tall Grass */, 50 /*Torch*/, 63 /*Sign*/, 90 /*Portal*/, 106 /*Vine*/, 175 /*Double Plant*/, 486 /*Weeping Vines*/, 542 /*Twisted Vines*/, 542 /*Twisted Vines*/ };
	std::vector<int> belowBlocks = { 0 /*Air*/, 6 /*Sappling*/, 27 /*Golden Rail*/, 28 /*Detector Rail*/, 30 /*Cobweb*/, 31 /*Tall Grass */, 32 /*Dead Bush*/, 37 /*Yellow Flower*/, 38 /*Red Flower*/, 39 /*Brown Mushroom*/, 40 /*Red Mushroom*/, 50 /*Torch*/, 51 /*Fire*/, 55 /*Redstone Wire*/, 59 /*Wheat*/, 63 /*Sign*/, 65 /*Ladder*/, 66 /*Rail*/, 68 /*Wall Sign*/, 69 /*Lever*/, 70 /*Stone Pressure Plate*/, 72 /*Wooden Pressure Plate*/, 75 /*Unlit Redstone Torch*/, 76 /*Lit Redstone Torch*/, 77 /*Stone Button*/, 78 /*Snow Layer*/, 83 /*Reeds*/, 90 /*Portal*/, 104 /*Pumpkin Stem*/, 105 /*Melon Stem*/, 106 /*Vine*/, 119 /*End Portal*/, 126 /*Activator Rail*/, 143 /*Wooden Button*/, 147 /*Golden Pressure Plate*/, 148 /*Iron Pressure Plate*/, 171 /*Carpet*/, 175 /*Double Plant*/, 385 /*Sea Grass*/, 386 /*Coral*/, 388 /*Coral Fan*/, 389 /*Coral Fan Dead*/, 393 /*Kelp*/, 395 /*Acacia Button*/, 396 /*Birch Button*/, 397 /*Dark Oak Button*/, 398 /*Jungle Button*/, 399 /*Spruce Button*/, 462 /*Sweet Berry Bush*/, 478 /*Crimson Roots*/, 479 /*Warped Roots*/, 483 /*Crimson Fungus*/, 484 /*Warped Fungus*/, 486 /*Weeping Vines*/, 492 /*Soul Fire*/, 493 /*Nether Sprouts*/, 505 /*Crimson Sign*/, 506 /*Warped Sign*/, 507 /*Crimson Wall Sign*/, 508 /*Warped Wall Sign*/, 515 /*Crimson Button*/, 516 /*Warped Button*/, 517 /*Crimson Pressure Plate*/, 518 /*Warped Pressure Plate*/, 523 /*Soul Torch*/, 542 /*Twisted Vines*/, 550 /*Polished Pressure Plate*/ };
	if (Player != nullptr) {
		Vec3 currPos = *Player->getPos();
		Block* block = Player->BlockSource->getBlock(Vec3(blockPos.x, currPos.y - 1.0f, blockPos.z));
		int blockID = block->toLegacy()->blockID;

		bool colliding = true;

		for (auto ID : belowBlocks) { //Check just below head
			if (blockID == ID) {
				colliding = false;
				break;
			};
		};

		if (!colliding) {
			Block* block = Player->BlockSource->getBlock(blockPos);
			int blockID = block->toLegacy()->blockID;

			for (auto ID : inFrontBlocks) { //Check at head position
				if (blockID == ID) {
					colliding = false;
					break;
				};
			};
		};
		return colliding;
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
	Player->setPos(&blockPos);

	if (sendPackets) {
		this->sendPacket(blockPos);
	};
};