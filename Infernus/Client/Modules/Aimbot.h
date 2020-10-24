#pragma once
#include "../../Other/VComponent.h"

class Aimbot : public VModule {
public:
	Aimbot() : VModule::VModule("Aimbot", "Automatically aim your crosshair at other entities") {
		this->addWindowObj(new VWindowSlider(&this->distance, 0.0f, 20.0f, "Distance: ", MC_Colour(255, 255, 255), 1.0f, 1.0f, MC_Colour(255, 110, 30), .7f));
	};
	void onGmTick();
	void aimAt(Actor*);
private:
	float distance = 8.0f;
};

void Aimbot::onGmTick() {
	LocalPlayer* Player = Minecraft::GetLocalPlayer();
	std::vector<Actor*>* Entities = Minecraft::FetchPlayers();
	if (Player != nullptr && Entities != nullptr && !Entities->empty()) {
		std::vector<float> distances = std::vector<float>();
		for (auto Entity : *Entities) {
			float currDistance = Utils::distanceVec3(*Entity->getPos(), *Player->getPos());
			if (currDistance <= distance) {
				distances.push_back(currDistance);
			};
		};
		if (!distances.empty()) {
			std::sort(distances.begin(), distances.end());
			for (auto Entity : *Entities) {
				float currDistance = Utils::distanceVec3(*Entity->getPos(), *Player->getPos());
				if (currDistance == distances.at(0)) {
					aimAt(Entity);
					break;
				};
			};
		};
	};
};

void Aimbot::aimAt(Actor* Target) {
	LocalPlayer* Player = Minecraft::GetLocalPlayer();
	if (Player != nullptr) {
		Vec3 origin = Minecraft::GetClientInstance()->GetLevelRenderer()->origin();
		Vec2 angle = origin.calcAngle(*Target->getPos());
		Vec2 appl = angle.sub(Player->lookingVector).normalAngles();
		appl.x = -appl.x;
		Player->toActor()->applyTurnDelta(&appl);
	};
};