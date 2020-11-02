#pragma once
#include "../../Other/VComponent.h"

class Nametags : public VModule {
public:
	Nametags() : VModule::VModule("Nametags", "Display entity nametags even when they're crouching") {};
	void onRender();
};

void Nametags::onRender() {
	auto C_instance = Minecraft::GetClientInstance();
	auto L_Player = Minecraft::GetLocalPlayer();
	bool canUseKeys = C_instance != nullptr ? C_instance->MinecraftGame->canUseKeys : false;

	if (L_Player != nullptr && canUseKeys && RenderUtils::canUseRenderUtils()) {
		auto Players = Minecraft::FetchPlayers();

		if (!Players->empty()) {
			for (auto Player : *Players) {
				if (L_Player != nullptr) {
					if (C_instance->isValidTarget(Player)) {
						float distance = Utils::distanceVec3(*Player->getPos(), *C_instance->LocalPlayer()->getPos());
						RenderUtils::DrawNametag(Player, MC_Colour(255, 255, 255), MC_Colour(50, 50, 50), MC_Colour(30, 160, 200), fmax(0.6f, 3.f / distance), C_instance);
					};
				};
			};
		};
	};
};