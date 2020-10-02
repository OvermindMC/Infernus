#pragma once
#include "../../Other/VComponent.h"
#include "../../Other/RenderUtils.h"

class ClickGui : public VModule {
public:
	ClickGui() : VModule::VModule("ClickGui", "Renders a UI which can be used to manage modules", 0x2D) {};
	void onRender();
	void onEnable();
	void onVButtonClick(VWindowObj*);
private:
	std::vector<VWindow*> Windows;
	bool isDragingWindow = false;
};

void ClickGui::onRender() {
	for (auto Window : Windows) {
		Window->Render();

		for (auto VObj : Window->WindowObjects) {
			if (VObj->hoveringOver && VObj->objType == 2) {
				for (auto Module : ClientHandler::GetModules()) {
					if (Module->name == VObj->text) {
						Vec2 scaledRes = Minecraft::GetClientInstance()->GuiData()->ScaledResolution;
						std::string displayText = std::string(Module->name + ": ") + std::string(Module->description);
						float rectangleLength = RenderUtils::GetTextWidth(displayText, 1.0f);

						RenderUtils::RenderText(displayText, Vec2(0, scaledRes.y - 10), MC_Colour(255, 255, 255), 1.0f, 1.0f);
						RenderUtils::FillRectangle(Vec4(0, scaledRes.y - 10, rectangleLength, scaledRes.y), MC_Colour(0, 0, 0), 1.0f);
						RenderUtils::DrawRectangle(Vec4(0, scaledRes.y - 10, rectangleLength, scaledRes.y), MC_Colour(110, 220, 230), 1.0f, 1.2f);
						RenderUtils::FlushText();
						break;
					};
				};
			};
		};
	};
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