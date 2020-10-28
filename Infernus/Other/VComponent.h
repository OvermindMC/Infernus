#pragma once
#include "Utils.h"
#include "RenderUtils.h"
#include <functional>

class VModule {
public:
	std::string name, description;
	uint64_t key;
	bool isEnabled = false, wasEnabled = false;
	VModule(std::string name, std::string description, uint64_t key = NULL) { this->name = name, this->description = description; this->key = key; };

	std::vector<class VWindowObject*> WindowObjects;

	void addWindowObj(VWindowObject* Obj) {
		this->WindowObjects.push_back(Obj);
	};

	/* Events */
	virtual void onLoop(); //For ticking each module and handling the onEnable & onDisable events
	virtual void onTick();
	virtual void onEnable() {};
	virtual void onDisable() {};

	virtual void onMouse(char, bool) {};
	virtual void onMouseMove() {};

	/* Events handled by hooks */
	virtual void onGmTick() {};
	virtual void onRender() {};
	virtual void onKey(uint64_t WinKey, bool isDown, bool* cancel) {};

	virtual void onLerpMotion(Vec3* velocity) {};
	virtual void onJump(float*) {};
	virtual void onEntityTick(std::vector<class Actor*>*) {};
	virtual void onSpeed(float*) {};

	virtual void onDestroyBlock(class GameMode*, Vec3_i*, uint8_t) {};
	virtual void onAttack(class Actor*, class Actor*) {};

	virtual void onPacket(void*, enum class PacketType, bool*) {};

	/* VWindow Stuff */
	virtual void onVButtonClick(VWindowObject*) {};
};

class VCommand {
public:
	std::string input, description;
	VCommand(std::string input, std::string description) { this->input = input, this->description = description; };

	virtual void execute(std::string input, std::vector<std::string> words) {};
	virtual void reply(std::string);
	virtual void emptyReply() { this->reply("\n"); };
};

class VHook {
public:
	virtual void Init() {};
};

class VCategory {
public:
	std::string name;
	std::vector<VModule*> modules;
	VCategory(std::string name) { this->name = name; };
};

/* Virtual Object Stuff */

enum class VObjectType {
	Text,
	Button,
	Slider,
	Unknown
};

class VWindowObject {
private:
	std::string textC;
	float textAlphaC, backgroundAlphaC;
	MC_Colour textColourC, backgroundColourC;
public:
	std::string text;
	Vec4 position;
	float textSize, textAlpha, backgroundAlpha;
	MC_Colour textColour, backgroundColour, enabledColour;
	bool* toggleState;
	bool hoveringOver = false;
	bool expandedItems = false;

	float* value;
	float min, max, drawnWidth;
	bool draggingSlider = false;
	std::string sliderText;

	VObjectType type;
	std::vector<VWindowObject*> objects;

	void InitData() {
		this->textC = text;
		this->textAlphaC = textAlpha;
		this->backgroundAlphaC = backgroundAlpha;
		this->textColourC = textColour;
		this->backgroundColourC = backgroundColour;
	};

	bool withinObject(Vec2);
	void handleRenderingObject();
	void addExpandedItem(VWindowObject*);
	void toggle();
	void updateSlider();
	float getPixelValue();
};

class VWindowText : public VWindowObject {
public:
	VWindowText(std::string text, MC_Colour textColour = MC_Colour(255, 255, 255), float textSize = 1.0f, float textAlpha = 1.0f) {
		this->text = text;
		this->textColour = textColour;
		this->textSize = textSize;
		this->textAlpha = textAlpha;
		this->type = VObjectType::Text;
		this->InitData();
	};
};

class VWindowButton : public VWindowObject {
public:
	VWindowButton(std::string text, bool* toggle = (bool*)false, float textSize = 1.0f, MC_Colour textColour = MC_Colour(255, 255, 255), MC_Colour backgroundColour = MC_Colour(128, 128, 128), MC_Colour enabledColour = MC_Colour(255, 255, 0), float textAlpha = 1.0f, float backgroundAlpha = .2f) {
		this->text = text;
		this->toggleState = toggle;
		this->textSize = textSize;
		this->textColour = textColour;
		this->backgroundColour = backgroundColour;
		this->enabledColour = enabledColour;
		this->textAlpha = textAlpha;
		this->backgroundAlpha = backgroundAlpha;
		this->type = VObjectType::Button;
		this->InitData();
	};
};

class VWindowSlider : public VWindowObject {
public:
	VWindowSlider(float* value, float min = 0.0f, float max = 10.0f, std::string sliderText = "", MC_Colour textColour = MC_Colour(255, 255, 255), float textSize = 1.0f, float textAlpha = 1.0f, MC_Colour progressBarColour = MC_Colour(0, 255, 128), float progressBarAlpha = 1.0f) {
		this->value = value;
		this->min = min, this->max = max;
		this->draggingSlider = false;
		this->sliderText = sliderText;
		this->textColour = textColour;
		this->textSize = textSize;
		this->textAlpha = textAlpha;
		this->backgroundColour = progressBarColour;
		this->backgroundAlpha = progressBarAlpha;
		this->type = VObjectType::Slider;
		this->InitData();
		this->updateSlider();
	};
};

class VWindow {
private:
	static std::vector<VWindow*> windows;
	static Vec2 mousePos();
public:
	std::string name;
	Vec4 position;
	Vec2 scale;
	MC_Colour textColour, backgroundColour, titleBarColour;
	float textSize, textAlpha, backgroundAlpha;
	bool isHidden = false, isHoveringOver = false, isHoveringOverTitle = false, isBeingDragged = false, canBeDragged = false;
	std::vector<VWindowObject*> windowObjects;
	std::chrono::time_point<std::chrono::steady_clock> lastTicked;

	VWindow(std::string name, Vec4 position, float textSize = 1.0f, MC_Colour textColour = MC_Colour(255, 255, 255), MC_Colour backgroundColour = MC_Colour(120, 120, 120), MC_Colour titleBarColour = MC_Colour(120, 160, 255), float textAlpha = 1.0f, float backgroundAlpha = 1.0f) {
		this->name = name;
		this->position = position;
		this->scale = Vec2((position.z - position.x), (position.w - position.y));
		this->textSize = textSize;
		this->textColour = textColour;
		this->backgroundColour = backgroundColour;
		this->textAlpha = textAlpha;
		this->backgroundAlpha = backgroundAlpha;
		this->titleBarColour = titleBarColour;
		this->isHidden = false, this->isBeingDragged = false, this->canBeDragged = true;
	};

	void setPosition(Vec2);
	void render();
	bool wasRenderedRecently();
	bool posWithinWindow(Vec2);
	bool posWithinTitleBar(Vec2);
	bool hasTitleBar();
	void addObject(VWindowObject*);

	static std::vector<VWindow*> FetchWindows() { return windows; };
	static Vec2 getMousePos() { return mousePos(); };
};