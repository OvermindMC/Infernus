#pragma once
#include "../../Other/VComponent.h"

class ClickTP : public VModule {
public:
	ClickTP() : VModule::VModule("ClickTP", "Teleport when you click on a block!") {};
	void onMouse(char, bool);
};