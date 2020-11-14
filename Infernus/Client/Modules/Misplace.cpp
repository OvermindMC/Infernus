#include "Misplace.h"
#include "AntiBot.h"
#include "../ClientHandler.h"
#include "../../SDK/Minecraft.h"

void Misplace::onGmTick() {
	LocalPlayer* Player = Minecraft::GetLocalPlayer();
	std::vector<Actor*>* Entities = Minecraft::FetchPlayers();
	bool antiBot = ClientHandler::GetModule(AntiBot())->isEnabled;
	if (Player != nullptr) {
		std::vector<float> distances;
		for (auto Entity : *Entities) {
			float distance = Utils::distanceVec3(*Entity->getPos(), *Player->getPos());
			if (distance <= range) {
				distances.push_back(distance);
			};
		};
		std::sort(distances.begin(), distances.end());
		if (!distances.empty()) {
			for (auto Entity : *Entities) {
				if (Utils::distanceVec3(*Entity->getPos(), *Player->getPos()) == distances.at(0)) {
					if (antiBot) {
						if (Minecraft::GetClientInstance()->isValidTarget(Entity) && Entity->movedTick > 1) {
							positionEntity(Entity);
						};
					}
					else {
						positionEntity(Entity);
					};
					break;
				};
			};
		};
	};
};

void Misplace::positionEntity(Actor* Entity) {
	LocalPlayer* Player = Minecraft::GetLocalPlayer();
	if (Player != nullptr && Entity != nullptr) {
		float calcYaw = (Player->lookingVector.y + 90.0f) * (PI / 180.0f);
		Vec3 currPos = *Player->getPos();
		currPos.x += cos(calcYaw) * 2.0f;
		currPos.z += sin(calcYaw) * 2.0f;
		Entity->setPos(&currPos);
	};
};