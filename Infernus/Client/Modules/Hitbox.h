#pragma once
#include "../../Other/VComponent.h"

class Hitbox : public VModule {
public:
	Hitbox() : VModule::VModule("Hitbox", "Enlarge the collision size of entities") {
		this->addWindowObj(new VWindowSlider("Width: ", &this->width));
		this->addWindowObj(new VWindowSlider("Height: ", &this->height));
	};
	void onGmTick();
	void onEnable() { revertMobs = true; };
	void onDisable();
	void onEntityTick(std::vector<Actor*>*);

	bool revertMobs = false;
	float width = 2.0f, height = 4.0f;
};