#pragma once
#include "../../Other/VComponent.h"

class TestCommand : public VCommand {
public:
	TestCommand() : VCommand::VCommand("test", "Test Command") {};
	void execute(std::string, std::vector<std::string>);
};

void TestCommand::execute(std::string input, std::vector<std::string> words) {
	this->reply("Hello, World!");
};