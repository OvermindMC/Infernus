#include "Criticals.h"
#include "../../SDK/Minecraft.h"

void Criticals::onEnable() {
	critsAddr = Utils::FindSignature("0F B6 86 ?? ?? 00 00 88 47 ?? 48 8B 96");
	if (critsAddr != NULL) {
		Utils::Patch((BYTE*)critsAddr, (BYTE*)"\xB8\x00\x00\x00\x00\x90\x90", 7);
		modified = true;
	};
};

void Criticals::onDisable() {
	if (modified) {
		Utils::Patch((BYTE*)critsAddr, (BYTE*)"\x0F\xB6\x86\xA0\x01\x00\x00", 7);
		modified = false;
	};
};