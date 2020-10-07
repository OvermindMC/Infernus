#include "VComponent.h"
#include "RenderUtils.h"
#include "../Client/ClientHandler.h"

std::vector<VWindow*> StoredWindows;

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
	if (this->canBeDragged) {
		position.x = pos.x;
		position.y = pos.y;
		position.z = pos.x + scale.x;
		position.w = pos.y + scale.y;
	};
};

void VWindow::Render() {

	bool alreadyExist = false;
	for (auto Window : StoredWindows) {
		if (Window == this) alreadyExist = true;
	};
	if(!alreadyExist) StoredWindows.push_back(this);

	if (!this->isHidden) {
		this->lastTicked = std::chrono::high_resolution_clock::now();
		RenderUtils::RenderText(name, Vec2(position.x, position.y), textColour, 1.0f, textTransparency);
		RenderUtils::FillRectangle(position, backgroundColour, backgroundTransparency);
		RenderUtils::FillRectangle(Vec4(position.x, position.y, position.z, position.y + 10), windowTitleBarColour, 1.0f);

		int pX = (int)getMouseX();
		int pY = (int)getMouseY();

		if (position.x < pX && position.y < pY && position.z > pX && position.w > pY) {
			isHoveringOver = true;
		}
		else {
			isHoveringOver = false;
		};

		int objectYPos = 0;
		for (auto VObj : this->WindowObjects) {
			
			float downY = position.y + (objectYPos * 10) + 10;
			VObj->position = Vec4(position.x, downY, position.z, downY + 10);

			if (VObj->contains((int)getMouseX(), (int)getMouseY())) {
				VObj->backgroundAlpha = .3f;
				VObj->hoveringOver = true;
			}
			else {
				if (VObj->hoveringOver) {
					VObj->hoveringOver = false;
					VObj->backgroundAlpha = VObj->backgroundAlphaCopy;
				};
			};

			int type = VObj->objType;

			if (type == 2) {
				if (VObj->toggleState) {
					VObj->textColour = MC_Colour(200, 200, 100);
				}
				else {
					if (VObj->textColour != VObj->textColourCopy) VObj->textColour = VObj->textColourCopy;
				};
				RenderUtils::RenderText(VObj->text, Vec2(VObj->position.x, VObj->position.y), VObj->textColour, 1.0, VObj->textAlpha);
				RenderUtils::FillRectangle(VObj->position, VObj->backgroundColour, VObj->backgroundAlpha);
			};

			if (type == 3) {
				VModule* Module = VObj->Module;
				if (Module != nullptr) {
					VObj->textColour = Module->isEnabled ? MC_Colour(200, 200, 100) : VObj->textColourCopy;
					RenderUtils::RenderText(Module->name, Vec2(VObj->position.x, VObj->position.y), VObj->textColour, 1.0, VObj->textAlpha);
					RenderUtils::FillRectangle(VObj->position, VObj->backgroundColour, VObj->backgroundAlpha);

					if (!Module->WindowObjects.empty()) {
						RenderUtils::RenderText(VObj->expandedItems ? "-" : "+", Vec2(VObj->position.x + (this->scale.x - 10), VObj->position.y), MC_Colour(255, 255, 255), 1.0f, 1.0f);

						if (VObj->expandedItems) {
							for (auto Obj : Module->WindowObjects) {
								Obj->position = Vec4(position.x, (position.y + (objectYPos * 10) + 20), position.z, (position.y + (objectYPos * 10) + 30));

								RenderUtils::RenderText(Obj->text, Vec2(Obj->position.x, Obj->position.y), Obj->textColour, 1.0f, Obj->textAlpha);

								if (Obj->contains((int)VWindow::getMouseX(), (int)VWindow::getMouseY())) {
									Obj->backgroundAlpha = .3f;
									Obj->hoveringOver = true;
								}
								else {
									if (Obj->hoveringOver) {
										Obj->backgroundAlpha = Obj->backgroundAlphaCopy;
										Obj->hoveringOver = false;
									};
								};

								if (Obj->objType) {
									if (Obj->objType == 2) {
										Obj->textColour = *Obj->toggleState ? MC_Colour(200, 200, 100) : Obj->textColourCopy;
										RenderUtils::FillRectangle(Obj->position, Obj->backgroundColour, Obj->backgroundAlpha);
									}
									else  if (Obj->objType == 4) {
										Obj->updateSlider();
										RenderUtils::FillRectangle(Vec4(Obj->position.x, Obj->position.y, (Obj->position.x + Obj->drawnWidth), Obj->position.w), MC_Colour(0, 140, 255), 1.0f);
									};

									objectYPos++;
								};
							};
						};
					};
				};
			};

			if (type == 4) {
				RenderUtils::FillRectangle(Vec4(VObj->position.x, VObj->position.y, (VObj->position.x + VObj->drawnWidth), VObj->position.w), MC_Colour(0, 140, 255), 1.0f);
				VObj->updateSlider();
			};

			if (type) {
				RenderUtils::RenderText(VObj->text, Vec2(VObj->position.x, VObj->position.y), VObj->textColour, 1.0f, VObj->textAlpha); //Applies for all
				objectYPos++;
			};
		};

		position.w = position.y + (objectYPos * 10) + 50; //Automatically enlarge VWindow
		RenderUtils::FlushText();
	}
	else {
		isHoveringOver = false;
	}
};

void VWindow::addObject(VWindowObj* object) {
	this->WindowObjects.push_back(object);
};

bool VWindow::withinWindow(float pX, float pY) {
	return position.x < pX&& position.y < pY&& position.z > pX&& position.w > pY;
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

bool VWindow::renderedRecently() {
	return std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::high_resolution_clock::now() - lastTicked) <= std::chrono::milliseconds(50);
};