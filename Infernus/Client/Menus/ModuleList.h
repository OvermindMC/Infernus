#pragma once
#include "../../Other/VComponent.h"

class ModuleList : public VModule {
public:
	ModuleList() : VModule::VModule("ModuleList", "Displays a list of enabled modules") { this->isEnabled = true; };
	void onRender();
};