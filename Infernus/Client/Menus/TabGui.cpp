#include "TabGui.h"
#include "../ClientHandler.h"
#include "../../SDK/Minecraft.h"

void TabGui::onRender() {
	std::vector<VCategory*> Categories = ClientHandler::GetCategories();
	std::vector<VModule*> CurrentModules = Categories.at(selectedCategory)->modules;
	int indexYPos = 0;

	float categoryBoxWidth = RenderUtils::GetTextWidth(Utils::SortArrayOfStrings(ClientHandler::CategoriesToString(Categories)).back(), 1.0f);

	RenderUtils::RenderText("Infernus", Vec2(15, 10), MC_Colour(255, 110, 30), 1.0f, 1.0f);
	for (auto Category : Categories) {
		RenderUtils::RenderText(categorySelected && selectedCategory == indexYPos ? Category->name + " > " : Category->name, Vec2(15, indexYPos * 10 + 20), categorySelected && selectedCategory == indexYPos ? MC_Colour(0, 255, 128) : MC_Colour(200, 200, 200), 1.0f, 1.0f);
		indexYPos++;
	};

	indexYPos = 0;

	if (moduleSelected) {
		if (!CurrentModules.empty()) {
			for (auto Module : CurrentModules) {
				RenderUtils::RenderText(selectedModule == indexYPos ? "> " + Module->name : Module->name, Vec2(categoryBoxWidth + 30, indexYPos * 10 + 20), Module->isEnabled ? MC_Colour(255, 255, 0) : MC_Colour(255, 255, 255), 1.0f, 1.0f);
				indexYPos++;
			};
			float largestModWTxt = RenderUtils::GetTextWidth(Utils::SortArrayOfStrings(ClientHandler::ModulesToString(CurrentModules)).back(), 1.0f) + 10;
			float currentCatWTxt = RenderUtils::GetTextWidth(Categories.at(selectedCategory)->name, 1.0f) + 10;
			float currBoxWidth = largestModWTxt > currentCatWTxt ? largestModWTxt : currentCatWTxt;
			float categoryTextWidth = RenderUtils::GetTextWidth(Categories.at(selectedCategory)->name, 1.0f);
			RenderUtils::RenderText(Categories.at(selectedCategory)->name, Vec2(categoryBoxWidth + 30, 10), MC_Colour(255, 110, 30), 1.0f, 1.0f);
			RenderUtils::FillRectangle(Vec4(categoryBoxWidth + 30, 10, (categoryBoxWidth + 30) + currBoxWidth, (CurrentModules.size() * 10) + 20), MC_Colour(50, 50, 50), .3f);
		};
	};

	RenderUtils::FillRectangle(Vec4(10, 10, categoryBoxWidth + 30, Categories.size() * 10 + 20), MC_Colour(50, 50, 50), .3f);
	RenderUtils::FlushText();
};

void TabGui::onKey(uint64_t key, bool isDown, bool* cancel) {
	if (isDown) {
		if (Minecraft::GetLocalPlayer() != nullptr) {
			if (Minecraft::GetClientInstance()->MinecraftGame->canUseKeys) {
				if (handleKey(key)) {
					*cancel = true;
				};
			};
		}
		else {
			if (handleKey(key)) {
				*cancel = true;
			};
		};
	};
};

bool TabGui::handleKey(uint64_t WinKey) {
	std::vector<VCategory*> Categories = ClientHandler::GetCategories();
	VModule* Module = Categories.at(selectedCategory)->modules.size() ? Categories.at(selectedCategory)->modules.at(selectedModule) : nullptr;

	if (WinKey == 0x25) { //Left
		if (moduleSelected) {
			moduleSelected = false;
			selectedModule = 0;
		}
		else {
			if (categorySelected) {
				categorySelected = false;
			};
		};
		return true;
	}
	else if (WinKey == 0x27) { //Right
		if (!categorySelected) {
			categorySelected = true;
		}
		else {
			if (!moduleSelected) {
				moduleSelected = true;
			}
			else {
				if (Module != nullptr) Module->isEnabled = !Module->isEnabled;
			};
		};
		return true;
	}
	else if (WinKey == 0x26) { //Up
		if (categorySelected && !moduleSelected) {
			if (!selectedCategory) selectedCategory = Categories.size();
			selectedCategory--;
		}
		else {
			if (moduleSelected) {
				if (!selectedModule) selectedModule = Categories.at(selectedCategory)->modules.size();
				selectedModule--;
			};
		};
		return true;
	}
	else if (WinKey == 0x28) { //Down
		if (categorySelected && !moduleSelected) {
			selectedCategory++;
			if (selectedCategory >= Categories.size()) selectedCategory = 0;
		}
		else {
			if (moduleSelected) {
				selectedModule++;
				if (selectedModule >= Categories.at(selectedCategory)->modules.size()) selectedModule = 0;
			};
		};
		return true;
	};
	return false;
};