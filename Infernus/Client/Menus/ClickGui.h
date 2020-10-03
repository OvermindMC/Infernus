#pragma once
#include "../../Other/VComponent.h"
#include "../../Other/RenderUtils.h"

class ClickGui : public VModule {
public:
	ClickGui() : VModule::VModule("ClickGui", "Renders a UI which can be used to manage modules", 0x2D) {};
	void onRender();
	void onEnable();
private:
	std::vector<VWindow*> Windows;
};

void ClickGui::onRender() {
	for (auto Window : Windows) Window->Render();
};

void ClickGui::onEnable() {
	if (Windows.empty()) {

		int indexSpace = 0;
		for (auto Category : ClientHandler::GetCategories()) {
			float toRight = indexSpace * 110;

			VWindow* newWindow = new VWindow(Category->name, Vec4(toRight + 10, 100, toRight + 110, 230));
			newWindow->textColour = MC_Colour(255, 110, 30);
			newWindow->windowTitleBarColour = MC_Colour(0, 200, 100);
			newWindow->backgroundTransparency = .7f;

			for (auto Module : Category->modules) {
				VWindowButtonModule* newObject = new VWindowButtonModule(Module);
				newWindow->addObject(newObject);
			};
			Windows.push_back(newWindow);
			indexSpace++;
		};
	};
};