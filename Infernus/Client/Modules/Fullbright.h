#pragma once
#include "../../Other/VComponent.h"

class Fullbright : public VModule {
public:
	Fullbright() : VModule::VModule("Fullbright", "Lets you see in dark environments") {};
	void onGmTick();
	void onEnable();
	void onDisable();
private:
	float storedValue = 0.0f;
	uintptr_t gammaPtr = NULL;
};

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