#pragma once
#include "../../Other/VComponent.h"

class ModuleList : public VModule {
public:
	ModuleList() : VModule::VModule("ModuleList", "Displays a list of enabled modules") { this->isEnabled = true; };
	void onRender();
};

void ModuleList::onRender() {
	std::vector<VModule*> Modules = ClientHandler::GetModules();
	Vec2 screenRes = Minecraft::GetClientInstance()->GuiData()->ScaledResolution;
	int indexY = 0;

	std::vector<VModule*> modules = ClientHandler::GetModules();
	std::vector<std::string> moduleNames;

	for (auto mod : modules) {
		if (mod->isEnabled) moduleNames.push_back(mod->name);
	};

	moduleNames = Utils::SortArrayOfStrings(moduleNames);
	std::reverse(moduleNames.begin(), moduleNames.end());

	for (auto modName : moduleNames) {
		float textWidth = RenderUtils::GetTextWidth(modName, 1.0f);
		float width = screenRes.x - textWidth;
		RenderUtils::RenderText(modName, Vec2(width - 5, indexY * 10 + 5), MC_Colour(255, 255, 255), 1.0f, 1.0f);
		RenderUtils::FillRectangle(Vec4(width - 7, indexY * 10 + 5, width + textWidth - 3, indexY * 10 + 15), MC_Colour(50, 50, 50), .3f);
		RenderUtils::DrawRectangle(Vec4(width - 7, indexY * 10 + 5, width + textWidth - 3, indexY * 10 + 15), MC_Colour(255, 110, 30), .3f, 1.5f);
		indexY++;
	};

	/*for (auto Module : Modules) {
		if (Module->isEnabled) {
			float textWidth = RenderUtils::GetTextWidth(Module->name, 1.0f);
			float width = screenRes.x - textWidth;
			RenderUtils::RenderText(Module->name, Vec2(width - 5, indexY * 10 + 5), MC_Colour(255, 255, 255), 1.0f, 1.0f);
			RenderUtils::FillRectangle(Vec4(width - 7, indexY * 10 + 5, width + textWidth - 3, indexY * 10 + 15), MC_Colour(50, 50, 50), .3f);
			RenderUtils::DrawRectangle(Vec4(width - 7, indexY * 10 + 5, width + textWidth - 3, indexY * 10 + 15), MC_Colour(255, 110, 30), .3f, 1.5f);
			indexY++;
		};
	};*/
	RenderUtils::FlushText();
};