#pragma once
#include "Utils.h"
#include "RenderUtils.h"
#include <functional>

class VModule {
public:
	std::string name, description;
	bool isEnabled = false, wasEnabled = false;
	UINT64 key;
	VModule(std::string name, std::string description, UINT64 key = NULL) { this->name = name, this->description = description; this->key = key; };

	std::vector<class VWindowObject*> WindowObjects;

	int objCount = 0;

	void addWindowObj(VWindowObject*);

	/* Events */
	virtual void onBaseTick(); //For ticking each module and handling the onEnable & onDisable events
	virtual void onLoop() {};
	virtual void onEnable() {};
	virtual void onDisable() {};
	virtual void onTick() {};

	virtual void onMouse(char, bool, bool*) {};
	virtual void onMouseMove(bool*) {};

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

class VKey {
public:
	uint64_t key;
	VKey(uint64_t key) {
		this->key = key;
	};
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

enum class VObjectType {
	ModuleContainer,
	Button,
	Slider,
	Key,
	Unknown
};

class VWindowObject {
public:
	std::string text;
	std::string sliderText;
	VObjectType type = VObjectType::Unknown;

	bool expanded;
	bool dragging = false;
	bool changingKey = false;

	Vec2 position;
	Vec4 rectPos;

	bool* toggle;
	float* value;

	float min = 0, max = 10;
	float drawnWidth = 0;

	int ID = 0;

	VModule* modulePtr;
	UINT64* key;

	bool withinRectPos(Vec2 pos) {
		return rectPos.x < pos.x && rectPos.y < pos.y && rectPos.z > pos.x && rectPos.w > pos.y;
	};

	void updateSlider() {
		std::ostringstream ss;
		ss << *value;
		text = sliderText + std::string(ss.str());

		if (*value <= min || *value <= (min + 0.1f)) {
			*value = min;
		}
		else if (*value >= max || *value >= (max - 0.1f)) {
			*value = max;
		};

		float div = std::abs(min) + std::abs(max);
		drawnWidth = ((*value + std::abs(min))) / (div / (rectPos.z - position.x));
	};
};

class VWindowModuleContainer : public VWindowObject {
public:
	VWindowModuleContainer(VModule* modulePtr) {
		this->text = modulePtr->name;
		this->modulePtr = modulePtr;
		this->toggle = &modulePtr->isEnabled;
		this->type = VObjectType::ModuleContainer;
	};
};

class VWindowButton : public VWindowObject {
public:
	VWindowButton(std::string text, bool* toggle = (bool*)false) {
		this->text = text;
		this->toggle = toggle;
		this->type = VObjectType::Button;
	};
};

class VWindowSlider : public VWindowObject {
public:
	VWindowSlider(std::string text, float* value) {
		this->sliderText = text;
		this->value = value;
		this->type = VObjectType::Slider;
	};
};

class VWindowKey : public VWindowObject {
public:
	VWindowKey(UINT64* key) {
		this->key = key;
		this->type = VObjectType::Key;
	};
};