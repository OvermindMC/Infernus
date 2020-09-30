#pragma once
#include "../../Other/VComponent.h"

class HUD : public VModule {
public:
	HUD() : VModule::VModule("HUD", "Heads up display") { this->isEnabled = true; };
	void onRender();
};

void HUD::onRender() {
	LocalPlayer* Player = Minecraft::GetLocalPlayer();
	if (Player != nullptr && Minecraft::GetClientInstance()->MinecraftGame->canUseKeys) {
		Vec2 scaledRes = Minecraft::GetClientInstance()->GuiData()->ScaledResolution;

		Vec3 pos = *Player->getPos();
		std::string coordsStr(std::to_string((int)(pos.x)) + " : " + std::to_string((int)(pos.y)) + " : " + std::to_string((int)(pos.z)));

		float rectangleLength = RenderUtils::GetTextWidth(coordsStr, 1.0f);
		RenderUtils::RenderText(coordsStr, Vec2(0, scaledRes.y - 10), MC_Colour(255, 255, 255), 1.0f, 1.0f);
		RenderUtils::FillRectangle(Vec4(0, scaledRes.y - 10, rectangleLength, scaledRes.y), MC_Colour(50, 50, 50), .3f);
		RenderUtils::FlushText();
	};
};