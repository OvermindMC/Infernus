#pragma once
#include "../../Other/VComponent.h"

class NoWeb : public VModule {
public:
	NoWeb() : VModule::VModule("NoWeb", "Prevent cobwebs from slowing you down") {};
	void onGmTick();
};