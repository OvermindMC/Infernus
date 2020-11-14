#pragma once
#include "../../Other/VComponent.h"
#include "../../Other/RenderUtils.h"

class Window {
public:
	std::string name;
	Vec2 position;
	Vec4 rectPos;
	Vec4 barPos;

	bool expanded = false;
	bool dragging = false;

	std::vector<VWindowObject*> objects;

	Window(std::string name, Vec2 position) {
		this->name = name;
		this->position = position;
	};

	bool withinWindow(Vec2 pos) {
		return rectPos.x < pos.x && rectPos.y < pos.y && rectPos.z > pos.x && rectPos.w > pos.y;
	};

	bool withinWindowBar(Vec2 pos) {
		return barPos.x < pos.x && barPos.y < pos.y && barPos.z > pos.x && barPos.w > pos.y;
	};
};

class ClickGui : public VModule {
public:
	ClickGui() : VModule::VModule("ClickGui", "Renders a UI which can be used to manage modules", 0x2D) {
		this->addWindowObj(new VWindowButton("Show Tooltips", &this->showTooltips));
	};
	void onRender();
	void onKey(uint64_t, bool, bool*);
	void onEnable();
	void onDisable();
	void renderWindow(Window*);
	void renderObject(Window*, VWindowObject*, int*);
	void onMouseMove(bool*);
	void onMouse(char, bool, bool*);
	Vec2 scaledPos(int, int);
private:
	Vec2 dragStart;
	bool showTooltips = true;
	bool applyingKey = false;
	bool dragging = false;
	bool setPositions = false;
	std::vector<Window*> windows;

	MC_Colour textColour = MC_Colour(255, 255, 255);
	MC_Colour windowBarColour = MC_Colour(255, 128, 0);
	MC_Colour backgroundColour = MC_Colour(20, 20, 20);
};