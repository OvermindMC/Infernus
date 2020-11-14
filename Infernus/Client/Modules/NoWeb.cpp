#include "NoWeb.h"
#include "../../SDK/Minecraft.h"

void NoWeb::onGmTick() {
	LocalPlayer* Player = Minecraft::GetLocalPlayer();
	if (Player != nullptr) Player->webSlowSpeed = 0.0f;
};