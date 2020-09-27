#include "VComponent.h"
#include "RenderUtils.h"
#include "../Client/ClientHandler.h"

std::vector<VWindow*> StoredWindows;

bool alreadyStoredWindow(VWindow* Window) {
	for (auto StoredWindow : StoredWindows) {
		if (StoredWindow == Window) return true;
	};
	return false;
};

void VModule::onLoop() {
	if (this->wasEnabled != this->isEnabled) {
		if (this->isEnabled) {
			this->onEnable();
		}
		else {
			this->onDisable();
		};
		this->wasEnabled = this->isEnabled;
	};
	if (this->isEnabled) this->onTick();
};

void VModule::onTick() {};

void VModule::onEnable() {
	for (auto Module : ClientHandler::GetModules()) {
		Module->EnabledCall(this);
	};
};
void VModule::onDisable() {
	for (auto Module : ClientHandler::GetModules()) {
		Module->DisabledCall(this);
	};
};

/* Virtual Window Stuff */

std::vector<VWindow*> VWindow::FetchWindows() {
	return StoredWindows;
};

void VWindow::setPosition(Vec2 pos) {
	position.x = pos.x - 10;
	position.y = pos.y - 4;
	position.z = pos.x + position.z;
	position.w = pos.y + position.w;

};

void VWindow::Render() {

	if (!alreadyStoredWindow(this)) StoredWindows.push_back(this);

	if (!this->isHidden) {
		RenderUtils::RenderText(name, Vec2(position.x, position.y), textColour, 1.0f, textTransparency);
		RenderUtils::FillRectangle(position, backgroundColour, backgroundTransparency);
		RenderUtils::FillRectangle(Vec4(position.x, position.y, position.z, position.y + 10), windowTitleBarColour, 1.0f);

		int objectYPos = 0;
		for (auto VObj : this->WindowObjects) {
			float downY = position.y + (objectYPos * 10) + 10;
			VObj->position = Vec4(position.x, downY, position.z, downY + 10);

			if (VObj->contains(getMouseX(), getMouseY())) {
				VObj->backgroundAlpha = .3f;
				VObj->hoveringOver = true;
			}
			else {
				if (VObj->hoveringOver) {
					VObj->hoveringOver = false;
					VObj->backgroundAlpha = VObj->backgroundAlphaCopy;
				};
			};

			switch (VObj->objType) {
			case 1: //Text
				RenderUtils::RenderText(VObj->text, Vec2(VObj->position.x, VObj->position.y), VObj->textColour, 1.0f, VObj->textAlpha);
			break;

			case 2: //Button
				if (VObj->toggleState) {
					VObj->textColour = MC_Colour(200, 200, 100);
				}
				else {
					if (VObj->textColour != VObj->textColourCopy) VObj->textColour = VObj->textColourCopy;
				};
				RenderUtils::RenderText(VObj->text, Vec2(VObj->position.x, VObj->position.y), VObj->textColour, 1.0, VObj->textAlpha);
				RenderUtils::FillRectangle(VObj->position, VObj->backgroundColour, VObj->backgroundAlpha);
			break;
			};

			if(VObj->objType > 0 && VObj->objType <= 2) objectYPos++;
		};

		RenderUtils::FlushText();
	};
};

void VWindow::addObject(VWindowObj* object) {
	this->WindowObjects.push_back(object);
};

bool VWindow::withinWindowBar(float pX, float pY) {
	return position.x < pX&& position.y < pY&& position.z > pX && (position.y + 10) > pY;
};

bool VWindow::hoveringOverTitleBar() {
	return this->withinWindowBar(getMouseX(), getMouseY());
};

short VWindow::getMouseX() {
	GuiData* GuiData = Minecraft::GetClientInstance()->GuiData();
	short mx = float(GuiData->mouseX()) / GuiData->GuiScale();
	if (mx < 0 || mx > GuiData->ScaledResolution.x) mx = 0;
	return mx;
};

short VWindow::getMouseY() {
	GuiData* GuiData = Minecraft::GetClientInstance()->GuiData();
	short my = float(GuiData->mouseY()) / GuiData->GuiScale();
	if (my < 0 || my > GuiData->ScaledResolution.y) my = 0;
	return (int)(my + 1);
};