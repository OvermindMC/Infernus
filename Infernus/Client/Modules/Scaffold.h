#pragma once
#include "../../Other/VComponent.h"

class Scaffold : public VModule {
public:
	Scaffold() : VModule::VModule("Scaffold", "Automatically place blocks below you") {};
	void onGmTick();
	bool tryBuild(Vec3);
};