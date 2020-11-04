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
	ClickGui() : VModule::VModule("ClickGui", "Renders a UI which can be used to manage modules", 0x2D) {};
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
	bool applyingKey = false;
	bool dragging = false;
	bool setPositions = false;
	std::vector<Window*> windows;

	MC_Colour textColour = MC_Colour(255, 255, 255);
	MC_Colour windowBarColour = MC_Colour(255, 128, 0);
	MC_Colour backgroundColour = MC_Colour(20, 20, 20);
};

void ClickGui::onRender() {

	int count = 0;
	int counter = 0;
	int yDown = 0;
	for (auto window : windows) {
		if (!setPositions) {
			window->position = Vec2(count > 0 ? windows.at(count - 1)->position.x + RenderUtils::GetTextWidth(windows.at(count - 1)->name, 1.0f) + 120 : 10, window->position.y = count > 0 ? counter >= 3 ? windows.at(count - 1)->position.y + 100 : windows.at(count - 1)->position.y : 0);
			if (counter >= 3) {
				window->position.x = 10;
				counter = 0;
				yDown++;
			};
			counter++;
			count++;
		};
		renderWindow(window);
	};
	
	if (!setPositions) {
		for (int I = 0; I < windows.size(); I++) {
			if (I == (windows.size() - 1)) {
				if (windows.at(I)->position.x > 0) {
					setPositions = true;
					break;
				};
			};
		};
	};
};

void ClickGui::onKey(uint64_t key, bool isDown, bool* cancel) {
	if (isDown) {
		if (applyingKey) {
			if (key != VK_ESCAPE) {
				for (auto Window : windows) {
					for (auto Obj : Window->objects) {
						if (Obj->modulePtr != nullptr) {
							for (auto obj : Obj->modulePtr->WindowObjects) {
								if (obj->changingKey && obj->type == VObjectType::Key) {
									std::string hexified = Utils::hexify(key);
									if (!hexified.empty() && hexified != std::string("-")) {
										Obj->modulePtr->key = key;
										obj->changingKey = false;
										applyingKey = false;
										ClientHandler::UpdateModuleFileData(Obj->modulePtr);
									};
								};
							};
						};
					};
				};
			}
			else {
				for (auto Window : windows) {
					for (auto Obj : Window->objects) {
						if (Obj->modulePtr != nullptr) {
							for (auto obj : Obj->modulePtr->WindowObjects) {
								obj->changingKey = false;
							};
						};
					};
				};
				applyingKey = false;
			};
		}
		else {
			if (key == VK_ESCAPE) {
				isEnabled = false;
			};
		};
	};
	*cancel = true;
};

void ClickGui::onEnable() {
	if (windows.empty()) {
		int count = 0;
		for (auto Category : ClientHandler::GetCategories()) {
			Window* window = new Window(Category->name, Vec2(0, 0));
			for (auto Module : Category->modules) {
				Module->addWindowObj(new VWindowKey(&Module->key));
				window->objects.push_back(new VWindowModuleContainer(Module));
			};
			windows.push_back(window);
			count++;
		};
	};
	Minecraft::GetClientInstance()->releaseMouse();
};

void ClickGui::onDisable() {
	if (applyingKey) {
		isEnabled = true;
	}
	else {
		if (Minecraft::GetLocalPlayer() != nullptr) Minecraft::GetClientInstance()->grabMouse();
	};
};

void ClickGui::renderWindow(Window* window) {
	float titleLength = RenderUtils::GetTextWidth(window->name, .8f);
	float titleBarWidth = titleLength + 120;
	Vec2 windowPos = window->position;
	window->barPos = Vec4(windowPos.x - 3, windowPos.y, windowPos.x + titleBarWidth, windowPos.y + 15);
	RenderUtils::RenderText(window->name, Vec2(windowPos.x, windowPos.y + 2.5), textColour, 1.0f, 1.0f);
	RenderUtils::RenderText(window->expanded ? "-" : "+", Vec2(windowPos.x + (titleBarWidth - 10), windowPos.y + 2.5), textColour, 1.0f, 1.0f);
	RenderUtils::FillRectangle(window->barPos, windowBarColour, 1.0f);

	/* Render background */

	if (window->expanded) {
		int count = 0;
		for (auto Obj : window->objects) {
			if (Obj->type == VObjectType::ModuleContainer) {
				if (Obj->expanded && Obj->modulePtr != nullptr) {
					for (auto obj : Obj->modulePtr->WindowObjects) {
						count++;
					};
				};
			};
			count++;
		};

		window->rectPos = Vec4(windowPos.x - 2, windowPos.y + 15, windowPos.x + (titleBarWidth - 2), windowPos.y + (count * 15) + 20);
		RenderUtils::FillRectangle(window->rectPos, backgroundColour, 1.0f);

		/* Render Objects */

		count = 0;
		for (auto Obj : window->objects) {
			Obj->position = Vec2(windowPos.x + 2, windowPos.y + (count * 15) + 20);
			Obj->rectPos = Vec4(windowPos.x + 2, windowPos.y + (count * 15) + 20, window->rectPos.z, Obj->position.y + 10);
			renderObject(window, Obj, &count);
		};
	};
	RenderUtils::FlushText();
};

void ClickGui::renderObject(Window* window, VWindowObject* Obj, int* count) {
	if (Obj->type == VObjectType::ModuleContainer && Obj->modulePtr != nullptr) {
		if (!Obj->modulePtr->WindowObjects.empty()) {
			RenderUtils::RenderText(Obj->expanded && !Obj->modulePtr->WindowObjects.empty() ? "-" : "+", Vec2(window->rectPos.z - 10, Obj->position.y), textColour, .95, 1.0f);
			if (Obj->expanded) {
				int innerObjCount = 0;
				for (auto obj : Obj->modulePtr->WindowObjects) {
					if (obj->type != VObjectType::ModuleContainer) {
						obj->position = Vec2(Obj->position.x + 5, window->position.y + (*count * 15) + 35);
						obj->rectPos = Vec4(Obj->position.x + 5, obj->position.y, window->rectPos.z, obj->position.y + 10);
						renderObject(window, obj, count);
						innerObjCount++;
					};
				};
				RenderUtils::FillRectangle(Vec4(Obj->position.x, Obj->position.y + 10, Obj->position.x + 2, Obj->position.y + (innerObjCount * 15) + 10), windowBarColour, 1.0f);
			};
		};
		if (Obj->modulePtr->isEnabled) {
			Vec4 recPos = Vec4(Obj->rectPos.z - 30, Obj->position.y, Obj->rectPos.z - 20, Obj->rectPos.w);
			RenderUtils::FillRectangle(recPos, windowBarColour, .6f);
		};
	}
	else if (Obj->type == VObjectType::Button) {
		Obj->rectPos = Vec4(Obj->rectPos.x, Obj->rectPos.y - 2, Obj->rectPos.x + 10, Obj->rectPos.w - 2);
		if (*Obj->toggle) {
			RenderUtils::FillRectangle(Obj->rectPos, windowBarColour, 1.0f);
		};
		RenderUtils::DrawRectangle(Obj->rectPos, MC_Colour(200, 200, 200), .8f, .8f);
		Obj->position.x += 15.0f;
	}
	else if (Obj->type == VObjectType::Slider) {
		Obj->updateSlider();
		RenderUtils::FillRectangle(Vec4(Obj->rectPos.x, Obj->rectPos.y - 2, Obj->rectPos.x + Obj->drawnWidth, Obj->rectPos.w + 2), MC_Colour(200, 200, 200), .3f);
	}
	else if (Obj->type == VObjectType::Key) {
		if (Obj->changingKey) {
			Obj->text = "Listening for key...";
		}
		else {
			Obj->text = "Keybind: ";
			Obj->text += *Obj->key != NULL ? Utils::convert_ASCII(*Obj->key) : "NONE";
		};
	};
	RenderUtils::RenderText(Obj->text, Obj->position, textColour, .95f, 1.0f);
	*count = *count + 1;
};

void ClickGui::onMouseMove(bool* cancel) {
	
	std::vector<Window*> reversed = windows;
	std::reverse(reversed.begin(), reversed.end());

	Vec2 mousePos = scaledPos(Utils::mousePos.x, Utils::mousePos.y);

	/* Window Dragging */

	if (Utils::mouseState[1]) {
		if (dragging) {
			for (auto Window : reversed) {
				if (Window->dragging) {
					Vec2 diff = Vec2(mousePos).sub(dragStart);
					Window->position = Window->position.add(diff);
					dragStart = mousePos;
					break;
				};
			};
		};
	};

	/* Slider Dragging */

	if (Utils::mouseState[1]) {
		bool draggingSlider = false;
		for (auto Window : reversed) {
			if (!draggingSlider && !dragging) {
				for (auto Obj : Window->objects) {
					if (!draggingSlider && !dragging) {
						if (Obj->modulePtr != nullptr) {
							for (auto obj : Obj->modulePtr->WindowObjects) {
								if (!dragging) {
									if (obj->type == VObjectType::Slider && obj->withinRectPos(scaledPos(Utils::mousePos.x, Utils::mousePos.y))) {
										int xOff = scaledPos(Utils::mousePos.x, Utils::mousePos.y).x - obj->position.x;
										float div = std::abs(obj->min) + std::abs(obj->max);
										float newVal = (div / (obj->rectPos.z - obj->rectPos.x)) * xOff;
										newVal += obj->min;
										*obj->value = newVal;
										draggingSlider = true;
										break;
									};
								} else break;
							};
						};
					} else break;
				};
			} else break;
		};
	};

	*cancel = true;
};

void ClickGui::onMouse(char action, bool isDown, bool* cancel) {

	std::vector<Window*> reversed = windows;
	std::reverse(reversed.begin(), reversed.end());

	Vec2 mousePos = scaledPos(Utils::mousePos.x, Utils::mousePos.y);

	/* Window Dragging */

	if (action == 1) {
		if (isDown) {
			for (auto Window : reversed) {
				if (!dragging) {
					if (Window->withinWindowBar(scaledPos(Utils::mousePos.x, Utils::mousePos.y))) {
						Window->dragging = true;
						dragging = true;
						dragStart = mousePos;
					};
				};
			};
		}
		else {
			for (auto Window : reversed) {
				Window->dragging = false;
			};
			dragging = false;
		};
	};

	/* Window Expanding */

	if (action == 2 && isDown) {
		for (auto Window : reversed) {
			if (Window->withinWindowBar(scaledPos(Utils::mousePos.x, Utils::mousePos.y))) {
				Window->expanded = !Window->expanded;
				break;
			};
		};
	};

	/* Window Elements - Buttons */

	if (action == 1 && isDown) {
		bool clicked = false;
		for (auto Window : reversed) {
			if (!clicked) {
				if (Window->withinWindowBar(scaledPos(Utils::mousePos.x, Utils::mousePos.y)) || Window->dragging)
					break;
				if (Window->expanded && Window->withinWindow(scaledPos(Utils::mousePos.x, Utils::mousePos.y))) {
					for (auto Obj : Window->objects) {
						if (!clicked) {
							if (Obj->withinRectPos(scaledPos(Utils::mousePos.x, Utils::mousePos.y))) {
								if (Obj->modulePtr != nullptr) {
									Obj->modulePtr->isEnabled = !Obj->modulePtr->isEnabled;
								};
								clicked = true;
							};
						}
						else break;
					};
				};
			};
		};
	}
	else if (action == 2 && isDown) {
		bool clicked = false;
		for (auto Window : reversed) {
			if (!clicked) {
				if (Window->withinWindowBar(scaledPos(Utils::mousePos.x, Utils::mousePos.y)) || Window->dragging)
					break;
				if (Window->expanded && Window->withinWindow(scaledPos(Utils::mousePos.x, Utils::mousePos.y))) {
					for (auto Obj : Window->objects) {
						if (!clicked) {
							if (Obj->withinRectPos(scaledPos(Utils::mousePos.x, Utils::mousePos.y))) {
								Obj->expanded = !Obj->expanded;
								clicked = true;
							};
						}
						else break;
					};
				};
			};
		};
	};

	if (action == 1 && isDown) {
		bool clicked = false;
		for (auto Window : reversed) {
			if (!clicked) {
				if (Window->withinWindowBar(scaledPos(Utils::mousePos.x, Utils::mousePos.y)) || Window->dragging)
					break;
				if (Window->expanded && Window->withinWindow(scaledPos(Utils::mousePos.x, Utils::mousePos.y))) {
					for (auto Obj : Window->objects) {
						if (!clicked) {
							if (Obj->modulePtr != nullptr) {
								for (auto obj : Obj->modulePtr->WindowObjects) {
									if (obj->withinRectPos(scaledPos(Utils::mousePos.x, Utils::mousePos.y))) {
										if (obj->type == VObjectType::Button) {
											*obj->toggle = !*obj->toggle;
										}
										else if (obj->type == VObjectType::Key) {
											if (!applyingKey) {
												obj->changingKey = true;
												applyingKey = true;
											};
										};
										clicked = true;
									};
								};
							};
						} else break;
					};
				};
			} else break;
		};
	};

	*cancel = true;
	
};

Vec2 ClickGui::scaledPos(int a1, int a2) {
	GuiData* GuiData = Minecraft::GetClientInstance()->GuiData();
	short mx = float(a1) / GuiData->GuiScale();
	short my = float(a2) / GuiData->GuiScale();
	if (mx < 0 || mx > GuiData->ScaledResolution.x) mx = 0;
	if (my < 0 || my > GuiData->ScaledResolution.y) my = 0;
	return Vec2(mx, my);
};