#include "HUD.h"
#include "../../SDK/Minecraft.h"

void HUD::onRender() {
	LocalPlayer* Player = Minecraft::GetLocalPlayer();
	if (Player != nullptr && Minecraft::GetClientInstance()->MinecraftGame->canUseKeys) {
		Vec2 scaledRes = Minecraft::GetClientInstance()->GuiData()->ScaledResolution;

		Vec3 pos = *Player->getPos();
		std::string coordsStr(std::to_string((int)(pos.x)) + " : " + std::to_string((int)(pos.y)) + " : " + std::to_string((int)(pos.z)));

		float rectangleLength = RenderUtils::GetTextWidth(coordsStr, 1.0f);
		RenderUtils::RenderText(coordsStr, Vec2(0, scaledRes.y - 10), MC_Colour(255, 255, 255), 1.0f, 1.0f);
		RenderUtils::FillRectangle(Vec4(0, scaledRes.y - 10, rectangleLength, scaledRes.y), MC_Colour(50, 50, 50), .3f);
		rectangleLength = RenderUtils::GetTextWidth(Player->getNameTag()->getText(), 1.0f);
		RenderUtils::RenderText(Player->getNameTag()->getText(), Vec2(0, scaledRes.y - 20), MC_Colour(255, 255, 255), 1.0f, 1.0f);
		RenderUtils::FillRectangle(Vec4(0, scaledRes.y - 20, rectangleLength, scaledRes.y - 10), MC_Colour(50, 50, 50), .3f);

		RenderUtils::FlushText();
	};
};