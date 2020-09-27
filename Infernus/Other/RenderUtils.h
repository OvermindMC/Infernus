#pragma once
#include "Utils.h"

struct MC_Colour {
	union {
		struct {
			float r, g, b, a;
		};
		float arr[4];
	};
	bool shouldDelete = true;

	MC_Colour() {
		this->r = 1;
		this->g = 1;
		this->b = 1;
		this->a = 1;
	};

	MC_Colour(const MC_Colour& other) {
		this->r = other.r;
		this->g = other.g;
		this->b = other.b;
		this->a = other.a;
		this->shouldDelete = other.shouldDelete;
	}

	MC_Colour(const float* arr) {
		this->arr[0] = arr[0];
		this->arr[1] = arr[1];
		this->arr[2] = arr[2];
		this->arr[3] = arr[3];
	};

	MC_Colour(const float r, const float g, const float b, const float a = 1) {
		this->r = r;
		this->g = g;
		this->b = b;
		this->a = a;
	};

	MC_Colour(const int r, const int g, const int b, const int a = 255) {
		this->r = r / 255.0f;
		this->g = g / 255.0f;
		this->b = b / 255.0f;
		this->a = a / 255.0f;
	};

	MC_Colour(const float r, const float g, const float b, const float a, const bool shouldDelete) {
		this->r = r;
		this->g = g;
		this->b = b;
		this->a = a;
		this->shouldDelete = shouldDelete;
	};

	bool operator == (MC_Colour colour) {
		return this->r == colour.r && this->g == colour.g && this->b == colour.b;
	};

	bool operator != (MC_Colour colour) {
		return this->r != colour.r || this->g != colour.g || this->b != colour.b;
	};
};

class RenderUtils {
public:
	static void SetCtx(class MinecraftUIRenderContext* Ctx);
	static void FlushText();
	static class BitmapFont* GetFont();
	static float GetTextWidth(std::string text, float textSize);
	static void RenderText(std::string text, Vec2 position, MC_Colour colour, float textSize, float transparency);
	static void FillRectangle(Vec4 position, MC_Colour colour, float alpha);
	static void DrawRectangle(Vec4 position, MC_Colour colour, float alpha, float lineWidth);
};