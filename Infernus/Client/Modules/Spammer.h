#pragma once
#include "../../Other/VComponent.h"

class Spammer : public VModule {
public:
	Spammer() : VModule::VModule("Spammer", "Automatically Spam in the Chat") {
		VWindowSlider* spamDelaySlider = new VWindowSlider("Delay (MS): ", &delay_ms);
		spamDelaySlider->max = 1000.f;
		this->addWindowObj(spamDelaySlider);
	};
	void onGmTick();
public:
	float delay_ms = 0.0f;
	std::string message = std::string("Spammer is enabled, Change message via .spam <message>");
	std::chrono::time_point<std::chrono::steady_clock> savedTime;
};