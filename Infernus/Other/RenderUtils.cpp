#include "RenderUtils.h"
#include "../SDK/Minecraft.h"

MinecraftUIRenderContext* Context;

void RenderUtils::SetCtx(MinecraftUIRenderContext* Ctx) { Context = Ctx; };
void RenderUtils::FlushText() { Context->flushText(0); };

BitmapFont* RenderUtils::GetFont() { return Minecraft::GetClientInstance()->MinecraftGame->Font1; };
float RenderUtils::GetTextWidth(std::string text, float textSize) { return Context->getLineLength(GetFont(), &TextHolder(text), textSize, false); };

void RenderUtils::RenderText(std::string text, Vec2 position, MC_Colour colour, float textSize, float transparency) {
	static uintptr_t caretMeasureData = 0xFFFFFFFF;
	Vec4 textPos(position.x, position.x + 1000, position.y, position.y + 1000);
	Context->drawText(GetFont(), &textPos, &TextHolder(text), colour, transparency, 0, &textSize, &caretMeasureData);
};

void RenderUtils::FillRectangle(Vec4 position, MC_Colour colour, float alpha) {
	Context->fillRectangle(Vec4(position.x, position.z, position.y, position.w), colour, alpha);
};

void RenderUtils::DrawRectangle(Vec4 position, MC_Colour colour, float alpha, float lineWidth) {
	lineWidth /= 2;
	FillRectangle(Vec4(position.x - lineWidth, position.y - lineWidth, position.z + lineWidth, position.y + lineWidth), colour, alpha);
	FillRectangle(Vec4(position.x - lineWidth, position.y, position.x + lineWidth, position.w), colour, alpha);
	FillRectangle(Vec4(position.z - lineWidth, position.y, position.z + lineWidth, position.w), colour, alpha);
	FillRectangle(Vec4(position.x - lineWidth, position.w - lineWidth, position.z + lineWidth, position.w + lineWidth), colour, alpha);
};

void RenderUtils::DrawNametag(class Actor* Entity, float textSize, class ClientInstance* instance) {
	Vec2 textPos;
	Vec4 rectPos;
	std::string text = Entity->getNameTag()->getText();

	float textWidth = GetTextWidth(text, textSize);
	float textHeight = 10.0f * textSize;

	Vec3 eyePos = Entity->getEyePos().add(0, 0.5f, 0);
	Vec3 origin = instance->GetLevelRenderer()->origin();
	Vec2 scale = instance->GuiData()->ScaledResolution;
	Vec2 fov = instance->getFov();

	glmatrixf* badrefdef = instance->getViewMatrix();
	std::shared_ptr<glmatrixf> matrixPtr = std::shared_ptr<glmatrixf>(badrefdef->correct());

	if (matrixPtr->OWorldToScreen(origin, eyePos, textPos, fov, scale)) {
		textPos.y -= textHeight;
		textPos.x -= textWidth / 2.f;
		RenderText(text, textPos, MC_Colour(255, 255, 255), textSize, 1.0f);

		rectPos.x = textPos.x - 1.f * textSize;
		rectPos.y = textPos.y - 1.f * textSize;
		rectPos.z = textPos.x + textWidth + 1.f * textSize;
		rectPos.w = textPos.y + textHeight + 2.f * textSize;
		Vec4 subRectPos = rectPos;
		subRectPos.y = subRectPos.w - 2.f * textSize;

		FillRectangle(rectPos, MC_Colour(50, 50, 50), 0.7f);
		FillRectangle(subRectPos, MC_Colour(30, 160, 200), 1);
	};
};