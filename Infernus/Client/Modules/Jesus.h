#pragma once
#include "../../Other/VComponent.h"

class Jesus : public VModule {
public:
	Jesus() : VModule::VModule("Jesus", "Hover above water") {};
	void onGmTick();
};