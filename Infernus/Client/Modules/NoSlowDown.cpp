#include "NoSlowDown.h"
#include "../../SDK/Minecraft.h"

void NoSlowDown::onEnable() {
	if (opCodeAddresses.empty()) {
		opCodeAddresses.push_back(Utils::FindSignature("F3 0F 11 46 ?? F3 0F 10 4E ??"));
		opCodeAddresses.push_back(Utils::FindSignature("F3 0F 11 46 ?? 45 89 66 ??"));
	};

	if (!opCodeAddresses.empty()) {
		for (int I = 0; I < opCodeAddresses.size(); I++) {
			uintptr_t curr = opCodeAddresses.at(I);
			if (curr != NULL) Utils::Nop((BYTE*)curr, 5);
		};
	};
};

void NoSlowDown::onDisable() {
	if (!opCodeAddresses.empty()) {
		for (int I = 0; I < opCodeAddresses.size(); I++) {
			uintptr_t curr = opCodeAddresses.at(I);
			if (curr != NULL) Utils::Patch((BYTE*)curr, (BYTE*)"\xF3\x0F\x11\x46\x0C", 5);
		};
	};
};