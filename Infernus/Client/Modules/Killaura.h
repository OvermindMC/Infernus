#pragma once
#include "../../Other/VComponent.h"
#include "AntiBot.h"

class Killaura : public VModule {
public:
	Killaura() : VModule::VModule("Killaura", "Automatically attack nearby entities") {
		this->addWindowObj(new VWindowButton("Multi-Ents", &this->multiEnts));
		this->addWindowObj(new VWindowButton("Attack with UI open", &this->menuOpen));
		this->addWindowObj(new VWindowButton("Send Server Rotations", &this->sendRotations));
		this->addWindowObj(new VWindowSlider("Range: ", &disRange));
		VWindowSlider* delaySlider = new VWindowSlider("Delay (MS): ", &delay_ms);
		delaySlider->max = 50.f;
		this->addWindowObj(delaySlider);
	};
	void onLoop() { delay_ms = roundf(delay_ms); };
	void onGmTick();

	void attackPlayers();
	void attackEnt(Actor*);

	void onPacket(void* Packet, PacketType type, bool* cancel);

	bool multiEnts = true;
	bool menuOpen = true;
	bool sendRotations = true;
	float disRange = 8.0f;
	float delay_ms = 0.0f;
	std::chrono::time_point<std::chrono::steady_clock> savedTime = std::chrono::high_resolution_clock::now();

	Vec2 storedAngles;
	bool writePacket = false;
};

void Killaura::onGmTick() {
	if (std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::high_resolution_clock::now() - savedTime) >= std::chrono::milliseconds((int)delay_ms)) {
		if (Minecraft::GetLocalPlayer() != nullptr) {
			if (menuOpen) {
				attackPlayers();
			}
			else {
				if (Minecraft::GetClientInstance()->MinecraftGame->canUseKeys) {
					attackPlayers();
				};
			};
		};
		savedTime = std::chrono::high_resolution_clock::now();
	};
};

void Killaura::attackPlayers() {
	LocalPlayer* Player = Minecraft::GetLocalPlayer();
	std::vector<Actor*>* Players = Minecraft::FetchPlayers();
	bool antiBot = ClientHandler::GetModule(AntiBot())->isEnabled;

	if (!Players->empty()) {
		Vec3 currPos = *Player->getPos();
		if (multiEnts) {
			if (antiBot) {
				for (auto ent : *Players) {
					if (Utils::distanceVec3(*ent->getPos(), currPos) <= disRange) {
						if (Minecraft::GetClientInstance()->isValidTarget(ent)) {
							attackEnt(ent);
						};
					};
				};
			}
			else {
				for (auto ent : *Players) {
					if (Utils::distanceVec3(*ent->getPos(), currPos) <= disRange) {
						attackEnt(ent);
					};
				};
			}
		}
		else {
			std::vector<float> distances = std::vector<float>();

			for (auto ent : *Players) {
				float distance = Utils::distanceVec3(*ent->getPos(), currPos);
				if (distance <= disRange) {
					distances.push_back(distance);
				};
			};

			if (!distances.empty()) {
				std::sort(distances.begin(), distances.end());

				for (auto ent : *Players) {
					float distance = Utils::distanceVec3(*ent->getPos(), currPos);
					if (distance == distances.at(0)) {
						if (antiBot) {
							if (Minecraft::GetClientInstance()->isValidTarget(ent)) {
								attackEnt(ent);
							};
						}
						else {
							attackEnt(ent);
						};
						break;
					};
				};
			};
		};
	};
};

void Killaura::attackEnt(Actor* entity) {
	GameMode* GM = Minecraft::GetGameMode();
	LocalPlayer* Player = Minecraft::GetLocalPlayer();

	if (Player != nullptr && GM != nullptr) {
		writePacket = true;
		storedAngles = Player->getRotationsToEnt(entity);
		GM->attack(entity);
		Player->swing();
	};
};

void Killaura::onPacket(void* Packet, PacketType type, bool* cancel) {
	if (sendRotations) {
		if (type == PacketType::MovePlayerPacket) {
			if (writePacket) {
				MovePlayerPacket* currentPacket = (MovePlayerPacket*)Packet;
				currentPacket->rotation = storedAngles;
				writePacket = false;
			};
		}
		else if (type == PacketType::PlayerAuthInput) {
			if (writePacket) {
				PlayerAuthInputPacket* currentPacket = (PlayerAuthInputPacket*)Packet;
				currentPacket->lookingVector = storedAngles;
				writePacket = false;
			};
		};
	};
};