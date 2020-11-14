#include "ESP.h"
#include "../../SDK/Minecraft.h"

void ESP::onLoop() {
	if (Minecraft::GetLocalPlayer() == nullptr) {
		if (!cachedPlayers.empty()) cachedPlayers.clear();
	};
};

void ESP::onGmTick() {
	if (cachedPlayers.empty()) {
		for (auto Ent : *Minecraft::FetchPlayers()) {
			cachedPlayers.push_back(Ent);
		};
	};
};

void ESP::onRender() {
	if (canContinueRendering()) {
		Vec3 currPos = Minecraft::GetLocalPlayer() != nullptr ? *Minecraft::GetLocalPlayer()->getPos() : Vec3();
		for (auto target : cachedPlayers) {
			if (canContinueRendering() && Minecraft::GetClientInstance()->isValidTarget(target)) {
				RenderUtils::DrawBoxAroundEnt(target, 1, Minecraft::GetClientInstance());
				count++;
			}
			else {
				count = 0;
				break;
			};
		};
	};

	count = 0;
	cachedPlayers.clear();
};

bool ESP::canContinueRendering() {
	if (Minecraft::GetClientInstance() == nullptr)
		return false;
	if (Minecraft::GetLocalPlayer() == nullptr)
		return false;
	if (!Minecraft::GetClientInstance()->MinecraftGame->canUseKeys)
		return false;
	if (count >= 1000)
		return false;
	return true;
};