#include "VComponent.h"
#include "RenderUtils.h"
#include "../Client/ClientHandler.h"

void VModule::onBaseTick() {
	this->onLoop();
	if (this->wasEnabled != this->isEnabled) {
		if (this->isEnabled) {
			this->onEnable();
		}
		else {
			this->onDisable();
		};
		ClientHandler::UpdateModuleFileData(this);
		this->wasEnabled = this->isEnabled;
	};
	if (this->isEnabled) this->onTick();
};

void VModule::addWindowObj(VWindowObject* Obj) {
	objCount++;
	Obj->ID = objCount;
	this->WindowObjects.push_back(Obj);
};

void VCommand::reply(std::string input) {
	LocalPlayer* Player = Minecraft::GetLocalPlayer();
	if (Player != nullptr) {
		Player->displayTextObjectMessage(&TextHolder(input));
	};
};