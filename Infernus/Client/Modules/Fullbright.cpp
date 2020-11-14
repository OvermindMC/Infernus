#include "Fullbright.h"
#include "../../SDK/Minecraft.h"

void Fullbright::onGmTick() {
	if (gammaPtr != NULL) {
		*(float*)(gammaPtr) = 10.0f;
	};
};

void Fullbright::onEnable() {
	uintptr_t foundAddr = Utils::FindAddress((uintptr_t)Minecraft::GetClientInstance(), { 0x110, 0xB8, 0x8, 0x148 });
	if (foundAddr != NULL) {
		gammaPtr = (uintptr_t)(foundAddr + 0xF0);
		storedValue = *(float*)(gammaPtr);
	}
	else {
		this->isEnabled = false;
	};
};

void Fullbright::onDisable() {
	if (gammaPtr != NULL) {
		*(float*)(gammaPtr) = storedValue;
	};
};