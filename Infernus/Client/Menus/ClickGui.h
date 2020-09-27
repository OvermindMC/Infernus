#pragma once
#include "../../Other/VComponent.h"
#include "../../Other/RenderUtils.h"

class ClickGui : public VModule {
public:
	ClickGui() : VModule::VModule("ClickGui", "Renders a UI which can be used to manage modules") {};
	void onRender();
	void onEnable();
	void onVButtonClick(VWindowObj* Obj);
private:
	std::vector<VWindow*> Windows;
	bool isDragingWindow = false;
};

void ClickGui::onRender() {
	for (auto Window : Windows) { Window->Render(); };
};

void ClickGui::onEnable() {
	if (Windows.empty()) {
		int indexSpace = 0;
		for (auto Category : ClientHandler::GetCategories()) {
			float toRight = indexSpace * 100;
			
			VWindow* newWindow = new VWindow(Category->name, Vec4(toRight + 10, 100, toRight + 100, 230));
			newWindow->textColour = MC_Colour(255, 110, 30);
			newWindow->windowTitleBarColour = MC_Colour(0, 200, 100);
			newWindow->backgroundTransparency = .7f;

			for (auto Module : Category->modules) {
				VWindowButton* moduleBtn = new VWindowButton(Module->name, MC_Colour(255, 255, 0));
				moduleBtn->toggleState = Module->isEnabled;
				newWindow->addObject(moduleBtn);
			};
			Windows.push_back(newWindow);
			indexSpace++;
		};
	};
};

void ClickGui::onVButtonClick(VWindowObj* Obj) {
	if (Obj->objType == 2) {
		for (auto Module : ClientHandler::GetModules()) {
			if (Module->name == Obj->text) {
				Module->isEnabled = Obj->toggleState;
				break;
			};
		};
	};
};