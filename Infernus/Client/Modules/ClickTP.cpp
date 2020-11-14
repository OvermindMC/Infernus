#include "ClickTP.h"
#include "../../SDK/Minecraft.h"

void ClickTP::onMouse(char action, bool isDown) {
	if (action == 2 && isDown) {
		LocalPlayer* Player = Minecraft::GetLocalPlayer();
		if (Player != nullptr && Minecraft::GetClientInstance()->MinecraftGame->canUseKeys) {
			Vec3_i staringPos = Player->MultiPlayerLevel->facingBlockPos();
			if (staringPos.y > 0) {
				Player->setPos(&Vec3(staringPos.x + 0.5, staringPos.y + 3, staringPos.z + 0.5));
			};
		};
	};
};