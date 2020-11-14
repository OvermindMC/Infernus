#pragma once
#include "BunnyHop.h"
#include "../../Other/VComponent.h"

class WarpSpeed : public VModule {
public:
	WarpSpeed() : VModule::VModule("WarpSpeed", "Warp forward") {
		this->addWindowObj(new VWindowSlider("Speed: ", &speed));
		this->addWindowObj(new VWindowButton("Send Packets", &sendPackets));
	};
	void onGmTick();
	void onLoop();
	bool isColliding(Vec3);
	void sendPacket(Vec3);
	void runTask(class LocalPlayer*, Vec3);
private:
	float speed = .45f;
	bool sendPackets = true;
	BunnyHop* Bhop = nullptr;
};