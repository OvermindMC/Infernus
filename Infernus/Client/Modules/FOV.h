#pragma once
#include "../../Other/VComponent.h"

class FOV : public VModule {
public:
	FOV() : VModule::VModule("FOV", "Change your field of view") {
		VWindowSlider* newSlider = new VWindowSlider("FOV Value: ", &modifier);
		newSlider->max = 2.0f;
		this->addWindowObj(newSlider);
	};
	void onGmTick();
	void onDisable();
private:
	bool modified = false;
	float modifier = 0.1f;
};

void FOV::onGmTick() {
	LocalPlayer* Player = Minecraft::GetLocalPlayer();
	if (Player != nullptr) {
		Player->setFieldOfViewModifier(modifier);
		modified = true;
	};
};

void FOV::onDisable() {
	LocalPlayer* Player = Minecraft::GetLocalPlayer();
	if (Player != nullptr) {
		if (modified) {
			Player->setFieldOfViewModifier(1.0f);
			modified = false;
		};
	};
};