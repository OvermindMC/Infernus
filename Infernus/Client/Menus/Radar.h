#pragma once
#include "../../Other/VComponent.h"

class Radar : public VModule {
public:
	Radar() : VModule::VModule("Radar", "Display nearby enemies") {
		this->addWindowObj(new VWindowText("Radar Size:"));
		this->addWindowObj(new VWindowSlider(&this->radarSize, 0, 100.0f));
		this->addWindowObj(new VWindowText("Entity Range:"));
		this->addWindowObj(new VWindowSlider(&this->entityRange, 0.0f, 100.0f));
	};
	void onRender();
	void renderEntities();

	void onEnable() {
		if (radarWindow == nullptr) radarWindow = new VWindow("Radar", Vec4(windowPosition.x, windowPosition.y, windowPosition.x + (radarSize * 2), windowPosition.y + (radarSize * 2)));
	};
private:
	/* WIP */
	VWindow* radarWindow = nullptr;
	Vec2 windowPosition = Vec2(20, 20);
	bool showCoords = false, showNametags = false;
	float entityRange = 50.0f;
	float radarSize = 50.0f;
};

void Radar::onRender() {
	if (radarWindow != nullptr && Minecraft::GetLocalPlayer()) {
		windowPosition = Vec2(radarWindow->position.x, radarWindow->position.y);
		radarWindow->position = Vec4(windowPosition.x, windowPosition.y, windowPosition.x + (radarSize * 2), windowPosition.y + (radarSize * 2));
		radarWindow->Render();
		Radar::renderEntities();
	};
};

void Radar::renderEntities() {
	LocalPlayer* Player = Minecraft::GetLocalPlayer();
	std::vector<Actor*>* Players = Minecraft::FetchPlayers();
	Vec3 currPos = *Player->getPos();
	float rectSize = (radarSize / 10) - 9;

	if (Player != nullptr && Player->toActor()->movedTick > 1) {
		float centerX = radarWindow->position.x + radarSize;
		float centerY = radarWindow->position.y + radarSize;
		RenderUtils::DrawRectangle(Vec4(centerX, centerY, centerX + 1.0f, centerY + 1.0f), MC_Colour(100, 255, 180), 1.0f, rectSize);
	};

	if (Players->size() > 0) {
		for (auto Entity : *Players) {
			if (Minecraft::GetClientInstance()->isValidTarget(Entity)) {
				Vec3 entPos = *Entity->getPos();
				if (Utils::distanceVec3(currPos, entPos) <= entityRange) {
					float offX = currPos.x - entPos.x;
					float offY = currPos.z - entPos.z;
					float screenX = windowPosition.x + offX + radarSize;
					float screenY = windowPosition.y + offY + radarSize;
					if (radarWindow->withinWindow(screenX, screenY)) RenderUtils::DrawRectangle(Vec4(screenX, screenY, screenX + 1.0f, screenY + 1.0f), MC_Colour(255, 0, 0), 1.0f, rectSize);
				};
			};
		};
	};
};