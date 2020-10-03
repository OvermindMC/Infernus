#pragma once
#include "../../Other/VComponent.h"

class MouseHook : public VHook {
public:
	void Init();
};

typedef void(__fastcall* _InputMouse)(uint64_t param_1, char param_2, uint64_t param_3, uint64_t param_4, uint64_t param_5, short param_6, short param_7, byte param_8);
_InputMouse InputMouse;

void MouseCallback(uint64_t a1, char action, uint64_t isDown, uint64_t a4, uint64_t a5, short a6, short a7, byte a8) {

	if (action == 1) {
		if (isDown) {
			for (auto Window : VWindow::FetchWindows()) {
				if (Window->hoveringOverTitleBar()) {
					Window->isBeingDragged = true;
					break;
				};
			};
		}
		else {
			for (auto Window : VWindow::FetchWindows()) {
				if (Window->isBeingDragged) Window->isBeingDragged = false;
			};
		};
	};

	if (action) {
		if (Utils::mouseState[action] != isDown) {
			Utils::mouseState[action] = isDown;

			for (auto Module : ClientHandler::GetModules()) if (Module->isEnabled) Module->onMouse(action, (bool)(isDown));
		};
	}
	else {
		for (auto Module : ClientHandler::GetModules()) if (Module->isEnabled) Module->onMouseMove();

		for (auto Window : VWindow::FetchWindows()) {
			if (Window->isBeingDragged) {
				Window->setPosition(Vec2((int)(VWindow::getMouseX() - 15), (int)(VWindow::getMouseY() - 8)));
				break;
			};
		};
	};

	for (auto Window : VWindow::FetchWindows()) {
		for (auto VObj : Window->WindowObjects) {
			if (VObj->hoveringOver) {
				if (VObj->objType == 2 && (bool)(action == 1 && isDown)) {
					VObj->toggleButtonState();
					for (auto Module : ClientHandler::GetModules()) if (Module->isEnabled) Module->onVButtonClick(VObj);
				}
				else if (VObj->objType == 3) {
					if (isDown && VObj->Module->isEnabled) {
						switch (action) {
						case 1:
							VObj->Module->isEnabled = !VObj->Module->isEnabled;
						break;
						case 2:
							VObj->expandedItems = !VObj->expandedItems;
						break;
						};

						for (auto Obj : VObj->Module->WindowObjects) {
							if (Obj->hoveringOver) Obj->toggleButtonState();
						};
					};
				};
			};
		};
	};

	InputMouse(a1, action, isDown, a4, a5, a6, a7, a8);
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