#include "VComponent.h"
#include "RenderUtils.h"
#include "../Client/ClientHandler.h"

//std::vector<VWindow*> StoredWindows;

void VModule::onBaseTick() {
	this->onLoop();
	if (this->wasEnabled != this->isEnabled) {
		if (this->isEnabled) {
			this->onEnable();
		}
		else {
			this->onDisable();
		};
		ClientHandler::SaveModuleState(this);
		this->wasEnabled = this->isEnabled;
	};
	if (this->isEnabled) this->onTick();
};

void VCommand::reply(std::string input) {
	LocalPlayer* Player = Minecraft::GetLocalPlayer();
	if (Player != nullptr) {
		Player->displayTextObjectMessage(&TextHolder(input));
	};
};

/* VWindow */

/*std::vector<VWindow*> VWindow::windows = std::vector<VWindow*>();

Vec2 VWindow::mousePos() {
	GuiData* GuiData = Minecraft::GetClientInstance()->GuiData();
	short mx = float(GuiData->mouseX()) / GuiData->GuiScale();
	short my = float(GuiData->mouseY()) / GuiData->GuiScale();
	if (mx < 0 || mx > GuiData->ScaledResolution.x) mx = 0;
	if (my < 0 || my > GuiData->ScaledResolution.y) my = 0;
	return Vec2(mx, my);
};

void VWindow::setPosition(Vec2 pos) {
	if (!this->isHidden && this->canBeDragged) {
		position.x = pos.x;
		position.y = pos.y;
		position.z = pos.x + scale.x;
		position.w = pos.y + scale.y;
	};
};

void VWindow::render() {
	bool alreadyExists = false;
	for (auto Window : windows) {
		if (this == Window) alreadyExists = true;
	};
	if (!alreadyExists) windows.push_back(this);

	if (!this->isHidden) {
		this->lastTicked = std::chrono::high_resolution_clock::now();
		int objectYPos = 0;

		RenderUtils::RenderText(name, Vec2(position.x, position.y), textColour, textSize, textAlpha);
		RenderUtils::FillRectangle(position, backgroundColour, backgroundAlpha);
		RenderUtils::FillRectangle(Vec4(position.x, position.y, position.z, position.y + 10), titleBarColour, titleAlpha);

		Vec2 currMousePos = mousePos();
		isHoveringOver = posWithinWindow(currMousePos);
		isHoveringOverTitle = (bool)(position.x < currMousePos.x && position.y < currMousePos.y && position.z > currMousePos.x && position.y + 10 > currMousePos.y);

		for (auto VObj : windowObjects) {
			float downY = position.y + (objectYPos * 10) + 10;
			VObj->position = Vec4(position.x, downY, position.z, downY + 10);
			VObj->handleRenderingObject();
			if (!VObj->objects.empty()) {
				RenderUtils::RenderText(VObj->expandedItems ? "-" : "+", Vec2(VObj->position.z - 10, VObj->position.y), VObj->textColour, VObj->textSize, VObj->textAlpha);
				if (VObj->expandedItems) {
					for (auto Obj : VObj->objects) {
						Obj->position = Vec4(position.x, (position.y + (objectYPos * 10) + 20), position.z, (position.y + (objectYPos * 10) + 30));
						Obj->handleRenderingObject();
						if (!Obj->objects.empty()) {
							RenderUtils::RenderText(Obj->expandedItems ? "-" : "+", Vec2(Obj->position.z - 10, Obj->position.y), Obj->textColour, Obj->textSize, Obj->textAlpha);
							if (Obj->expandedItems) {
								for (auto obj : Obj->objects) {
									obj->position = Vec4(position.x, (position.y + (objectYPos * 10) + 30), position.z, (position.y + (objectYPos * 10) + 40));
									obj->handleRenderingObject();
									objectYPos++;
								};
							};
						};
						objectYPos++;
					};
				};
			};
			objectYPos++;
		};

		position.w = position.y + (objectYPos * 10) + 80;
		RenderUtils::FlushText();
	};
};

bool VWindow::wasRenderedRecently() {
	return std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::high_resolution_clock::now() - lastTicked) <= std::chrono::milliseconds(50);
};

bool VWindow::posWithinWindow(Vec2 pos) {
	return position.x < pos.x && position.y < pos.y && position.z > pos.x && position.w > pos.y;
};

bool VWindow::posWithinTitleBar(Vec2 pos) {
	return position.x < pos.x&& position.y < pos.y&& position.z > pos.x&& position.y + 10 > pos.y;
};

bool VWindow::hasTitleBar() {
	return name.length() > 0;
};

void VWindow::addObject(VWindowObject* Obj) {
	this->windowObjects.push_back(Obj);
};

bool VWindowObject::withinObject(Vec2 pos) {
	return position.x < pos.x&& position.y < pos.y&& position.z > pos.x&& position.w > pos.y;
};

void VWindowObject::handleRenderingObject() {
	switch (type) {
	case VObjectType::Text:
		RenderUtils::RenderText(text, Vec2(position.x, position.y), textColour, textSize, textAlpha);
	break;
	case VObjectType::Button:
		RenderUtils::RenderText(text, Vec2(position.x, position.y), *toggleState ? enabledColour : textColour, textSize, textAlpha);
		RenderUtils::FillRectangle(position, backgroundColour, hoveringOver ? (backgroundAlpha - .1f) : backgroundAlpha);
	break;

	case VObjectType::Slider:
		VWindowObject::updateSlider();
		RenderUtils::RenderText(sliderText.length() ? sliderText + text : text, Vec2(position.x, position.y), textColour, textSize, textAlpha);
		RenderUtils::FillRectangle(Vec4(position.x, position.y, (position.x + drawnWidth), position.w), backgroundColour, backgroundAlpha);
	break;
	};
};

void VWindowObject::addExpandedItem(VWindowObject* Obj) {
	objects.push_back(Obj);
};

void VWindowObject::toggle() {
	if (type == VObjectType::Button) {
		*toggleState = !*toggleState;
	};
};

void VWindowObject::updateSlider() {
	std::ostringstream ss;
	ss << *value;
	text = std::string(ss.str());

	if (*value <= min) {
		*value = min;
	}
	else if (*value >= max) *value = max;

	if (*value + 0.2f >= max) *value = max;
	if (*value - 0.2f <= min) *value = min;

	drawnWidth = ((*value + std::abs(min))) / getPixelValue();
};

float VWindowObject::getPixelValue() {
	float div = std::abs(min) + std::abs(max);
	return div / (position.z - position.x);
};*/