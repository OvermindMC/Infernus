#include "PlayerWarning.h"
#include "../../SDK/Minecraft.h"

bool entAlreadyFound(std::vector<Actor*>* Vec, Actor* Entity) {
	__int64 matchID = Entity->GetRuntimeID();
	bool exists = false;
	for (auto EntityObj : *Vec) {
		if (EntityObj->GetRuntimeID() == matchID) exists = true;
	};
	return exists;
};

void PlayerWarning::onGmTick() {
	LocalPlayer* Player = Minecraft::GetLocalPlayer();
	if (Player != nullptr) {
		auto Entities = Minecraft::FetchPlayers();
		if (Entities != nullptr && !Entities->empty()) {
			for (auto Entity : *Entities) {
				if (!entAlreadyFound(detectedEnts, Entity)) {
					detectedEnts->push_back(Entity);
					displayWarning(Entity);
				};
			};
		};
		for (auto Ent : *detectedEnts) {
			if (!entAlreadyFound(Entities, Ent)) {
				displayNonThreat(Ent);
				detectedEnts = removeDetectedEnt(Ent);
			};
		};
	}
	else {
		if (!detectedEnts->empty()) {
			detectedEnts->clear();
		};
	};
};

void PlayerWarning::displayWarning(Actor* Entity) {
	LocalPlayer* Player = Minecraft::GetLocalPlayer();
	Vec3 entPos = *Entity->getPos();
	std::string coordsStr = std::string("X: " + std::to_string((int)entPos.x) + " | Y: " + std::to_string((int)entPos.y) + " | Z: " + std::to_string((int)entPos.z));
	std::string message = std::string("Player with username ( " + std::string(Entity->getNameTag()->getText()) + " ) was detected nearby! Coordinates: " + coordsStr);
	std::string distanceStr = std::to_string((int)(Utils::distanceVec3(entPos, *Player->getPos())));
	Player->displayTextObjectMessage(&TextHolder(message));
	Player->displayTextObjectMessage(&TextHolder("Distance: " + distanceStr));
};

void PlayerWarning::displayNonThreat(Actor* Entity) {
	LocalPlayer* Player = Minecraft::GetLocalPlayer();
	if (Player != nullptr) {
		Player->displayTextObjectMessage(&TextHolder("One previously detected player is no longer nearby!"));
	};
};

std::vector<Actor*>* PlayerWarning::removeDetectedEnt(Actor* EntityObj) {
	std::vector<Actor*>* newVec = new std::vector<Actor*>();
	for (auto Entity : *detectedEnts) {
		if (Entity != EntityObj) newVec->push_back(Entity);
	};
	return newVec;
};