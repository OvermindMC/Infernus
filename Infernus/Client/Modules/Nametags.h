#pragma once
#include "../../Other/VComponent.h"

class Nametags : public VModule {
public:
	Nametags() : VModule::VModule("Nametags", "Display entity nametags even when they're crouching") {};
	void onRender();
	bool canContinueRendering();
};

bool Nametags::canContinueRendering() {
	if (Minecraft::GetClientInstance() == nullptr)
		return false;
	if (Minecraft::GetLocalPlayer() == nullptr)
		return false;
	if (!Minecraft::GetClientInstance()->MinecraftGame->canUseKeys)
		return false;
	return true;
};

void Nametags::onRender() {
	std::vector<Actor*>* Entities = Minecraft::FetchPlayers();
	if (canContinueRendering()) {
		for (auto Entity : *Entities) {
			if (canContinueRendering()) {
				if (Minecraft::GetClientInstance()->isValidTarget(Entity)) {
					float distance = Utils::distanceVec3(*Entity->getPos(), *Minecraft::GetLocalPlayer()->getPos());
					RenderUtils::DrawNametag(Entity, fmax(0.6f, 3.f / distance), Minecraft::GetClientInstance());
				};
			}
			else {
				Entities->clear();
				break;
			};
		};
		RenderUtils::FlushText();
	};
};