#pragma once
#include "../../Other/VComponent.h"

class MouseHook : public VHook {
public:
	void Init();
};

typedef void(__fastcall* _InputMouse)(uint64_t param_1, char param_2, uint64_t param_3, uint64_t param_4, uint64_t param_5, short param_6, short param_7, byte param_8);
_InputMouse InputMouse;

/*
* Vec2 VWindow::mousePos() {
	GuiData* GuiData = Minecraft::GetClientInstance()->GuiData();
	short mx = float(GuiData->mouseX()) / GuiData->GuiScale();
	short my = float(GuiData->mouseY()) / GuiData->GuiScale();
	if (mx < 0 || mx > GuiData->ScaledResolution.x) mx = 0;
	if (my < 0 || my > GuiData->ScaledResolution.y) my = 0;
	return Vec2(mx, my);
};
*/

Vec2 scaledPos(int a1, int a2) {
	GuiData* GuiData = Minecraft::GetClientInstance()->GuiData();
	short mx = float(a1) / GuiData->GuiScale();
	short my = float(a2) / GuiData->GuiScale();
	if (mx < 0 || mx > GuiData->ScaledResolution.x) mx = 0;
	if (my < 0 || my > GuiData->ScaledResolution.y) my = 0;
	return Vec2(mx, my);
};

Vec2 scaledMousePos = Vec2();
bool alreadyDraggingWindow = false;

void handleVObject(VWindowObject* VObj, char action, bool isDown) {
	switch (VObj->type) {
		case VObjectType::Button:
			if (action && isDown && VObj->hoveringOver) {
				if (action == 1) {
					VObj->toggle();
				}
				else if (action == 2) {
					if (!VObj->objects.empty()) VObj->expandedItems = !VObj->expandedItems;
				};
			};
		break;

		case VObjectType::Slider:
			if (action == 1) {
				if (VObj->hoveringOver) {
					VObj->draggingSlider = isDown;
				}
				else {
					if (VObj->draggingSlider) VObj->draggingSlider = false;
				};
			};

			if (VObj->hoveringOver && VObj->draggingSlider) {
				int xOff = scaledMousePos.x - VObj->position.x;
				float newVal = VObj->getPixelValue() * xOff;
				newVal += VObj->min;
				*VObj->value = newVal;
			};
		break;
	};
};

void MouseCallback(uint64_t a1, char action, uint64_t isDown, uint64_t a4, uint64_t a5, short a6, short a7, byte a8) {
	if (action) {
		if (Utils::mouseState[action] != isDown) {
			Utils::mouseState[action] = isDown;

			for (auto Module : ClientHandler::GetModules()) if (Module->isEnabled) Module->onMouse(action, isDown);
		};
	}
	else {
		for (auto Module : ClientHandler::GetModules()) if (Module->isEnabled) Module->onMouseMove();
	};

	/* VWindow Stuff */

	bool returnOrigin = true;

	for (auto Window : VWindow::FetchWindows()) {
		if (Window->wasRenderedRecently()) {
			scaledMousePos = scaledPos(a4, a5);
			Window->isHoveringOverTitle = Window->posWithinTitleBar(scaledMousePos);
			Window->isHoveringOver = Window->posWithinWindow(scaledMousePos);

			if (Window->wasRenderedRecently() && Window->canBeDragged && Window->isBeingDragged && Window->hasTitleBar()) {
				Window->setPosition(Vec2(scaledMousePos.x - 10, scaledMousePos.y - 8));
				alreadyDraggingWindow = true;
			};

			if (Window->isHoveringOverTitle && Window->hasTitleBar()) {
				if (Utils::mouseState[1]) {
					if (!alreadyDraggingWindow) {
						Window->isBeingDragged = true;
						alreadyDraggingWindow = true;
					};
				}
				else {
					if (Window->isBeingDragged) {
						Window->isBeingDragged = false;
						alreadyDraggingWindow = false;
					};
				};
			};

			if (!alreadyDraggingWindow) {
				for (auto VObj : Window->windowObjects) {
					VObj->hoveringOver = VObj->withinObject(scaledMousePos);
					handleVObject(VObj, action, isDown);
					for (auto Obj : VObj->objects) {
						Obj->hoveringOver = Obj->withinObject(scaledMousePos);
						handleVObject(Obj, action, isDown);
					};
				};
			};

			returnOrigin = false;
		};
	};

	if(returnOrigin) InputMouse(a1, action, isDown, a4, a5, a6, a7, a8);
}

void MouseHook::Init() {
	uintptr_t signatureAddr = Utils::FindSignature("48 8B C4 48 89 58 ?? 48 89 68 ?? 48 89 70 ?? 57 41 54 41 55 41 56 41 57 48 83 EC ?? 44 0F B7 BC 24 ?? ?? ?? ?? 33 F6");
	if (signatureAddr != NULL) {
		Utils::DebugFileLog("Found address needed for the mouse hook, Preparing Mouse Hook now...");
		if (MH_CreateHook((void*)signatureAddr, &MouseCallback, reinterpret_cast<LPVOID*>(&InputMouse)) == MH_OK) {
			Utils::DebugFileLog("Successfully created mouse hook, enabling hook now...");
			MH_EnableHook((void*)signatureAddr);
		}
		else {
			Utils::DebugFileLog("Failed to create mouse hook!");
		};
	}
	else {
		Utils::DebugFileLog("Failed to find address needed for the mouse hook");
	};
};