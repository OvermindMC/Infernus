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

void Surround::onLoop() {
	if (ScaffoldMod == nullptr) {
		ScaffoldMod = (Scaffold*)ClientHandler::GetModule(Scaffold());
	};
}

void Surround::onGmTick() {
	LocalPlayer* Player = Minecraft::GetLocalPlayer();
	if (Player != nullptr) {
		auto Players = *Minecraft::FetchPlayers();
		Vec3 currPos = *Player->getPos();
		std::vector<float> distances = std::vector<float>();
		for (auto ent : Players) {
			float distance = Utils::distanceVec3(*ent->getPos(), currPos);
			if (distance <= range) {
				distances.push_back(distance);
			};
		};

		if (!distances.empty()) {
			std::sort(distances.begin(), distances.end());

			for (auto ent : Players) {
				if (Utils::distanceVec3(*ent->getPos(), currPos) == distances.at(0)) {
					surroundEnt(ent);
					break;
				};
			};
		};
	};
};

void Surround::removeFromVecArr(std::vector<Vec3>* arr, Vec3 el) {
	auto cloned = *arr;
	arr->clear();

	for (auto curr : cloned) {
		if (curr != el) arr->push_back(curr);
	};

	return;
};

void Surround::calculateAroundPos(std::vector<Vec3>* blockPositions, Vec3 targetPos) {
	if (blockPositions->empty()) {
		for (int x = -1; x <= 1; x++) {
			for (int z = -1; z <= 1; z++) {
				Vec3 newPos = Vec3(targetPos.x + x, targetPos.y, targetPos.z + z);
				if (floorf(newPos.x) != floorf(targetPos.x) || floorf(newPos.z) != floorf(targetPos.z)) {
					blockPositions->push_back(newPos);
				};
			};
		};

		for (auto curr : *blockPositions) {
			for (int y = 0; y < 3; y++) {
				Vec3 newPos = Vec3(curr.x, curr.y + y, curr.z);
				if (floorf(newPos.x) != floorf(targetPos.x) || floorf(newPos.z) != floorf(targetPos.z)) {
					blockPositions->push_back(newPos);
				};
			};
		};

		blockPositions->push_back(Vec3(targetPos.x, targetPos.y + 2, targetPos.z));
	};
};

void Surround::surroundEnt(Actor* Entity) {
	LocalPlayer* Player = Minecraft::GetLocalPlayer();
	Vec3 entPos = *Entity->getPos();
	entPos.y -= 1;

	std::vector<Vec3> blockPositions = std::vector<Vec3>();
	AABB entAABB = Entity->GetAABB();

	calculateAroundPos(&blockPositions, entPos);
	doSurround(&blockPositions);

	if (((LocalPlayer*)(Entity))->isSprinting()) {
		float speed = Entity->Velocity.magnitudexz();
		Vec3 vel = Entity->Velocity;
		vel = vel.normalize();
		entPos.x -= vel.x * 1.0f;
		entPos.z -= vel.z * 1.0f;
		calculateAroundPos(&blockPositions, entPos);
		doSurround(&blockPositions);
	};
};

void Surround::doSurround(std::vector<Vec3>* blockPositions) {
	if (!blockPositions->empty()) {
		for (auto blockPos : *blockPositions) {
			ScaffoldMod->tryBuild(blockPos);
		};
	};
};