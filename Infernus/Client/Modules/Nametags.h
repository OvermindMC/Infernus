#pragma once
#include "../../Other/VComponent.h"

class Nametags : public VModule {
public:
	Nametags() : VModule::VModule("Nametags", "Display entity nametags even when they're crouching") {
		this->addWindowObj(new VWindowButton("Show Mobs", &showMobs));
	};
	void onTick();
	void onDisable();
	void onRender();
	void removeCachedEnt(Actor*);
	bool alreadyCached(Actor*);
	void onEntityTick(std::vector<Actor*>*);
private:
	bool showMobs = true;
	std::vector<Actor*> CachedEntities;
};

void Nametags::onTick() {
	if (Minecraft::GetLocalPlayer() == nullptr && !CachedEntities.empty()) CachedEntities.clear();
};

void Nametags::onDisable() {
	if(!CachedEntities.empty()) CachedEntities.clear();
};

void Nametags::onRender() {
	auto C_instance = Minecraft::GetClientInstance();
	auto L_Player = Minecraft::GetLocalPlayer();

	if (L_Player != nullptr) {
		if (Minecraft::GetClientInstance()->MinecraftGame->canUseKeys) {
			auto Players = *Minecraft::FetchPlayers();
			for (auto Player : Players) {
				if (C_instance->isValidTarget(Player)) {
					float distance = Utils::distanceVec3(*Player->getPos(), *C_instance->LocalPlayer()->getPos());
					RenderUtils::DrawNametag(Player, MC_Colour(255, 255, 255), MC_Colour(50, 50, 50), MC_Colour(30, 160, 200), fmax(0.6f, 3.f / distance), C_instance);
				};
			};

			for (auto Entity : CachedEntities) {
				if (Entity != nullptr && Entity->isAlive()) {
					float distance = Utils::distanceVec3(*Entity->getPos(), *C_instance->LocalPlayer()->getPos());
					RenderUtils::DrawNametag(Entity, MC_Colour(255, 255, 255), MC_Colour(50, 50, 50), MC_Colour(90, 215, 125), fmax(0.6f, 3.f / distance), C_instance);
				}
				else {
					removeCachedEnt(Entity);
				};
			};

			if (!Players.empty() || !CachedEntities.empty()) {
				RenderUtils::FlushText();
			};
		};
	};
};

void Nametags::removeCachedEnt(Actor* Entity) {
	std::vector<Actor*> newArr;
	for (auto Ent : CachedEntities) {
		if (Ent != Entity && Ent->EntityID != Entity->EntityID) {
			newArr.push_back(Ent);
		};
	};
	CachedEntities.clear();
	for (auto Ent : newArr) {
		CachedEntities.push_back(Ent);
	};
};

bool Nametags::alreadyCached(Actor* Entity) {
	for (auto Ent : CachedEntities) {
		if (Ent == Entity || Ent->EntityID == Entity->EntityID) return true;
	};
	return false;
};

void Nametags::onEntityTick(std::vector<Actor*>* Entities) {
	if (CachedEntities.empty()) {
		for (auto Entity : *Entities) {
			if (!alreadyCached(Entity)) CachedEntities.push_back(Entity);
		};
	}
	else {
		CachedEntities.clear();
		for (auto Entity : *Entities) {
			if (!alreadyCached(Entity)) CachedEntities.push_back(Entity);
		};
	};
};