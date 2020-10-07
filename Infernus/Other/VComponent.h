#pragma once
#include "Utils.h"

class VModule {
public:
	std::string name, description;
	uint64_t key;
	bool isEnabled = false, wasEnabled = false;
	VModule(std::string name, std::string description, uint64_t key = NULL) { this->name = name, this->description = description; this->key = key; };

	std::vector<class VWindowObj*> WindowObjects;

	void addWindowObj(VWindowObj* Obj) {
		this->WindowObjects.push_back(Obj);
	};

	/* Events */
	virtual void onLoop(); //For ticking each module and handling the onEnable & onDisable events
	virtual void onTick();
	virtual void onEnable();
	virtual void onDisable();

	virtual void onMouse(char, bool) {};
	virtual void onMouseMove() {};

	virtual void EnabledCall(VModule*) {};
	virtual void DisabledCall(VModule*) {};

	/* Events handled by hooks */
	virtual void onGmTick() {};
	virtual void onRender() {};
	virtual void onKey(uint64_t WinKey, bool isDown) {};

	virtual void onLerpMotion(Vec3* velocity) {};
	virtual void onJump(float*) {};
	virtual void onEntityTick(std::vector<class Actor*>*) {};
	virtual void onSpeed(float*) {};

	virtual void onDestroyBlock(class GameMode*, Vec3_i*, uint8_t) {};

	virtual void onPacket(void*, enum class PacketType, bool*) {};

	/* VWindow Stuff */
	virtual void onVButtonClick(VWindowObj*) {};
};

class VHook {
public:
	virtual void Init() {};
};

/* Virtual Object Events */

class VCategory {
public:
	std::string name;
	std::vector<VModule*> modules;
	VCategory(std::string name) { this->name = name; };
};

#include "RenderUtils.h"
#include <functional>

class VWindowObj {
public:

	int objType = 0;
	Vec4 position; //Gets updated by VWindow

	/* All */
	std::string text;
	float textAlpha;
	MC_Colour textColour;

	/* Button */
	float backgroundAlpha;
	MC_Colour backgroundColour;
	bool* toggleState;
	bool hoveringOver = false;

	/* VModule Button */
	VModule* Module;
	bool expandedItems = false;

	/* Slider */
	float* value;
	float min, max;
	float drawnWidth;
	bool dragging = false;

	bool contains(float pX, float pY) {
		return position.x < pX && position.y < pY && position.z > pX && position.w > pY;
	};

	void initData() {
		this->textCopy = this->text;
		this->textAlphaCopy = textAlpha;
		this->backgroundAlphaCopy = backgroundAlpha;
		this->textColourCopy = textColourCopy;
		this->backgroundColourCopy = backgroundColour;
	};

	std::string textCopy;
	float textAlphaCopy;
	float backgroundAlphaCopy;
	MC_Colour textColourCopy;
	MC_Colour backgroundColourCopy;

	void toggleButtonState() {
		if (objType == 2) {
			if (*toggleState) {
				*toggleState = false;
			}
			else {
				*toggleState = true;
			};
		};
		return;
	};

	void updateSlider() {
		std::ostringstream ss;
		ss << *value;
		text = std::string(ss.str());

		if (*value <= min) {
			*value = min;
		}
		else if (*value >= max) *value = max;

		if (*value + 0.2f >= max) *value = max;
		if (*value - 0.2f <= min) *value = min;

		drawnWidth = ((*value + std::abs(min))) / getPixelValue();
	};

	float getPixelValue() {
		float div = std::abs(min) + std::abs(max);
		return div / (position.z - position.x);
	};
};

class VWindowText : public VWindowObj {
public:
	VWindowText(std::string text, MC_Colour colour = MC_Colour(255, 255, 255), float textAlpha = 1.0f) {
		this->text = text;
		this->textColour = colour;
		this->textAlpha = textAlpha;
		this->objType = 1; //Text
		this->initData();
	};
};

class VWindowButton : public VWindowObj {
public:
	VWindowButton(std::string text, bool* toggle = (bool*)false, MC_Colour textColour = MC_Colour(255, 255, 255), MC_Colour backgroundColour = MC_Colour(180, 180, 180), float textAlpha = 1.0f, float backgroundAlpha = 1.0f) {
		this->text = text;
		this->toggleState = toggle;
		this->textAlpha = textAlpha;
		this->textColour = textColour;
		this->backgroundColour = backgroundColour;
		this->textAlpha = textAlpha;
		this->backgroundAlpha = backgroundAlpha;
		this->objType = 2; //Button
		this->initData();
	};
};

class VWindowButtonModule : public VWindowObj {
public:
	VWindowButtonModule(VModule* Module, MC_Colour colour = MC_Colour(255, 255, 255), MC_Colour backgroundColour = MC_Colour(180, 180, 180), float textAlpha = 1.0f, float backgroundAlpha = 1.0f) {
		this->Module = Module;
		this->textColour = colour;
		this->textAlpha = textAlpha;
		this->backgroundColour = backgroundColour;
		this->backgroundAlpha = backgroundAlpha;
		this->objType = 3; //Module Button
		this->initData();
	};
};

class VWindowSlider : public VWindowObj {
public:
	VWindowSlider(float* value = 0, float min = 0.0f, float max = 10.0f) {
		this->value = value;
		this->text = std::to_string(*value);
		this->min = min, this->max = max;
		this->textColour = MC_Colour(255, 255, 255);
		this->textAlpha = 1.0f;
		this->objType = 4; //Slider
		this->initData();
	};
};

class VWindow {
public:
	static std::vector<VWindow*> FetchWindows();

	std::string name;
	Vec4 position;
	Vec2 scale;
	MC_Colour backgroundColour;
	MC_Colour textColour;
	float backgroundTransparency;
	float textTransparency;
	bool isHidden;
	bool isHoveringOver = false;
	bool isBeingDragged = false;
	bool canBeDragged = true;
	MC_Colour windowTitleBarColour;

	std::vector<VWindowObj*> WindowObjects;
	std::chrono::time_point<std::chrono::steady_clock> lastTicked;

	VWindow(std::string name, Vec4 position, MC_Colour backgroundColour = MC_Colour(120, 120, 120), MC_Colour textColour = MC_Colour(255, 255, 255), float backgroundAlpha = 1.0f, float textAlpha = 1.0f, bool isHidden = false, bool canDrag = true) {
		this->name = name;
		this->position = position;
		this->scale = Vec2((position.z - position.x), (position.w - position.y));
		this->backgroundColour = backgroundColour;
		this->textColour = textColour;
		this->backgroundTransparency = backgroundAlpha;
		this->textTransparency = textAlpha;
		this->isHidden = isHidden;
		this->canBeDragged = canDrag;
		this->windowTitleBarColour = MC_Colour(120, 160, 255);
	};

	void setPosition(Vec2);
	void Render();
	void addObject(VWindowObj* object);
	bool withinWindow(float pX, float pY);
	bool withinWindowBar(float pX, float pY);
	bool hoveringOverTitleBar();
	static short getMouseX();
	static short getMouseY();
	bool renderedRecently();
};