#pragma once
#include "../../Other/VComponent.h"

class HUD : public VModule {
public:
	HUD() : VModule::VModule("HUD", "Heads up display") { this->isEnabled = true; };
	void onRender();
};