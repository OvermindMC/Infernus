#include "Spider.h"
#include "BunnyHop.h"
#include "../ClientHandler.h"
#include "../../SDK/Minecraft.h"

void Spider::onGmTick() {
	BunnyHop* BhopMod = (BunnyHop*)ClientHandler::GetModule(BunnyHop());
	LocalPlayer* Player = Minecraft::GetLocalPlayer();
	if (Player != nullptr) {
		if (Player->toActor()->isCollidedDir() && BhopMod->usingKeys()) {
			Player->Velocity.y = speed;
		};
	};
};