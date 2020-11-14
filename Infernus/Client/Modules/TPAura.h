#pragma once
#include "../../Other/VComponent.h"

class TPAura : public VModule {
public:
	TPAura() : VModule::VModule("TPAura", "Teleports around the entity that you're attacking") {
		this->addWindowObj(new VWindowSlider("Range: ", &this->tpRange));
		this->addWindowObj(new VWindowSlider("Delay (MS): ", &this->delay_ms));
		this->addWindowObj(new VWindowButton("Send Move Packets", &this->sendPackets));
	};
	void onAttack(Actor*, Actor*);
	void onLoop() { delay_ms = roundf(delay_ms); };
private:
	bool sendPackets = false;
	float tpRange = 5.0f;
	int count = 0;
	float delay_ms = 100.0f;
	std::chrono::time_point<std::chrono::steady_clock> savedTime = std::chrono::high_resolution_clock::now();
};