#pragma once
#include "../../Other/VComponent.h"

class Triggerbot : public VModule {
public:
	Triggerbot() : VModule::VModule("Triggerbot", "Automatically attack facing mobs") {
		this->addWindowObj(new VWindowSlider(&delay_ms, 0, 1000.0f, "Delay (MS): ", MC_Colour(255, 255, 255), 1.0f, 1.0f, MC_Colour(255, 110, 30), .7f));
	};
	void onGmTick();
	void onLoop() { delay_ms = roundf(delay_ms); };
private:
	float delay_ms = 0.0f;
	std::chrono::time_point<std::chrono::steady_clock> savedTime;
};

void Triggerbot::onGmTick() {
	if (std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::high_resolution_clock::now() - savedTime) >= std::chrono::milliseconds((int)delay_ms)) {
		LocalPlayer* Player = Minecraft::GetLocalPlayer();
		if (Player != nullptr) {
			Actor* facing = Player->MultiPlayerLevel->facingEnt;
			if (facing != nullptr) {
				Minecraft::GetGameMode()->attack(facing);
				Player->swing();
			};
		};
	};
};