#pragma once
#include "../../Other/VComponent.h"

class Spider : public VModule {
public:
	Spider() : VModule::VModule("Spider", "Automatically ascend upwards on contact with surfaces") {
		this->addWindowObj(new VWindowSlider(&this->speed, 0, 5.0f, "Y Speed: ", MC_Colour(255, 255, 255), 1.0f, 1.0f, MC_Colour(255, 110, 30), .7f));
	};
	void onGmTick();
private:
	float speed = 0.3f;
};

void Spider::onGmTick() {
	BunnyHop* BhopMod = (BunnyHop*)ClientHandler::GetModule(BunnyHop());
	LocalPlayer* Player = Minecraft::GetLocalPlayer();
	if (Player != nullptr) {
		if (Player->toActor()->isCollidedDir() && BhopMod->usingKeys()) {
			Player->Velocity.y = speed;
		};
	};
};