#include "Nametags.h"
#include "../../SDK/Minecraft.h"

void Nametags::onEnable() {
	count = 0;
};

bool Nametags::canContinueRendering() {
	if (Minecraft::GetClientInstance() == nullptr)
		return false;
	if (Minecraft::GetLocalPlayer() == nullptr)
		return false;
	if (!Minecraft::GetClientInstance()->MinecraftGame->canUseKeys)
		return false;
	if (count >= 50)
		return false;
	return true;
};

void Nametags::onRender() {
	if (canContinueRendering()) {
		Vec3 currPos = Minecraft::GetLocalPlayer() != nullptr ? *Minecraft::GetLocalPlayer()->getPos() : Vec3();
		auto Entities = Minecraft::FetchPlayers();
		for (auto Entity : *Entities) {
			if (canContinueRendering()) {
				if (Minecraft::GetClientInstance()->isValidTarget(Entity)) {
					float distance = Utils::distanceVec3(*Entity->getPos(), currPos);
					RenderUtils::DrawNametag(Entity, fmax(0.6f, 3.f / distance), Minecraft::GetClientInstance());
					count++;
				};
			}
			else {
				count = 0;
				break;
			};
		};
	};
	if (count > 0) {
		RenderUtils::FlushText();
		count = 0;
	};
};