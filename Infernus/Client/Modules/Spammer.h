#pragma once
#include "../../Other/VComponent.h"

class Spammer : public VModule {
public:
	Spammer() : VModule::VModule("Spammer", "Automatically Spam in the Chat") {
		this->addWindowObj(new VWindowSlider(&delay_ms, 0.0f, 20.0f, "Delay (MS): ", MC_Colour(255, 255, 255), 1.0f, 1.0f, MC_Colour(255, 110, 30), .7f));
	};
	void onGmTick();
public:
	float delay_ms = 0.0f;
	std::string message = std::string("Spammer is enabled, Change message via .spam <message>");
	std::chrono::time_point<std::chrono::steady_clock> savedTime;
};

void Spammer::onGmTick() {
	if (std::chrono::duration_cast<std::chrono::seconds>(std::chrono::high_resolution_clock::now() - savedTime) >= std::chrono::milliseconds((int)(delay_ms))) {
		LocalPlayer* Player = Minecraft::GetLocalPlayer();
		if (Player != nullptr) {
			int randomInt = (int)Utils::randomFloat(0, 100);
			std::string brackets = std::string("[ " + std::to_string(randomInt) + " ]");
			std::string modifiedMsg = brackets + std::string(" " + this->message + " ") + brackets;

			TextPacket newPacket(Minecraft::GetLocalPlayer()->toActor(), modifiedMsg);
			Minecraft::GetClientInstance()->LoopbackPacketSender->sendToServer(&newPacket);
		};
		savedTime = std::chrono::high_resolution_clock::now();
	};
};