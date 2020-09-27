#pragma once
#include "../../Other/VComponent.h"

class AntiBot : public VModule {
public:
	AntiBot() : VModule::VModule("AntiBot", "Prevents targeting bots") { this->isEnabled = true; };
};