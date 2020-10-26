#pragma once
#include "../../Other/VComponent.h"

class TestCommand : public VCommand {
public:
	TestCommand() : VCommand::VCommand("test", "Test Command") {};
	void execute(std::string, std::vector<std::string>);
};

void TestCommand::execute(std::string input, std::vector<std::string> words) {
	this->reply("Hello, World!");
	LocalPlayer* Player = Minecraft::GetLocalPlayer();
	if (Player != nullptr) {
		Player->displayTextObjectMessage(&TextHolder("Sending movement packet.."));
		MovePlayerPacket newPacket(Player->toActor(), *Player->getPos(), Player->lookingVector, Player->onGround);
		Minecraft::GetClientInstance()->LoopbackPacketSender->sendToServer(&newPacket);
	};
};