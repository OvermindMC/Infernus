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
	for (auto Window : Windows) Window->render();
};

void ClickGui::onEnable() {
	if (Windows.empty()) {

		int indexSpace = 0;
		for (auto Category : ClientHandler::GetCategories()) {
			float toRight = indexSpace * 110;

			VWindow* newWindow = new VWindow(Category->name, Vec4(toRight + 10, 100, toRight + 110, 0), 1.0f, MC_Colour(255, 110, 30), MC_Colour(50, 50, 50), MC_Colour(50, 50, 50), 1.0f, .3f);

			for (auto Module : Category->modules) {
				VWindowButton* newObject = new VWindowButton(Module->name, &Module->isEnabled);
				for (auto VObj : Module->WindowObjects) {
					newObject->addExpandedItem(VObj);
				};
				newWindow->addObject(newObject);
			};
			Windows.push_back(newWindow);
			indexSpace++;
		};
	};
};