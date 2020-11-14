#include "Jetpack.h"
#include "../../SDK/Minecraft.h"

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