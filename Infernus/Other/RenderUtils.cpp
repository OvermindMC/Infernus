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