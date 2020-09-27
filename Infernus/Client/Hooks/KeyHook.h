#pragma once

class KeyHook : public VHook {
public:
	void Init();
};

typedef int(WINAPI* _KeyPress)(uint64_t WinKey, bool isDown);
_KeyPress KeyPress;

int KeyPressCallback(uint64_t WinKey, bool isDown) {
	Utils::keyMapping[WinKey] = isDown;
	if (isDown) {
		for (auto Module : ModulesList) {
			if (Module->isEnabled) {
				Module->onKey(WinKey, isDown);
			};
			if (Module->key != NULL && Module->key == WinKey) {
				if (Minecraft::GetClientInstance()->MinecraftGame->canUseKeys) {
					Module->isEnabled = !Module->isEnabled;
				};
			};
		};
	};
	return KeyPress(WinKey, isDown);
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