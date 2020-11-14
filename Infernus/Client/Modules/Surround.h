#pragma once
#include "../../Other/VComponent.h"
#include "Scaffold.h"

class Surround : public VModule {
public:
	Surround() : VModule::VModule("Surround", "Surround players in blocks") {
		this->addWindowObj(new VWindowSlider("Range: ", &range));
	};

	void onLoop();
	void onGmTick();
	void calculateAroundPos(std::vector<Vec3>*, Vec3);
	void removeFromVecArr(std::vector<Vec3>*, Vec3);
	void surroundEnt(Actor*);
	void doSurround(std::vector<Vec3>*);
private:
	Scaffold* ScaffoldMod = nullptr;
	float range = 5.f;
};