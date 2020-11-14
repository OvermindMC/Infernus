#pragma once
#include "../../Other/VComponent.h"

class PlayerWarning : public VModule {
public:
	PlayerWarning() : VModule::VModule("PlayerWarning", "Tells you in chat when a player is near") {};
	void onGmTick();
	void displayWarning(Actor*);
	void displayNonThreat(Actor*);
	void onDisable() { detectedEnts->clear(); };
	std::vector<Actor*>* removeDetectedEnt(Actor*);
private:
	std::vector<Actor*>* detectedEnts = new std::vector<Actor*>();
};