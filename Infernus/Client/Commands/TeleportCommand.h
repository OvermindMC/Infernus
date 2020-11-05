#pragma once
#include "../../Other/VComponent.h"

class TeleportCommand : public VCommand {
public:
	TeleportCommand() : VCommand::VCommand("tp", "Teleport to the given coordinates") {};
	void execute(std::string, std::vector<std::string>);
};

void TeleportCommand::execute(std::string input, std::vector<std::string> words) {
	if (words.size() >= 4) {
		bool allTrue = true;
		for (int I = 1; I < words.size(); I++) {
			if (!Utils::isStringFloat(words.at(I))) allTrue = false;
		};
		if (allTrue) {
			LocalPlayer* Player = Minecraft::GetLocalPlayer();
			if (Player != nullptr) {
				Player->setPos(&Vec3(std::atof(words.at(1).c_str()), std::atof(words.at(2).c_str()), std::atof(words.at(3).c_str())));
				Player->displayTextObjectMessage(&TextHolder("Teleported!"));
			};
		}
		else {
			this->reply("Invalid parameters!");
			this->emptyReply();
			this->reply("Example: " + ClientHandler::commandPrefix + this->input + " 500 80 300");
		};
	}
	else {
		this->reply("Missing parameters!");
	};
};