#pragma once

class KeyHook : public VHook {
public:
	void Init();
};

typedef void(WINAPI* _KeyPress)(uint64_t WinKey, bool isDown);
_KeyPress KeyPress;

void KeyPressCallback(uint64_t WinKey, bool isDown) {
	bool cancel = false;
	Utils::keyMapping[WinKey] = isDown;

	for (auto Module : ModulesList) {
		if (Module->isEnabled) {
			Module->onKey(WinKey, isDown, &cancel);
		};

		if (isDown) {
			if (Module->key && Module->key == WinKey) {
				if (Minecraft::GetClientInstance()->MinecraftGame->canUseKeys) {
					Module->isEnabled = !Module->isEnabled;
				};
			};
		};
	};
	if(!cancel) KeyPress(WinKey, isDown);
};

void KeyHook::Init() {
	Utils::DebugFileLog("Preparing Key Hook!");
	uintptr_t KeyHookAddr = Utils::FindSignature("48 89 5C 24 ?? ?? 48 83 EC ?? 8B 05 ?? ?? ?? ?? 8B DA");
	if (MH_CreateHook((void*)KeyHookAddr, &KeyPressCallback, reinterpret_cast<LPVOID*>(&KeyPress)) == MH_OK) {
		Utils::DebugFileLog("Successfully created Key Hook, Installing Hook...");
		MH_EnableHook((void*)KeyHookAddr);
	}
	else {
		Utils::DebugFileLog("Failed to create Key Hook!");
	};
};