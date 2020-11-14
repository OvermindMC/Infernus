#pragma once
#include "../../Other/VComponent.h"

class Killaura : public VModule {
public:
	Killaura() : VModule::VModule("Killaura", "Automatically attack nearby entities") {
		this->addWindowObj(new VWindowButton("Multi-Ents", &this->multiEnts));
		this->addWindowObj(new VWindowButton("Attack with UI open", &this->menuOpen));
		this->addWindowObj(new VWindowButton("Send Server Rotations", &this->sendRotations));
		this->addWindowObj(new VWindowSlider("Range: ", &disRange));
		VWindowSlider* delaySlider = new VWindowSlider("Delay (MS): ", &delay_ms);
		delaySlider->max = 50.f;
		this->addWindowObj(delaySlider);
	};
	void onLoop() { delay_ms = roundf(delay_ms); };
	void onGmTick();

	void attackPlayers();
	void attackEnt(Actor*);

	void onPacket(void* Packet, PacketType type, bool* cancel);

	bool multiEnts = true;
	bool menuOpen = true;
	bool sendRotations = true;
	float disRange = 8.0f;
	float delay_ms = 0.0f;
	std::chrono::time_point<std::chrono::steady_clock> savedTime = std::chrono::high_resolution_clock::now();

	Vec2 storedAngles;
	bool writePacket = false;
};