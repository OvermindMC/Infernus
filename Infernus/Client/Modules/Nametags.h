#pragma once
#include "../../Other/VComponent.h"

class Nametags : public VModule {
public:
	Nametags() : VModule::VModule("Nametags", "Display entity nametags even when they're crouching") {};
	void onRender();
};

void Nametags::onRender() {
	auto Entities = Minecraft::FetchPlayers();
	if (Entities != nullptr && !Entities->empty()) {
		ClientInstance* instance = Minecraft::GetClientInstance();
		for (auto Entity : *Entities) {
			if (instance->isValidTarget(Entity)) {
				float distance = Utils::distanceVec3(*Entity->getPos(), *instance->LocalPlayer()->getPos());
				RenderUtils::DrawNametag(Entity, fmax(0.6f, 3.f / distance), instance);
			};
		};
		RenderUtils::FlushText();
	};
};